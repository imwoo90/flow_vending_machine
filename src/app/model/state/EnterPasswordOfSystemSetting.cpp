#include "EnterPasswordOfSystemSetting.h"

#include "SystemSetting.h"
#include "Selling.h"

bool EnterPasswordOfSystemSetting::isMatched(int password) {
    return _database->getPasswordOfSystemSetting() == password;
}

MachineState* EnterPasswordOfSystemSetting::decide(int password) {
    if (_isChangePasswords) {
        _database->setPasswordOfSystemSetting(password);
        return this;
    }
    return SystemSetting::getInstance();
}

MachineState* EnterPasswordOfSystemSetting::cancel() {
    if (_isChangePasswords) {
        return PasswordChange::getInstance();
    }
    return Selling::getInstance();
}

void EnterPasswordOfSystemSetting::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterPasswordOfSystemSetting";
    if (_isChangePasswords) {
        char buf[32];
        _data["param_0"] = itoa(_database->getPasswordOfSystemSetting(), buf, 10);
    } else {
        _data["param_0"] = "0000";
    }
}

EnterPasswordOfSystemSetting* EnterPasswordOfSystemSetting::getInstance(bool changePassword) {
    static EnterPasswordOfSystemSetting singleton_instance;
    singleton_instance._isChangePasswords = changePassword;
    singleton_instance.initialize();
    return &singleton_instance;
}
