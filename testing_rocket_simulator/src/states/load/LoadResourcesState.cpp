#include "LoadResourcesState.h"
#include <iostream>
#include <memory>
#include "../../../../rocket_simulator/src/engine/AppState.h"
#include "../../app/TestApplication.h"
#include "../bind/BindResourcesState.h"
LoadResourcesState::LoadResourcesState(Core::Application& app):mApp(app){}

void LoadResourcesState::handle()
{
    std::cout << "Loading Resources..." << std::endl;
    if (mApp.load_resources()) {
        mApp.setState(std::make_unique<BindResources>(this->mApp)); // Transition to LoadResourcesState
    }
    else {
        std::cerr << "Loading failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}
