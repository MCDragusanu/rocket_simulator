#include "Camera.h"



Core::Gfx::CameraSystem::OrthographicCamera::OrthographicCamera(float top, float left, float bottom, float right , float far, float near):
	 mProjectionMatrix(Core::Math::Identity4()),
	 mViewMatrix(Core::Math::Identity4()),
	 mVPMatrix(Core::Math::Identity4())

{
	
	mProjectionMatrix.at(0, 0) = 2.0f / (right - left);
	mProjectionMatrix.at(0, 3) = - (right + left) / (right - left);
	mProjectionMatrix.at(1, 1) = 2.0f / (top - bottom);
	mProjectionMatrix.at(1, 3) =  - (top + bottom) / (top - bottom);
	mProjectionMatrix.at(2, 2) = -2.0f / (far - near);
	mProjectionMatrix.at(2, 3) = -(far + near) / (far - near);

	mVPMatrix = mProjectionMatrix * mViewMatrix;
}
