#include "Math.h"
#include <assert.h>
namespace Core::Math {
	Matrix3f::Matrix3f() : mBuffer()
	{
		mBuffer.fill(0.0f);
	}
	Matrix3f::Matrix3f(const std::array<float, 9>& buffer) : mBuffer(buffer)
	{
	}


	const float* Matrix3f::getBuffer() const noexcept {
		return mBuffer.data();
	}

	float Matrix3f::constAt(size_t x, size_t y) const {
		assert(x < 3 && y < 3);
		return mBuffer[y * 3 + x];
	}

	float& Matrix3f::at(size_t x, size_t y) noexcept {
		assert(x < 3 && y < 3);
		return mBuffer[y * 3 + x];
	}

	float Matrix3f::determinant() const noexcept {
		return mBuffer[0] * (mBuffer[4] * mBuffer[8] - mBuffer[5] * mBuffer[7])
			- mBuffer[1] * (mBuffer[3] * mBuffer[8] - mBuffer[5] * mBuffer[6])
			+ mBuffer[2] * (mBuffer[3] * mBuffer[7] - mBuffer[4] * mBuffer[6]);
	}

	Matrix3f Matrix3f::getInverse() const {
		float det = determinant();
		assert(std::fabs(det) >= FLT_EPSILON * 1e5);
		if (std::fabs(det) >= FLT_EPSILON * 1e5) {
			return Matrix3f();
		}
		float invDet = 1.0f / det;
		Matrix3f inv;
		inv.mBuffer = {
			invDet * (mBuffer[4] * mBuffer[8] - mBuffer[5] * mBuffer[7]),
			invDet * (mBuffer[2] * mBuffer[7] - mBuffer[1] * mBuffer[8]),
			invDet * (mBuffer[1] * mBuffer[5] - mBuffer[2] * mBuffer[4]),
			invDet * (mBuffer[5] * mBuffer[6] - mBuffer[3] * mBuffer[8]),
			invDet * (mBuffer[0] * mBuffer[8] - mBuffer[2] * mBuffer[6]),
			invDet * (mBuffer[2] * mBuffer[3] - mBuffer[0] * mBuffer[5]),
			invDet * (mBuffer[3] * mBuffer[7] - mBuffer[4] * mBuffer[6]),
			invDet * (mBuffer[1] * mBuffer[6] - mBuffer[0] * mBuffer[7]),
			invDet * (mBuffer[0] * mBuffer[4] - mBuffer[1] * mBuffer[3])
		};
		return inv;
	}

	Vec3f Matrix3f::getRow(int index) const {
		assert(index >= 0 && index < 3);
		return Vec3f{ mBuffer[index * 3], mBuffer[index * 3 + 1], mBuffer[index * 3 + 2] };
	}

	Vec3f Matrix3f::getCol(int index) const {
		assert(index >= 0 && index < 3);
		return Vec3f{ mBuffer[index], mBuffer[index + 3], mBuffer[index + 6] };
	}

	Matrix3f Matrix3f::transpose() const noexcept {

		return Matrix3f({
			mBuffer[0], mBuffer[3], mBuffer[6],
			mBuffer[1], mBuffer[4], mBuffer[7],
			mBuffer[2], mBuffer[5], mBuffer[8]
			}
		);
	}



	Matrix3f operator+(const Matrix3f& A, const Matrix3f& B) {
		Matrix3f result;
		for (size_t i = 0; i < 9; ++i) {
			result.mBuffer[i] = A.mBuffer[i] + B.mBuffer[i];
		}
		return result;
	}

	Matrix3f operator-(const Matrix3f& A, const Matrix3f& B) {
		Matrix3f result;
		for (size_t i = 0; i < 9; ++i) {
			result.mBuffer[i] = A.mBuffer[i] - B.mBuffer[i];
		}
		return result;
	}

	Matrix3f operator*(const Matrix3f& A, float a) {
		Matrix3f result;
		for (size_t i = 0; i < 9; ++i) {
			result.mBuffer[i] = A.mBuffer[i] * a;
		}
		return result;
	}

