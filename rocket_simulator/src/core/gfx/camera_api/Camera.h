#include <iostream>
namespace Core::Gfx::CameraSystem{
	
	struct MatrixView {
		const float* pBuffer;
		size_t rowCount, columnCount;
	};


	class Camera {

	public:
		virtual const MatrixView& getMatrix() const noexcept = 0;
		virtual float getFOV()const noexcept = 0;
		virtual float getAspectRatio() const noexcept = 0;

	};
}