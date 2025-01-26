#pragma once

#include "../../../../rocket_simulator/src/engine/AppState.h"

class LoadResourcesState : public Core::AppState {
public:
    LoadResourcesState(Core::Application& app);
    void handle() override;
    ~LoadResourcesState() {};
private:
    Core::Application& mApp;
};