	Matrix3f operator*(const Matrix3f& A, const Matrix3f& B) {
		std::array<float, 9> buffer = {
			A.mBuffer[0] * B.mBuffer[0] + A.mBuffer[1] * B.mBuffer[3] + A.mBuffer[2] * B.mBuffer[6],
			A.mBuffer[0] * B.mBuffer[1] + A.mBuffer[1] * B.mBuffer[4] + A.mBuffer[2] * B.mBuffer[7],
			A.mBuffer[0] * B.mBuffer[2] + A.mBuffer[1] * B.mBuffer[5] + A.mBuffer[2] * B.mBuffer[8],

			A.mBuffer[3] * B.mBuffer[0] + A.mBuffer[4] * B.mBuffer[3] + A.mBuffer[5] * B.mBuffer[6],
			A.mBuffer[3] * B.mBuffer[1] + A.mBuffer[4] * B.mBuffer[4] + A.mBuffer[5] * B.mBuffer[7],
			A.mBuffer[3] * B.mBuffer[2] + A.mBuffer[4] * B.mBuffer[5] + A.mBuffer[5] * B.mBuffer[8],

			A.mBuffer[6] * B.mBuffer[0] + A.mBuffer[7] * B.mBuffer[3] + A.mBuffer[8] * B.mBuffer[6],
			A.mBuffer[6] * B.mBuffer[1] + A.mBuffer[7] * B.mBuffer[4] + A.mBuffer[8] * B.mBuffer[7],
			A.mBuffer[6] * B.mBuffer[2] + A.mBuffer[7] * B.mBuffer[5] + A.mBuffer[8] * B.mBuffer[8]
		};

		return Matrix3f(buffer);
	}

	Vec3f operator*(const Matrix3f& A, const Vec3f& b) {
		return Vec3f(
			A.mBuffer[0] * b.x + A.mBuffer[1] * b.y + A.mBuffer[2] * b.z,
			A.mBuffer[3] * b.x + A.mBuffer[4] * b.y + A.mBuffer[5] * b.z,
			A.mBuffer[6] * b.x + A.mBuffer[7] * b.y + A.mBuffer[8] * b.z
		);
	}
	Matrix3f operator*(const Vec3f& b, const Matrix3f& A)
	{
		std::array<float, 9> buffer = {
			b.x * A.mBuffer[0] + b.y * A.mBuffer[3] + b.z * A.mBuffer[6],
			b.x * A.mBuffer[1] + b.y * A.mBuffer[4] + b.z * A.mBuffer[7],
			b.x * A.mBuffer[2] + b.y * A.mBuffer[5] + b.z * A.mBuffer[8],
		};

		return Matrix3f(buffer);
	}
	Matrix2f::Matrix2f() {
		mBuffer.fill(0.0f);
	}

	const float* Matrix2f::getBuffer() const noexcept {
		return mBuffer.data();
	}

	float Matrix2f::constAt(size_t x, size_t y) const {
		assert(x < 2 && y < 2);
		return mBuffer[y * 2 + x];
	}

	float& Matrix2f::at(size_t x, size_t y) noexcept {
		assert(x < 2 && y < 2);
		return mBuffer[y * 2 + x];
	}

	float Matrix2f::determinant() const noexcept {
		return mBuffer[0] * mBuffer[3] - mBuffer[1] * mBuffer[2];
	}

	Matrix2f Matrix2f::getInverse() const {
		float det = determinant();
		assert(std::fabs(det) >= FLT_EPSILON * 1e5);
		if (std::fabs(det) >= FLT_EPSILON * 1e5) {
			return Matrix2f();
		}
		Matrix2f inv;
		inv.mBuffer[0] = mBuffer[3] / det;
		inv.mBuffer[1] = -mBuffer[1] / det;
		inv.mBuffer[2] = -mBuffer[2] / det;
		inv.mBuffer[3] = mBuffer[0] / det;
		return inv;
	}

