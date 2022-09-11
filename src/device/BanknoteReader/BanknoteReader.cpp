#include "BanknoteReader.h"

static void banknoteEventTask(void *params) {
    BanknoteReader* reader = (BanknoteReader*)params;
    while(1) {
        reader->notifyBillData();
    }
}

void BanknoteReader::notifyBillData() {
    int billdata = getBillData();
    for (auto cb : _buillDataCallbacks) {
        cb(billdata);
    }
}

void BanknoteReader::registerBillDataCallBack(std::function<void(const int)> billdata) {
    _buillDataCallbacks.push_back(billdata);
}

int BanknoteReader::initialized(const char* taskName) {
    enum {
        Priority = configMAX_PRIORITIES / 2 - 1,
    };

    xTaskCreate(banknoteEventTask, taskName, 512, this, Priority, &_eventTask);
    return 0;
}
