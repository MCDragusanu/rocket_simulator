#pragma once

#include "../../../../rocket_simulator/src/engine/AppState.h"
class ErrorState : public Core::AppState {
public:
    ErrorState(Core::Application& app);
    void handle() override;
    ~ErrorState() {};
private:
    Core::Application& mApp;
};



