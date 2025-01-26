#include "UpdateState.h"
#include "../../app/TestApplication.h"
#include "../render/RenderState.h"
#include "../../../../rocket_simulator/src/engine/AppState.h"

UpdateState::UpdateState(Core::Application& app) :mApp(app) {}

void UpdateState::handle()
{
    std::cout << "Updating..." << std::endl;
    if (mApp.update()) {
        mApp.setState(std::make_unique<RenderState>(mApp)); // Transition to LoadResourcesState
    }
    else {
        std::cerr << "Initialization failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}