	Vec2f Matrix2f::getRow(int index) const {
		assert(index >= 0 && index < 2);
		return Vec2f(mBuffer[index * 2], mBuffer[index * 2 + 1]);
	}

	Vec2f Matrix2f::getCol(int index) const {
		assert(index >= 0 && index < 2);
		return Vec2f(mBuffer[index], mBuffer[index + 2]);
	}

	Matrix2f Matrix2f::transpose() const noexcept {
		return Matrix2f({ mBuffer[0], mBuffer[2], mBuffer[1], mBuffer[3] });
	}


	Matrix2f operator+(const Matrix2f& A, const Matrix2f& B) {
		Matrix2f result;
		result.mBuffer[0] = A.mBuffer[0] + B.mBuffer[0];
		result.mBuffer[1] = A.mBuffer[1] + B.mBuffer[1];
		result.mBuffer[2] = A.mBuffer[2] + B.mBuffer[2];
		result.mBuffer[3] = A.mBuffer[3] + B.mBuffer[3];
		return result;
	}

	Matrix2f operator-(const Matrix2f& A, const Matrix2f& B) {
		Matrix2f result;
		result.mBuffer[0] = A.mBuffer[0] - B.mBuffer[0];
		result.mBuffer[1] = A.mBuffer[1] - B.mBuffer[1];
		result.mBuffer[2] = A.mBuffer[2] - B.mBuffer[2];
		result.mBuffer[3] = A.mBuffer[3] - B.mBuffer[3];
		return result;
	}

	Matrix2f operator*(const Matrix2f& A, float a) {
		Matrix2f result;
		result.mBuffer[0] = A.mBuffer[0] * a;
		result.mBuffer[1] = A.mBuffer[1] * a;
		result.mBuffer[2] = A.mBuffer[2] * a;
		result.mBuffer[3] = A.mBuffer[3] * a;
		return result;
	}

	Matrix2f operator*(const Matrix2f& A, const Matrix2f& B) {
		Matrix2f result;
		result.mBuffer[0] = A.mBuffer[0] * B.mBuffer[0] + A.mBuffer[1] * B.mBuffer[2];
		result.mBuffer[1] = A.mBuffer[0] * B.mBuffer[1] + A.mBuffer[1] * B.mBuffer[3];
		result.mBuffer[2] = A.mBuffer[2] * B.mBuffer[0] + A.mBuffer[3] * B.mBuffer[2];
		result.mBuffer[3] = A.mBuffer[2] * B.mBuffer[1] + A.mBuffer[3] * B.mBuffer[3];
		return result;
	}

	Vec2f operator*(const Matrix2f& A, const Vec2f& b) {
		return Vec2f(
			A.mBuffer[0] * b.x + A.mBuffer[1] * b.y,
			A.mBuffer[2] * b.x + A.mBuffer[3] * b.y
		);
	}
	const float* Matrix4f::getBuffer() const noexcept
	{
		return mBuffer.data();
	}

	float Matrix4f::constAt(size_t x, size_t y) const
	{
		return 0.0f;
	}
	Matrix4f::Matrix4f(const std::array<float, 16>& buffer) : mBuffer(buffer)
	{
	}
	Matrix4f::Matrix4f()
	{
		mBuffer.fill(0.f);
	}
	// Element Access
	float& Matrix4f::at(size_t x, size_t y) noexcept {
		assert(x < 4 && y < 4);
		return mBuffer[y * 4 + x];
	}

	float Matrix4f::constAt(size_t x, size_t y) const {
		assert(x < 4 && y < 4);
		return mBuffer[y * 4 + x];
	}


