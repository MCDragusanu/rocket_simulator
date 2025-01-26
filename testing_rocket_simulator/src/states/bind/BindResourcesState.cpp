
#include "BindResourcesState.h"
#include "../../../../rocket_simulator/src/engine/AppState.h"
#include "../../app/TestApplication.h"
#include "../commit/CommitResourcesState.h"

BindResources::BindResources(Core::Application& app) :mApp(app) {}

void BindResources::handle()
{
    std::cout << "Binding Resources..." << std::endl;
    if (mApp.bind_resources()) {
        mApp.setState(std::make_unique<CommitResourcesState>(mApp)); // Transition to LoadResourcesState
    }
    else {
        std::cerr << "Binding failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}


