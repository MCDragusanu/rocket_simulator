#pragma once
#pragma once
#include <memory>

namespace Core{
    class AppState;  // Forward declaration of the State class

    // The abstract base class for the Application
    class Application {
    public:
        virtual ~Application() = default;

        // This method transitions the application to a new state
        virtual void setState(std::unique_ptr<AppState> newState) = 0;

        virtual void start() = 0;
        // Starts the application (state machine)
        virtual void run() = 0;

        // State transition and lifecycle methods
        virtual bool is_running() = 0;
        virtual bool initialize() = 0;
        virtual bool load_resources() = 0;
        virtual bool bind_resources() = 0;
        virtual bool commit_resources() = 0;
        virtual bool render() = 0;
        virtual bool update() = 0;
        virtual bool destroy() = 0;
    };
}

