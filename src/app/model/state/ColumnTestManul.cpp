#include "ColumnTestManul.h"

#include "WorkingTest.h"

void ColumnTestManul::initialize() {
    // init data
    _data.clear();
    _data["state"] = "ColumnTestManul";
    _data["param_0"] = "end";
    _data["param_1"] = "000";
}

ColumnTestManul* ColumnTestManul::getInstance() {
    static ColumnTestManul singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* ColumnTestManul::pressKey(const char key) {
    MachineState* next = this;
    _data["param_0"] = "end";
    switch ( key ) {
    case '#':{
        int column = std::stoi(_data["param_1"]) - 1;
        if (0 <= column && column < _database->getNumberOfColumns()) {
            _data["param_0"] = "start";
        }
        break;}
    case '*':
        next = WorkingTest::getInstance();
        break;
    default: {//1~9
        std::string &param_1 = _data["param_1"];
        rotate(param_1.begin(), param_1.begin()+1, param_1.end());
        param_1[param_1.length()-1] = key;
        break;}
    }
    return next;
}
