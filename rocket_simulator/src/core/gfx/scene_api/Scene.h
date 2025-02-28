#include "../camera_api/Camera.h"
#include <vector>

/**
 * @namespace Core::Gfx::SceneSystem
 * @brief Provides functionality for managing and rendering scenes.
 */
namespace Core::Gfx::SceneSystem {

    /**
     * @class Scene
     * @brief Represents a renderable scene in the graphics system.
     * @details It is the responsibility of the Scene to properly batch resources into appropriate render commands.
     */
    class Scene {
    public:
        /**
         * @brief Begins rendering the scene with the given camera state.
         * @param state The current camera state containing view and projection information.
         */
        virtual void beginScene(const CameraSystem::CameraState& state) = 0;

        /**
         * @brief Releases all resources associated with the scene.
         */
        virtual void releaseScene() = 0;

        /**
         * @brief Retrieves the name of the scene.
         * @return A reference to the scene name as a string.
         */
        virtual const std::string& getSceneName() const noexcept = 0;

    protected:
        /**
         * @brief Retrieves the list of render commands for the scene.
         * @return A reference to a vector of raw pointers representing render commands.
         * @note The scene is responsible for batching and organizing these commands correctly.
         */
        virtual const std::vector<void*>& getCommands() const noexcept = 0;
    };

}
