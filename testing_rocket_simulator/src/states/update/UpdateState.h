#pragma once
#include "../../../../rocket_simulator/src/engine/AppState.h"

class UpdateState : public Core::AppState {
public:
    UpdateState(Core::Application& app);
    void handle() override;
    ~UpdateState() {};
private:
    Core::Application& mApp;
};