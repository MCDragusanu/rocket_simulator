#pragma once
#include "../../../../rocket_simulator/src/engine/AppState.h"

class RenderState : public Core::AppState {
public:
    RenderState(Core::Application& app);
    void handle() override;
    ~RenderState() {};
private:
    Core::Application& mApp;
};