	Matrix4f Matrix4f::getInverse() const {

		float det = determinant();
		assert(std::fabs(det) >= FLT_EPSILON * 1e5);

		if (std::fabs(det) >= FLT_EPSILON * 1e5) {
			return Matrix4f();
		}

		// Compute the minors (determinants of the 3x3 submatrices)
		float m00 = mBuffer[0], m01 = mBuffer[1], m02 = mBuffer[2], m03 = mBuffer[3];
		float m10 = mBuffer[4], m11 = mBuffer[5], m12 = mBuffer[6], m13 = mBuffer[7];
		float m20 = mBuffer[8], m21 = mBuffer[9], m22 = mBuffer[10], m23 = mBuffer[11];
		float m30 = mBuffer[12], m31 = mBuffer[13], m32 = mBuffer[14], m33 = mBuffer[15];

		// 3x3 Determinants (minors)
		float det3x3_0 = (m11 * (m22 * m33 - m23 * m32)) - (m12 * (m21 * m33 - m23 * m31)) + (m13 * (m21 * m32 - m22 * m31));
		float det3x3_1 = (m10 * (m22 * m33 - m23 * m32)) - (m12 * (m20 * m33 - m23 * m30)) + (m13 * (m20 * m32 - m22 * m30));
		float det3x3_2 = (m10 * (m21 * m33 - m23 * m31)) - (m11 * (m20 * m33 - m23 * m30)) + (m13 * (m20 * m31 - m21 * m30));
		float det3x3_3 = (m10 * (m21 * m32 - m22 * m31)) - (m11 * (m20 * m32 - m22 * m30)) + (m12 * (m20 * m31 - m21 * m30));

		float det3x3_4 = (m01 * (m22 * m33 - m23 * m32)) - (m02 * (m21 * m33 - m23 * m31)) + (m03 * (m21 * m32 - m22 * m31));
		float det3x3_5 = (m00 * (m22 * m33 - m23 * m32)) - (m02 * (m20 * m33 - m23 * m30)) + (m03 * (m20 * m32 - m22 * m30));
		float det3x3_6 = (m00 * (m21 * m33 - m23 * m31)) - (m01 * (m20 * m33 - m23 * m30)) + (m03 * (m20 * m31 - m21 * m30));
		float det3x3_7 = (m00 * (m21 * m32 - m22 * m31)) - (m01 * (m20 * m32 - m22 * m30)) + (m02 * (m20 * m31 - m21 * m30));

		float det3x3_8 = (m01 * (m12 * m33 - m13 * m32)) - (m02 * (m11 * m33 - m13 * m31)) + (m03 * (m11 * m32 - m12 * m31));
		float det3x3_9 = (m00 * (m12 * m33 - m13 * m32)) - (m02 * (m10 * m33 - m13 * m30)) + (m03 * (m10 * m32 - m12 * m30));
		float det3x3_10 = (m00 * (m11 * m33 - m13 * m31)) - (m01 * (m10 * m33 - m13 * m30)) + (m03 * (m10 * m31 - m11 * m30));
		float det3x3_11 = (m00 * (m11 * m32 - m12 * m31)) - (m01 * (m10 * m32 - m12 * m30)) + (m02 * (m10 * m31 - m11 * m30));

		float det3x3_12 = (m01 * (m12 * m23 - m13 * m22)) - (m02 * (m11 * m23 - m13 * m21)) + (m03 * (m11 * m22 - m12 * m21));
		float det3x3_13 = (m00 * (m12 * m23 - m13 * m22)) - (m02 * (m10 * m23 - m13 * m20)) + (m03 * (m10 * m22 - m12 * m20));
		float det3x3_14 = (m00 * (m11 * m23 - m13 * m21)) - (m01 * (m10 * m23 - m13 * m20)) + (m03 * (m10 * m21 - m11 * m20));
		float det3x3_15 = (m00 * (m11 * m22 - m12 * m21)) - (m01 * (m10 * m22 - m12 * m20)) + (m02 * (m10 * m21 - m11 * m20));


		Matrix4f cofactorMatrix = Matrix4f({
			det3x3_0, -det3x3_1, det3x3_2, -det3x3_3,
			-det3x3_4, det3x3_5, -det3x3_6, det3x3_7,
			det3x3_8, -det3x3_9, det3x3_10, -det3x3_11,
			-det3x3_12, det3x3_13, -det3x3_14, det3x3_15
			});

		// Transpose the cofactor matrix to get the adjugate
		Matrix4f adjugate = cofactorMatrix.transpose();

		// Divide the adjugate matrix by the determinant to get the inverse
		Matrix4f inverse = adjugate * (1.0f / det);

		return inverse;
	}


