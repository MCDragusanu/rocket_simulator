#pragma once

#include "../../../../rocket_simulator/src/engine/AppState.h"

class DestroyState : public Core::AppState {
public:
    DestroyState(Core::Application& app);
    void handle() override;
    ~DestroyState() {};
private:
    Core::Application& mApp;
};


