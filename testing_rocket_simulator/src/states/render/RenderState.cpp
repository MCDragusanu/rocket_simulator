#include "RenderState.h"
#include "../../app/TestApplication.h"
#include "../update/UpdateState.h"
#include "../../../../rocket_simulator/src/engine/AppState.h"
RenderState::RenderState(Core::Application& app) :mApp(app) {}

void RenderState::handle()
{
    std::cout << "Rendering..." << std::endl;
    if (mApp.render()) {
        mApp.setState(std::make_unique<UpdateState>(mApp)); // Transition to LoadResourcesState
    }
    else {
        std::cerr << "Render failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}