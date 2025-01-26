#pragma once

#include "../../../../rocket_simulator/src/engine/AppState.h"

class BindResources : public Core::AppState {
public:
    BindResources(Core::Application& app);
    void handle() override;
    ~BindResources() {};
private:
    Core::Application& mApp;
};