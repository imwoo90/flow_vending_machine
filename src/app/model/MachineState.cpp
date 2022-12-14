#include <MachineState.h>

std::function<void(const int)> MachineState::_timeoutCallback;
std::function<void(std::unordered_map<std::string, std::string>)> MachineState::_onChangedCallback;
std::unordered_map<std::string, std::string> MachineState::_data;
MachineData* MachineState::_database;