	// Row and Column Retrieval
	Vec4f Matrix4f::getRow(int index) const {
		assert(index >= 0 && index < 4);
		return Vec4f(mBuffer[index * 4], mBuffer[index * 4 + 1], mBuffer[index * 4 + 2], mBuffer[index * 4 + 3]);
	}

	Vec4f Matrix4f::getCol(int index) const {
		assert(index >= 0 && index < 4);
		return Vec4f(mBuffer[index], mBuffer[index + 4], mBuffer[index + 8], mBuffer[index + 12]);
	}

	Matrix4f Matrix4f::transpose() const noexcept {
		// Swap rows with columns
		return Matrix4f(
			{
				mBuffer[0], mBuffer[4], mBuffer[8], mBuffer[12],
				mBuffer[1], mBuffer[5], mBuffer[9], mBuffer[13],
				mBuffer[2], mBuffer[6], mBuffer[10], mBuffer[14],
				mBuffer[3], mBuffer[7], mBuffer[11], mBuffer[15]
			}
		);
	}

	// Operator Overloads
	Matrix4f operator+(const Matrix4f& A, const Matrix4f& B) {
		return Matrix4f({
			A.mBuffer[0] + B.mBuffer[0], A.mBuffer[1] + B.mBuffer[1], A.mBuffer[2] + B.mBuffer[2], A.mBuffer[3] + B.mBuffer[3],
			A.mBuffer[4] + B.mBuffer[4], A.mBuffer[5] + B.mBuffer[5], A.mBuffer[6] + B.mBuffer[6], A.mBuffer[7] + B.mBuffer[7],
			A.mBuffer[8] + B.mBuffer[8], A.mBuffer[9] + B.mBuffer[9], A.mBuffer[10] + B.mBuffer[10], A.mBuffer[11] + B.mBuffer[11],
			A.mBuffer[12] + B.mBuffer[12], A.mBuffer[13] + B.mBuffer[13], A.mBuffer[14] + B.mBuffer[14], A.mBuffer[15] + B.mBuffer[15]
			});
	}

	Matrix4f operator-(const Matrix4f& A, const Matrix4f& B) {
		return Matrix4f({
			A.mBuffer[0] - B.mBuffer[0], A.mBuffer[1] - B.mBuffer[1], A.mBuffer[2] - B.mBuffer[2], A.mBuffer[3] - B.mBuffer[3],
			A.mBuffer[4] - B.mBuffer[4], A.mBuffer[5] - B.mBuffer[5], A.mBuffer[6] - B.mBuffer[6], A.mBuffer[7] - B.mBuffer[7],
			A.mBuffer[8] - B.mBuffer[8], A.mBuffer[9] - B.mBuffer[9], A.mBuffer[10] - B.mBuffer[10], A.mBuffer[11] - B.mBuffer[11],
			A.mBuffer[12] - B.mBuffer[12], A.mBuffer[13] - B.mBuffer[13], A.mBuffer[14] - B.mBuffer[14], A.mBuffer[15] - B.mBuffer[15]
			});
	}

	Matrix4f operator*(const Matrix4f& A, float a) {
		return Matrix4f({
			A.mBuffer[0] * a, A.mBuffer[1] * a, A.mBuffer[2] * a, A.mBuffer[3] * a,
			A.mBuffer[4] * a, A.mBuffer[5] * a, A.mBuffer[6] * a, A.mBuffer[7] * a,
			A.mBuffer[8] * a, A.mBuffer[9] * a, A.mBuffer[10] * a, A.mBuffer[11] * a,
			A.mBuffer[12] * a, A.mBuffer[13] * a, A.mBuffer[14] * a, A.mBuffer[15] * a
			});
	}

