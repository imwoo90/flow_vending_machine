#pragma once

#include <MachineState.h>
#include <MachineData.h>

#include <FreeRTOS.h>
#include <timers.h>

class InputMoney : public MachineState {
private:
    int _inputMoney;
    int _column;
    TimerHandle_t _timer;
    InputMoney();
    virtual void initialize();
public:
    static InputMoney* getInstance(int column);
    virtual MachineState* pressKey(const char key);
    virtual MachineState* recognizeBanknote(const int banknote);
    virtual MachineState* timeout(const int signal);
};
