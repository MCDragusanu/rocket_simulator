
#include "../camera_api/Camera.h"
#include "../entity_api/Entity.h"
#include "../shaders_api/ShaderPipeline.h"

namespace Core::Gfx::SceneSystem {

    class Scene {
    public:
        virtual void loadScene() = 0;
        virtual void beginScene() = 0;
        virtual void releaseScene() = 0;
        virtual const std::string& getSceneName() const noexcept = 0;

        // Provides render data instead of rendering itself
        virtual const std::vector<RenderingSystem::RenderCommand*>& getRenderCommands() const {
            return commandList;
        }

        virtual const std::vector<EntitySystem::Entity*>& getEntities() const {
            return entityList;
        }

    protected:
        std::shared_ptr<Core::Gfx::CameraSystem::Camera> camera;
        std::shared_ptr<Core::Gfx::ShaderSystem::ShaderPipeline> shaderPipeline;
        std::vector<RenderingSystem::RenderCommand*> commandList;
        std::vector<EntitySystem::Entity*> entityList;
        std::string sceneName;
    };

}
