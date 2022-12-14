#include "EnterProductNumber.h"
#include "Selling.h"
#include "EnterPasswordOfSystemSetting.h"
#include "InputMoney.h"
#include "EnterProductNumberNoGoods.h"

static void keyTimeoutCallBack( TimerHandle_t xTimer ) {
    MachineState::_timeoutCallback(TimeoutEnterProductNumber);
}

EnterProductNumber::EnterProductNumber() {
    _timer = xTimerCreate(
         /* Just a text name, not used by the RTOS
        kernel. */
        "EnterProductNumber",
        /* The timer period in ticks, must be
        greater than 0. */
        pdMS_TO_TICKS(10*1000),
        /* The timers will auto-reload themselves
        when they expire. */
        pdFALSE,
        /* The ID is used to store a count of the
        number of times the timer has expired, which
        is initialised to 0. */
        ( void * ) 0,
        /* Each timer calls the same callback when
        it expires. */
        keyTimeoutCallBack
    );
}

void EnterProductNumber::initialize() {
    // init data
    _data.clear();
    _data["state"] = "EnterProductNumber";
    _data["param_0"] = "000";

    //key timout start
    xTimerStart(_timer, 0);
}

EnterProductNumber* EnterProductNumber::getInstance() {
    static EnterProductNumber singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* EnterProductNumber::pressKey(const char key) {
    if ( xTimerIsTimerActive(_timer) == pdFALSE )
        return this;
    xTimerStop(_timer, 0);

    MachineState* next = this;
    switch ( key ) {
    case '#': {
        int n = std::stoi(_data["param_0"])-1;
        if ( n+1 == _database->getPasswordOfSystemManagement() ){
            next = EnterPasswordOfSystemSetting::getInstance();
        } else if ( 0 <= n && n < _database->getNumberOfColumns() ) {
            int total_quantity = _database->getQuantity(n) + _database->getAdditional(n);
            if (total_quantity > 0) {
                next =InputMoney::getInstance(n);
            } else {
                next = EnterProductNumberNoGoods::getInstance();
            }
        } else {
            next = EnterProductNumberNoGoods::getInstance();
        }
        break;}
    case '*': {
        next = Selling::getInstance();
        break;}
    default: {//1~9
        std::string &param_0 = _data["param_0"];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        xTimerStart(_timer, 0);
        break;}
    }
    return next;
}

MachineState* EnterProductNumber::timeout(const int signal) {
    return Selling::getInstance();
}
