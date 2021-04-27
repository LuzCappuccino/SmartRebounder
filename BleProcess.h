#include <stdint.h>
#include "ble/BLE.h"
#include "ble/Gap.h"
#include "pretty_printer.h"

/* new headers */
#include <events/mbed_events.h>
#include "platform/Callback.h"
#include "gap/AdvertisingDataParser.h"

const static char DEVICE_NAME[] = "BLE_LUZ";
static const uint16_t MAX_ADVERTISING_PAYLOAD_SIZE = 50;

using namespace std::literals::chrono_literals;

/* basic advertising parameters */
static const ble::AdvertisingParameters advertising_params(
    ble::advertising_type_t::CONNECTABLE_UNDIRECTED, /* type of connection, not looking for any specific peer */
    ble::adv_interval_t(ble::millisecond_t(25)), /* min advertising interval */
    ble::adv_interval_t(ble::millisecond_t(50)) /* max advertising interval */
);

class BLEProcess :  public ble::Gap::EventHandler {
    public:
        BLEProcess(BLE& ble, events::EventQueue& event_queue) : _ble(ble),
            _event_queue(event_queue),
            _gap(ble.gap()),
            _adv_data_builder(_adv_buffer) {  }

        ~BLEProcess() { stop(); }

        void start() {
            printf("Starting ble process...\n");
            if (_ble.hasInitialized()) {
                printf("Error: the ble instance has already been initialized.\r\n");
                return;
            }

            _gap.setEventHandler(this);
            // informs us of all events so we can schedule their handling using our event queue 
            _ble.onEventsToProcess(makeFunctionPointer(this, &BLEProcess::schedule_ble_events));
            // check for errors in initialization 
            ble_error_t error = _ble.init(this, &BLEProcess::on_init_complete);
            if(error) {
                print_error(error, "Error returned by init call");
                return;
            }
            // dispatches forever, does not return 
            _event_queue.dispatch_forever();
            return; // for code's sake 
        }
        void stop() {
            if(_ble.hasInitialized()) {
                _ble.shutdown();
                printf("Ble process has stopped. \n");
            }
        }

        // Defines callback to run the ble interface is initialized
        void on_init(mbed::Callback<void(BLE&, events::EventQueue&)> cb) {
            _post_init_cb = cb;
        }
        // Defines callback to run on successful connection
        void on_connect(mbed::Callback<void(BLE&, events::EventQueue&, const ble::ConnectionCompleteEvent &event)> cb) {
            _post_connect_cb = cb;
        }
    protected:
        // sets up advertising pyaload and starts advertising 
        // Function is invoked when the ble interface is initialized
        void on_init_complete(BLE::InitializationCompleteCallbackContext *event) {
            if(event->error) {
                print_error(event->error, "Error during init");
                return;
            }
            printf("Ble instance initialized \n");
            // All calls are serialised on the user thread through the event queue
            start_activity(); // calls the main advertising function 

            if(_post_init_cb) {
                _post_init_cb(_ble, _event_queue);
            }
        }
        // Called by Gap to notify the application we connected
        void onConnectionComplete(const ble::ConnectionCompleteEvent &event) override {
            if(event.getStatus() != BLE_ERROR_NONE) {
                printf("Connected to: ");
                print_address(event.getPeerAddress());
                if(_post_connect_cb) {
                    _post_connect_cb(_ble, _event_queue, event);
                }
            } else {
                printf("Failed to connect...\n");
                start_activity(); // restarts main activity
            }
        }
        // Called by gap to notify the application we disconnected 
        void onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event) override {
            printf("Disconnected...\n");
            start_activity(); // restarts main activity
        }
        // Restarts main activity on advertising end
        void onAdvertisingEnd(const ble::AdvertisingEndEvent &event) {
            start_activity(); // restarts main activity
        }
        // Starts advertising/scanning. Triggered by init or disconnection 
        virtual void start_activity() {
            _event_queue.call([this]() { advertise(); });
        }
        // Defines how to start the advertising process; ends when device connects
        void advertise() {
            ble_error_t error;
            if(_gap.isAdvertisingActive(_adv_handle)) {
                return; // already advertising
            }

            error = _gap.setAdvertisingParameters(_adv_handle, advertising_params);
            if(error) {
                print_error(error, "gap setAdvertisingParameters failed! \n");
                return;
            }

            _adv_data_builder.clear();
            _adv_data_builder.setFlags();
            _adv_data_builder.setName("BLE_LUZ");

            // set advertising payload
            error = _gap.setAdvertisingPayload(_adv_handle, _adv_data_builder.getAdvertisingData());
            if (error) {
                print_error(error, "Gap::setAdvertisingPayload() failed\r\n");
                return;
            }
            // start advertising the set
            error = _gap.startAdvertising(_adv_handle);
            if (error) {
                print_error(error, "Gap::startAdvertising() failed");
                return;
            }

            printf(
                "\r\nAdvertising started (type: 0x%x, interval: [%d : %d]ms)\r\n",
                advertising_params.getType(),
                advertising_params.getMinPrimaryInterval().valueInMs(),
                advertising_params.getMaxPrimaryInterval().valueInMs());
        }
        // Schedules processing of events from the ble middleware in the event queue
        void schedule_ble_events(BLE::OnEventsToProcessCallbackContext *event) {
            _event_queue.call(mbed::callback(&event->ble, &BLE::processEvents));
        }
    protected:
        events::EventQueue &_event_queue;
        BLE &_ble;
        ble::Gap &_gap;

        uint8_t _adv_buffer[MAX_ADVERTISING_PAYLOAD_SIZE];
        ble::AdvertisingDataBuilder _adv_data_builder;
        ble::advertising_handle_t _adv_handle = ble::LEGACY_ADVERTISING_HANDLE;

        mbed::Callback<void(BLE&, events::EventQueue&)> _post_init_cb;
        mbed::Callback<void(BLE&, events::EventQueue&, const ble::ConnectionCompleteEvent &event)> _post_connect_cb;
};