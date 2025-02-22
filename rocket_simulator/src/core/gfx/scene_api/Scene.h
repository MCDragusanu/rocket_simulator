#include "../camera_api/Camera.h"
#include <vector>

namespace Core::Gfx::SceneSystem {

	
	//it s the responsability of the Scene ton properly batch the resources
	class Scene {
		

	public:
		virtual void loadScene() = 0;
		virtual void bindScene() const = 0 ;
		virtual void beginScene(const CameraSystem::MatrixView& cameraView) = 0;
		virtual void releaseScene() = 0;

		virtual const std::string& getSceneName() const noexcept = 0;
	protected:
		virtual const std::vector< void* > & getCommands() const noexcept = 0;
	};
}