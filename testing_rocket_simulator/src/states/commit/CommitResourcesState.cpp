#include "CommitResourcesState.h"
#include "../../app/TestApplication.h"
#include "../update/UpdateState.h"
#include "../../../../rocket_simulator/src/engine/AppState.h"
CommitResourcesState::CommitResourcesState(Core::Application& app) :mApp(app) {}

void CommitResourcesState::handle()
{
    std::cout << "Commiting Resources..." << std::endl;
    if (mApp.commit_resources()) {
        mApp.setState(std::make_unique<UpdateState>(mApp)); // Transition to LoadResourcesState
    }
    else {
        std::cerr << "Commit failed failed." << std::endl;
        // Transition to ErrorState (not implemented here)
    }
}
