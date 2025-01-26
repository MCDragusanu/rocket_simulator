#pragma once
#include "../../../../rocket_simulator/src/engine/AppState.h"

class InitState : public Core::AppState {
public:
    InitState(Core::Application & app);
    void handle() override;
    ~InitState() {};
private:
    Core::Application& mApp;
};

