#include <events/mbed_events.h>
#include "ble/BLE.h"
#include "ble/Gap.h"
#include "pretty_printer.h"

/* General Notes
    - GAP: defines the general topology of the BLE network stack.
    - GATT: describes in detail how attributes (data) are 
            transferred once devices have a dedicated connection.
*/


const static char DEVICE_NAME[] = "REBOUND";

using namespace std::literals::chrono_literals;

/* should be plenty large enough for our purposes */
events::EventQueue event_queue;

/* basic advertising parameters */
static const ble::AdvertisingParameters advertising_params(
    ble::advertising_type_t::CONNECTABLE_UNDIRECTED, /* type of connection */
    ble::adv_interval_t(ble::millisecond_t(25)), /* min advertising interval */
    ble::adv_interval_t(ble::millisecond_t(50)) /* max advertising interval */
);

class Connectable : public ble::Gap::EventHandler
{
    public:
        Connectable(BLE& ble, events::EventQueue& event_queue) : 
        _ble(ble),
        _gap(ble.gap()),
        _event_queue(event_queue) { }

        ~Connectable() { 
            if(_ble.hasInitialized()) {
                _ble.shutdown();
            }
        }

        /* starts ble initialization */
        void run() {
            // handle gap events
            _gap.setEventHandler(this);
            // check for errors in initialization 
            ble_error_t error = _ble.init(this, &Connectable::on_init_complete);
            if(error) {
                print_error(error, "Error returned by init call");
                return;
            }
            /* dispatches forever, does not return */
            _event_queue.dispatch_forever();
        }

    private: 

        /* called when BLE interface is successfully initialized */
        void on_init_complete(BLE::InitializationCompleteCallbackContext *event) { 
            if(event->error) {
                print_error(event->error, "Error during init");
            }

            print_mac_address();

            /* setup the default phy used in connection to 2M to reduce power consumption */
            if (_gap.isFeatureSupported(ble::controller_supported_features_t::LE_2M_PHY)) {
                ble::phy_set_t phys(/* 1M */ false, /* 2M */ true, /* coded */ false);
                ble_error_t error = _gap.setPreferredPhys(/* tx */&phys, /* rx */&phys);
            /* PHY 2M communication will only take place if both peers support it */
                if (error) {
                    print_error(error, "GAP::setPreferedPhys failed");
                }
            } else {
                /* otherwise it will use 1M by default */
            }
            /* all calls are serialised on the user thread through the event queue.
               Start advertising. */
            _event_queue.call(this, &Connectable::advertise);
        }

        /* sets up and starts advertising */
        void advertise() {
            ble_error_t error = _gap.setAdvertisingParameters(ble::LEGACY_ADVERTISING_HANDLE, advertising_params);
            if(error) {
                print_error(error, "Gap::setAdvertisingParameters() failed");
                return;
            }

            // using a helper class to help us build a valid payload
            ble::AdvertisingDataSimpleBuilder<ble::LEGACY_ADVERTISING_MAX_SIZE> data_builder;
            // you can chain builder method calls to create the payload 
            data_builder.setFlags().setName("Legacy Set LUZ");

            // set advertising payload 
            error = _gap.setAdvertisingPayload(ble::LEGACY_ADVERTISING_HANDLE, data_builder.getAdvertisingData());
            if (error) {
                print_error(error, "Gap::setAdvertisingPayload() failed");
                return;
            }

            // start advertising the set
            error = _gap.startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
            if (error) {
                print_error(error, "Gap::startAdvertising() failed");
                return;
            }

            printf(
                "\r\nAdvertising started (type: 0x%x, interval: [%d : %d]ms)\r\n",
                advertising_params.getType(),
                advertising_params.getMinPrimaryInterval().valueInMs(),
                advertising_params.getMaxPrimaryInterval().valueInMs());

            // we don't do anything that will "end" advertising? hoping that connection events can still come through
        }

        /** Rest are defined GAP event handlers **/

        /* defines behavior at end of advertising */
        void onAdvertisingEnd(const ble::AdvertisingEndEvent &event) override { 
            if (event.isConnected()) {
                printf("Stopped advertising early due to connection\r\n");
            }
        }
        /* defines behavior at beginning of advertising */
        void onAdvertisingStart(const ble::AdvertisingStartEvent &event) override { 
            printf("Advertising set %d started\r\n", event.getAdvHandle());
        }
        /* called by Gap to notify the application we connected */ 
        void onConnectionComplete(const ble::ConnectionCompleteEvent &event) override {  
            if (event.getStatus() != BLE_ERROR_NONE) {
                print_error(event.getStatus(), "Connection failed");
                return;
            }
            printf("Connected!! \n");
        }
        /* called by Gap to notify the application we disconnected */
        void onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event) override {  
            printf("Disconnected \r \n");
            if(event.getReason() == ble::disconnection_reason_t::REMOTE_USER_TERMINATED_CONNECTION) {
                printf("Remote user disconnected \r \n");
            }
        }

        /** Carrying over phy error handling from Gap demo **/
        void onReadPhy(
            ble_error_t error,
            ble::connection_handle_t connectionHandle,
            ble::phy_t txPhy,
            ble::phy_t rxPhy) override {
            if (error) {
                printf(
                    "Phy read on connection %d failed with error code %s\r\n",
                    connectionHandle, BLE::errorToString(error)
                );
            } else {
                printf(
                    "Phy read on connection %d - Tx Phy: %s, Rx Phy: %s\r\n",
                    connectionHandle, phy_to_string(txPhy), phy_to_string(rxPhy)
                );
            }
        }

        void onPhyUpdateComplete(
            ble_error_t error,
            ble::connection_handle_t connectionHandle,
            ble::phy_t txPhy,
            ble::phy_t rxPhy) override {
            if (error) {
                printf(
                    "Phy update on connection: %d failed with error code %s\r\n",
                    connectionHandle, BLE::errorToString(error)
                );
            } else {
                printf(
                    "Phy update on connection %d - Tx Phy: %s, Rx Phy: %s\r\n",
                    connectionHandle, phy_to_string(txPhy), phy_to_string(rxPhy)
                );
            }
        }

        /**
         * Implementation of Gap::EventHandler::onDataLengthChange
         */
        void onDataLengthChange(
            ble::connection_handle_t connectionHandle,
            uint16_t txSize,
            uint16_t rxSize
        ) override {
            printf(
                "Data length changed on the connection %d.\r\n"
                "Maximum sizes for over the air packets are:\r\n"
                "%d octets for transmit and %d octets for receive.\r\n",
                connectionHandle, txSize, rxSize
            );
        }

        /** MEMBER VARIABLES **/
        BLE &_ble;
        ble::Gap &_gap;
        events::EventQueue &_event_queue;

        bool _is_conencting = false;
};

/*Schedule processing of events from the BLE middleware in the event queue.*/
void schedule_ble_events(BLE::OnEventsToProcessCallbackContext *context) {
    event_queue.call(Callback<void()>(&context->ble, &BLE::processEvents));
}

int main() 
{
    BLE &ble = BLE::Instance();
    // transfers control of event scheduling to our event queue 
    ble.onEventsToProcess(schedule_ble_events);

    Connectable connectable(ble, event_queue);
    connectable.run();
    
    return 0;
}

/* A couple of observations: 
    - name observed via the bluetooth scanner said that the name was set to 
    'legacy set LUZ'. Nice, didn't know that was the actual name
    - on disconnect, the board no longer seems to advertise. Maybe stretch goal could be to 
    restart advertising?
    - next goal should be to faciliate some sort of data transfer 
*/