	// Matrix Multiplication
	Matrix4f operator*(const Matrix4f& A, const Matrix4f& B) {
		return Matrix4f({
			A.mBuffer[0] * B.mBuffer[0] + A.mBuffer[1] * B.mBuffer[4] + A.mBuffer[2] * B.mBuffer[8] + A.mBuffer[3] * B.mBuffer[12],
			A.mBuffer[0] * B.mBuffer[1] + A.mBuffer[1] * B.mBuffer[5] + A.mBuffer[2] * B.mBuffer[9] + A.mBuffer[3] * B.mBuffer[13],
			A.mBuffer[0] * B.mBuffer[2] + A.mBuffer[1] * B.mBuffer[6] + A.mBuffer[2] * B.mBuffer[10] + A.mBuffer[3] * B.mBuffer[14],
			A.mBuffer[0] * B.mBuffer[3] + A.mBuffer[1] * B.mBuffer[7] + A.mBuffer[2] * B.mBuffer[11] + A.mBuffer[3] * B.mBuffer[15],

			A.mBuffer[4] * B.mBuffer[0] + A.mBuffer[5] * B.mBuffer[4] + A.mBuffer[6] * B.mBuffer[8] + A.mBuffer[7] * B.mBuffer[12],
			A.mBuffer[4] * B.mBuffer[1] + A.mBuffer[5] * B.mBuffer[5] + A.mBuffer[6] * B.mBuffer[9] + A.mBuffer[7] * B.mBuffer[13],
			A.mBuffer[4] * B.mBuffer[2] + A.mBuffer[5] * B.mBuffer[6] + A.mBuffer[6] * B.mBuffer[10] + A.mBuffer[7] * B.mBuffer[14],
			A.mBuffer[4] * B.mBuffer[3] + A.mBuffer[5] * B.mBuffer[7] + A.mBuffer[6] * B.mBuffer[11] + A.mBuffer[7] * B.mBuffer[15],

			A.mBuffer[8] * B.mBuffer[0] + A.mBuffer[9] * B.mBuffer[4] + A.mBuffer[10] * B.mBuffer[8] + A.mBuffer[11] * B.mBuffer[12],
			A.mBuffer[8] * B.mBuffer[1] + A.mBuffer[9] * B.mBuffer[5] + A.mBuffer[10] * B.mBuffer[9] + A.mBuffer[11] * B.mBuffer[13],
			A.mBuffer[8] * B.mBuffer[2] + A.mBuffer[9] * B.mBuffer[6] + A.mBuffer[10] * B.mBuffer[10] + A.mBuffer[11] * B.mBuffer[14],
			A.mBuffer[8] * B.mBuffer[3] + A.mBuffer[9] * B.mBuffer[7] + A.mBuffer[10] * B.mBuffer[11] + A.mBuffer[11] * B.mBuffer[15],

			A.mBuffer[12] * B.mBuffer[0] + A.mBuffer[13] * B.mBuffer[4] + A.mBuffer[14] * B.mBuffer[8] + A.mBuffer[15] * B.mBuffer[12],
			A.mBuffer[12] * B.mBuffer[1] + A.mBuffer[13] * B.mBuffer[5] + A.mBuffer[14] * B.mBuffer[9] + A.mBuffer[15] * B.mBuffer[13],
			A.mBuffer[12] * B.mBuffer[2] + A.mBuffer[13] * B.mBuffer[6] + A.mBuffer[14] * B.mBuffer[10] + A.mBuffer[15] * B.mBuffer[14],
			A.mBuffer[12] * B.mBuffer[3] + A.mBuffer[13] * B.mBuffer[7] + A.mBuffer[14] * B.mBuffer[11] + A.mBuffer[15] * B.mBuffer[15]
			});
	}

