#include "ble/BLE.h"
#include "ble/Gap.h"
#include "ble/GattServer.h"

#include <map>
#include <string>

enum RebounderModes {
    PLAYER_TRACK = 0,
    MANUEL_CONTROL = 1,
    UPLOAD_SEQUENCE = 2,
};

static map<int, std::string> modeToString = {
    {0, "player_track"},
    {1, "manuel_control"},
    {3, "upload_sequence"},
};


class ModeSwitchService {
    public:
        ModeSwitchService();
        ~ModeSwitchService();
    private:
        RebounderModes _mode;
        
};