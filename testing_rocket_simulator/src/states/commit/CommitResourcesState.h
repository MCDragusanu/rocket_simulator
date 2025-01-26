#pragma once
#include "../../../../rocket_simulator/src/engine/AppState.h"

class CommitResourcesState : public Core::AppState {
public:
    CommitResourcesState(Core::Application& app);
    void handle() override;
    ~CommitResourcesState() {};
private:
    Core::Application& mApp;
};