	Identity3::Identity3()
	{
		mBuffer[0] = 1;
		mBuffer[4] = 1;
		mBuffer[8] = 1;

	}
	Identity4::Identity4()
	{
		mBuffer[0] = 1;
		mBuffer[5] = 1;
		mBuffer[10] = 1;
		mBuffer[15] = 1;
	}
	float& Translate2D::getDx()
	{
		return mBuffer.at(2);
	}
	float& Translate2D::getDy()
	{
		return mBuffer.at(5);
	}
	float& Translate3D::getDx()
	{
		return mBuffer.at(3);
	}
	float& Translate3D::getDy()
	{
		return mBuffer.at(7);
	}
	float& Translate3D::getDz()
	{
		return mBuffer.at(11);
	}
	void Rotation2D::setAngle(float angle)  noexcept
	{
		mBuffer[0] = cos(angle);
		mBuffer[1] = -sin(angle);
		mBuffer[2] = sin(angle);
		mBuffer[3] = cos(angle);
	}

	// Constructor for ZAxisRotation3D that sets the initial angle
	ZAxisRotation3D::ZAxisRotation3D(float angle) {
		setAngle(angle);
	}

	// Set the angle for rotation around the Z-axis
	void ZAxisRotation3D::setAngle(float angle) noexcept {
		mBuffer[0] = cos(angle); mBuffer[1] = -sin(angle); mBuffer[2] = 0; mBuffer[3] = 0;
		mBuffer[4] = sin(angle); mBuffer[5] = cos(angle);  mBuffer[6] = 0; mBuffer[7] = 0;
		
		mBuffer[8] = 0; mBuffer[9] = 0; mBuffer[10] = 1; mBuffer[11] = 0;
		mBuffer[12] = 0;mBuffer[13] = 0;mBuffer[14] = 0; mBuffer[15] = 1;
		mAngle = angle;
	}

	// Constructor for YAxisRotation3D that sets the initial angle
	YAxisRotation3D::YAxisRotation3D(float angle) {
		setAngle(angle);
	}

	// Set the angle for rotation around the Y-axis
	void YAxisRotation3D::setAngle(float angle)  noexcept {
		mBuffer[0] = cos(angle); mBuffer[1] = 0; mBuffer[2] = sin(angle); mBuffer[3] = 0;
		mBuffer[4] = 0;			 mBuffer[5] = 1; mBuffer[6] = 0;		  mBuffer[7] = 0;
		mBuffer[8] = -sin(angle);mBuffer[9] = 0; mBuffer[10] = cos(angle);mBuffer[11] = 0;
		mBuffer[12] = 0;		 mBuffer[13] = 0;mBuffer[14] = 0;		  mBuffer[15] = 1;
		mAngle = angle;
	}

	inline float YAxisRotation3D::getAngle() const noexcept
	{
		return mAngle;
	}

	// Constructor for XAxisRotation3D that sets the initial angle
	XAxisRotation3D::XAxisRotation3D(float angle) {
		setAngle(angle);
	}

	// Set the angle for rotation around the X-axis
	void XAxisRotation3D::setAngle(float angle)  noexcept {
		mBuffer[0] = 1;	 mBuffer[1] = 0;			mBuffer[2] = 0;			 mBuffer[3] = 0;
		mBuffer[8] = 0;	 mBuffer[9] = sin(angle);   mBuffer[10] = cos(angle);mBuffer[11] = 0;
		mBuffer[12] = 0; mBuffer[13] = 0;			mBuffer[14] = 0;		 mBuffer[15] = 1;
	}

	inline float ZAxisRotation3D::getAngle() const noexcept
	{
		return mAngle;
	}
	Translate2D::Translate2D(float dx, float dy) : Identity3() {
		mBuffer[2] = dx;
		mBuffer[5] = dy;
		mBuffer[8] = 1;
	}
	Translate3D::Translate3D(float dx, float dy, float dz) : Identity4() {
		mBuffer[3] = dx;
		mBuffer[7] = dy;
		mBuffer[11] = dz;
		mBuffer[15] = 1;
	}
}

