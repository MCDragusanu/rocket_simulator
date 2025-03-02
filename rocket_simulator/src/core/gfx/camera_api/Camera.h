#include <iostream>
#include "../../math/Math.h"
#include <numeric>
/**
 * @namespace Core::Gfx::CameraSystem
 * @brief Contains camera-related functionality for the graphics system.
 */
namespace Core::Gfx::CameraSystem {


    struct CameraState {
        const Core::Math::Matrix4f* viewProjectionMatrix;
    };


    class Camera {
    public:
        virtual float getFOV() const noexcept = 0;
        virtual float getAspectRatio() const noexcept = 0;
        virtual void  setPosition(const Core::Math::Vec3f& position) const noexcept = 0;
        virtual void  setRotation(const Core::Math::Vec3f& angle) const noexcept = 0;
        virtual const CameraState& getCameraState() const noexcept = 0;

    protected:
        virtual void update() = 0;
       
    };

    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float top, float left, float bottom, float right , float far , float near);
    protected:
        Core::Math::Matrix4f mProjectionMatrix; /// Projection matrix.
        Core::Math::Matrix4f mViewMatrix;       /// View matrix.The position of the camera
        Core::Math::Matrix4f mVPMatrix;         /// View-Projection matrix.

    };

}
