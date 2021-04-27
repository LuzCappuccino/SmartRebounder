#include <events/mbed_events.h>
#include "ble/BLE.h"
#include "ble/GattServer.h"
#include "BleProcess.h"

#include <map>
#include <string>

enum RebounderModes {
    PLAYER_TRACK = 0,
    MANUEL_CONTROL = 1,
    UPLOAD_SEQUENCE = 2,
};

static map<char, std::string> modeToString = {
    {0, "player_track"},
    {1, "manuel_control"},
    {2, "upload_sequence"},
};

static EventQueue event_queue(/* event count */ 10 * EVENTS_EVENT_SIZE);

class ModeSwitchService : ble::GattServer::EventHandler {
    const static uint16_t FITNESS_SERVICE_UUID = GattService::UUID_FITNESS_MACHINE_SERVICE;
    const static uint16_t WRITABLE_MODE_CHAR_UUID = GattCharacteristic::UUID_FITNESS_MACHINE_CONTROL_POINT_CHAR;

    public:
        ModeSwitchService() {
            // init characteristic
            _mode_char = new ReadWriteGattCharacteristic<uint8_t>(WRITABLE_MODE_CHAR_UUID, &_mode_value);
            if(!_mode_char) {
                printf("Failed to allocate mode characteristic! \n");
            }   
        }
        ~ModeSwitchService() { }

        void start(BLE &ble, events::EventQueue &event_queue) {
            GattCharacteristic* charTable[] = { _mode_char };
            GattService modeServ(FITNESS_SERVICE_UUID, charTable, 1);

            ble.gattServer().addService(modeServ);
            ble.gattServer().setEventHandler(this);

            printf("Service added with UUID %u \n", (unsigned int) FITNESS_SERVICE_UUID);
            printf("Connect and write to characteristic %u \n", (unsigned int) WRITABLE_MODE_CHAR_UUID);
        }

        void printCurrentMode() {
            std::map<char, std::string>::iterator itr = modeToString.find(_mode_value);
            if(itr != modeToString.end()) {
                printf("Current mode %s \n", itr->second.c_str());
            } else {
                printf("ERROR: Invalid mode number %u", (unsigned int) _mode_value);
            }
        }

    private:
        // called whenever information about the characteristic is being updated
        virtual void onDataWritten(const GattWriteCallbackParams &params) {
            if(params.handle == _mode_char->getValueHandle()) {
                if(params.len == 1) {
                    printf("New characteristic value written: %x\r\n", *(params.data));
                    _mode_value = *(params.data);
                    printCurrentMode();
                } else {
                    printf("Wrote more than a byte to mode attribute. \n");
                }
            } else {
                printf("Wrote to non-mode attribute. \n");
            }
        }
    private:
        ReadWriteGattCharacteristic<uint8_t> *_mode_char = nullptr;
        uint8_t _mode_value = 0; // defaults to player track mode
};

int main()
{
    BLE &ble = BLE::Instance();
    printf("Starting mode switch service... \n");
    ModeSwitchService modeSwitchService;

    BLEProcess ble_process(ble, event_queue);
    ble_process.on_init(callback(&modeSwitchService, &ModeSwitchService::start));

    ble_process.start();
    return 0;
}