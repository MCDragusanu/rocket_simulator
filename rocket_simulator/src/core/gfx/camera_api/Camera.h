#include <iostream>
#include "../../math/Math.h"
/**
 * @namespace Core::Gfx::CameraSystem
 * @brief Contains camera-related functionality for the graphics system.
 */
namespace Core::Gfx::CameraSystem {

    /**
     * @struct CameraState
     * @brief Represents a read-only object that stores the current state of the camera;
     */
    struct CameraState {
        const Core::Math::Matrix4f*  pBuffer;                   /// Pointer to the matrix data.
        const Core::Math::Vec3f*     cameraPosition;            /// Pointer to a vector describing the camera position in space
        const Core::Math::Vec3f*     eulerAngles;               /// Pointer to a vector describing the camera rotation in euler angles
    };

    /**
     * @class Camera
     * @brief Abstract base class for camera handling in the graphics system.
     */
    class Camera {
    public:
        /**
         * @brief Gets the field of view (FOV) of the camera.
         * @return The FOV in degrees.
         */
        virtual float getFOV() const noexcept = 0;

        /**
         * @brief Gets the aspect ratio of the camera.
         * @return The aspect ratio (width / height).
         */
        virtual float getAspectRatio() const noexcept = 0;

        /**
         * @brief Sets the camera's position in 3D space.
         * @param position The new position as a 3D vector.
         */
        virtual void setPosition(const Core::Math::Vec3f& position) const noexcept = 0;


        virtual const CameraState& getCameraState() const noexcept = 0;

    protected:
        Core::Math::Vec3f mPosition;            /// Camera position in 3D space.
        Core::Math::Vec3f mEulerAngles;         /// Camera Rotation in Euler Angles
        Core::Math::Matrix4f mProjectionMatrix; /// Projection matrix.
        Core::Math::Matrix4f mViewMatrix;       /// View matrix.
        Core::Math::Matrix4f mVPMatrix;         /// View-Projection matrix.
    };

}
