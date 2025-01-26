#include "DestroyState.h"
#include "../../app/TestApplication.h"
#include "../commit/CommitResourcesState.h"
#include "../../../../rocket_simulator/src/engine/AppState.h"
DestroyState::DestroyState(Core::Application& app) :mApp(app) {}

void DestroyState::handle()
{
    std::cout << "Destroying..." << std::endl;
    if (mApp.destroy()) {
        std::cout << "App has been cleaned and destroyed" << "\n";
    }
    else {
        std::cerr << "Initialization failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}


