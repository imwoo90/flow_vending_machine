#include "EnterPasswordOfVendingMachineModeSetting.h"

#include "SystemSetting.h"
#include "VendingMachineModeSetting.h"


bool EnterPasswordOfVendingMachineModeSetting::isMatched(int password) {
    return _database->getPasswordOfVendingMachineModeSetting() == password;
}

MachineState* EnterPasswordOfVendingMachineModeSetting::decide() {
    if (_isChangePasswords) {
        return this;
    }
    return VendingMachineModeSetting::getInstance();
}

MachineState* EnterPasswordOfVendingMachineModeSetting::cancel() {
    if (_isChangePasswords) {
        return this;
    }
    return SystemSetting::getInstance();
}

void EnterPasswordOfVendingMachineModeSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfVendingMachineModeSetting";
    _data["param_0"] = "00000000";
}

EnterPasswordOfVendingMachineModeSetting* EnterPasswordOfVendingMachineModeSetting::getInstance(bool changePassword) {
    static EnterPasswordOfVendingMachineModeSetting singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}