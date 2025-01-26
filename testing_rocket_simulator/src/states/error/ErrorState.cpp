#include "ErrorState.h"

#include "../../app/TestApplication.h"
#include "../load/LoadResourcesState.h"
#include "../../../../rocket_simulator/src/engine/AppState.h"
ErrorState::ErrorState(Core::Application& app) :mApp(app) {}

void ErrorState::handle()
{
    std::cout << "error state..." << std::endl;
    
    //to do implement this 
}