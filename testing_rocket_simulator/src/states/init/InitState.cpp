#include "InitState.h"
#include "../../app/TestApplication.h"
#include "../load/LoadResourcesState.h"

InitState::InitState(Core::Application& app):mApp(app){}

void InitState::handle()
{
    std::cout << "Initializing..." << std::endl;
    if (mApp.initialize()) {
        mApp.setState(std::make_unique<LoadResourcesState>(mApp)); // Transition to LoadResourcesState
    }
    else {
        std::cerr << "Initialization failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}


