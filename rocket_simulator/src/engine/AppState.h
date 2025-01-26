// State.h
#pragma once

namespace Core{
    class Application;  // Forward declaration of the Application class

    // The abstract base class for all states
    class AppState {
    public:
        virtual ~AppState() = default;
        virtual void handle() = 0; // Abstract method to handle the logic for the state
    };
}
