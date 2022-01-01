#include "Matrix3.hpp"
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>

namespace Calcda {

CALCDA Matrix3::Matrix3()
{
	for (std::size_t index = 0; index < 9; ++index) {
		value.data[index] = 0.0f;
	}
}

CALCDA Matrix3::Matrix3(const std::initializer_list<float> &List)
{
	std::size_t count = 0;
	std::size_t rowCount = 0;
	std::size_t colCount = 0;

	for (auto val : List) {
		value.matrix[rowCount][colCount] = val;

		++count;
		++colCount;

		if (colCount >= 3) {
			colCount = 0;

			++rowCount;
		}

		if (count >= 9) {
			break;
		}
	}

	for (; count < 9; ++count) {
		value.matrix[rowCount][colCount] = 0.0f;

		++colCount;

		if (colCount >= 3) {
			colCount = 0;

			++rowCount;
		}
	}
}

CALCDA Matrix3::Matrix3(const Matrix3 &Other)
{
	for (std::size_t index = 0; index < 9; ++index) {
		value.data[index] = Other.value.data[index];
	}
}

CALCDA Matrix3::~Matrix3()
{
}

Vector3 CALCDA Matrix3::r01() const
{
	return Vector3(value.matrix[0][0], value.matrix[0][1], value.matrix[0][2]);
}

Vector3 CALCDA Matrix3::r02() const
{
	return Vector3(value.matrix[1][0], value.matrix[1][1], value.matrix[1][2]);
}

Vector3 CALCDA Matrix3::r03() const
{
	return Vector3(value.matrix[2][0], value.matrix[2][1], value.matrix[2][2]);
}

Vector3 CALCDA Matrix3::c01() const
{
	return Vector3(value.matrix[0][0], value.matrix[1][0], value.matrix[2][0]);
}

Vector3 CALCDA Matrix3::c02() const
{
	return Vector3(value.matrix[0][1], value.matrix[1][1], value.matrix[2][1]);
}

Vector3 CALCDA Matrix3::c03() const
{
	return Vector3(value.matrix[0][2], value.matrix[1][2], value.matrix[2][2]);
}

float *Matrix3::getData()
{
	return &value.data[0];
}

const float *Matrix3::getData() const
{
	return &value.data[0];
}

Matrix3 &CALCDA Matrix3::selfMultiply(const Matrix3 &Other)
{
	for (unsigned int i = 0U; i < 3U; i++) {
		for (unsigned int j = 0U; j < 3U; j++) {
			for (unsigned int k = 0U; k < 3U; k++) {
				value.matrix[i][k] *= Other.value.matrix[k][j];
			}
		}
	}

	return *this;
}

Matrix3 &CALCDA Matrix3::selfDivide(const Matrix3 &Other)
{
	double determinant = Other.calculateDeterminant();

	return (determinant == 0) ? *this : selfMultiply(Other.inverse(nullptr, &determinant));
}

Matrix3 CALCDA Matrix3::calculateAdjugate() const
{
	// https://en.wikipedia.org/wiki/Adjugate_matrix#3_%C3%97_3_generic_matrix
	// cofactor matrix
	return Matrix3{
	    value.m11 * value.m22 - value.m12 * value.m21,
	    -(value.m01 * value.m22 - value.m12 * value.m20),
	    value.m10 * value.m21 - value.m11 * value.m20,

	    -(value.m01 * value.m22 - value.m02 * value.m21),
	    value.m00 * value.m22 - value.m02 * value.m20,
	    -(value.m00 * value.m21 - value.m01 * value.m20),

	    value.m01 * value.m12 - value.m02 * value.m11,
	    -(value.m00 * value.m12 - value.m02 * value.m10),
	    value.m00 * value.m11 - value.m01 * value.m10,
	}
	    .transpose();
}

double CALCDA Matrix3::calculateDeterminant() const
{
	return value.m00 * (value.m11 * value.m22 - value.m12 * value.m21) -
	       value.m01 * (value.m10 * value.m22 - value.m12 * value.m20) -
	       value.m02 * (value.m10 * value.m21 - value.m11 * value.m20);
}

Matrix3 CALCDA Matrix3::inverse(Matrix3 *iTemporal, double *iDeterminant) const
{
	Matrix3 result;

	double determinant = (iDeterminant == nullptr) ? calculateDeterminant() : *iDeterminant;
	const Matrix3 temporal = (iTemporal == nullptr) ? calculateAdjugate() : *iTemporal;

	if (determinant == 0.0) {
		return Matrix3::Identity;
	}
	else {
		determinant = 1.0 / determinant;

		for (unsigned int i = 0U; i < 9U; i++) {
			result.value.data[i] = static_cast<float>(temporal.value.data[i] * determinant);
		}

		return result;
	}
}

Matrix3 CALCDA Matrix3::divide(const Matrix3 &Other) const
{
	double determinant = Other.calculateDeterminant();

	return (determinant == 0.0)
	           ? Matrix3()
	           : multiply(Other.inverse(nullptr, &determinant));
}

Vector3 CALCDA Matrix3::multiply(const Vector3 &Other) const
{
	const float X = (value.m00 * Other.x) + (value.m01 * Other.y) + (value.m02 * Other.z);
	const float Y = (value.m10 * Other.x) + (value.m11 * Other.y) + (value.m12 * Other.z);
	const float Z = (value.m20 * Other.x) + (value.m21 * Other.y) + (value.m22 * Other.z);

	return Vector3(X, Y, Z);
}

Matrix3 CALCDA Matrix3::multiply(const Matrix3 &Other) const
{
	Matrix3 result;

	for (unsigned int i = 0U; i < 3U; i++) {
		for (unsigned int j = 0U; j < 3U; j++) {
			for (unsigned int k = 0U; k < 3U; k++) {
				result.value.matrix[i][j] += value.matrix[i][k] * Other.value.matrix[k][j];
			}
		}
	}
	return result;
}

Matrix3 CALCDA Matrix3::transpose() const
{
	return Matrix3{
	    value.m00, value.m10, value.m20,
	    value.m01, value.m11, value.m21,
	    value.m02, value.m12, value.m22};
}

Matrix3 CALCDA Matrix3::negate() const
{
	return Matrix3{
	    -value.m00, -value.m01, -value.m02,
	    -value.m10, -value.m11, -value.m12,
	    -value.m20, -value.m21, -value.m22};
}

Matrix3 CALCDA Matrix3::operator-() const
{
	return negate();
}

Matrix3 CALCDA Matrix3::operator/(const Matrix3 &x) const
{
	return divide(x);
}

Matrix3 CALCDA Matrix3::operator*(const Matrix3 &x) const
{
	return multiply(x);
}

Vector3 CALCDA Matrix3::operator*(const Vector3 &x) const
{
	return multiply(x);
}

Matrix3 &CALCDA Matrix3::operator/=(const Matrix3 &x)
{
	return selfDivide(x);
}

Matrix3 &CALCDA Matrix3::operator*=(const Matrix3 &x)
{
	return selfMultiply(x);
}

Matrix3 &CALCDA Matrix3::operator=(const Matrix3 &Other)
{
	for (unsigned int Iterator = 0; Iterator < 9; ++Iterator) {
		value.data[Iterator] = Other.value.data[Iterator];
	}
	return *this;
}

bool CALCDA Matrix3::operator==(const Matrix3 &Other) const
{
	return (
	    value.m00 == Other.value.m00 && value.m01 == Other.value.m01 && value.m02 == Other.value.m02 &&
	    value.m10 == Other.value.m10 && value.m11 == Other.value.m11 && value.m12 == Other.value.m12 &&
	    value.m20 == Other.value.m20 && value.m21 == Other.value.m21 && value.m22 == Other.value.m22);
}

bool CALCDA Matrix3::operator!=(const Matrix3 &Other) const
{
	return (
	    value.m00 != Other.value.m00 || value.m01 != Other.value.m01 || value.m02 != Other.value.m02 ||
	    value.m10 != Other.value.m10 || value.m11 != Other.value.m11 || value.m12 != Other.value.m12 ||
	    value.m20 != Other.value.m20 || value.m21 != Other.value.m21 || value.m22 != Other.value.m22);
}

Matrix3 CALCDA Matrix3::rotation(Axis x, double value)
{
	switch (x) {
		case Axis::X:
			return Matrix3{
			    1.0f, 0.0f, 0.0f,
			    0.0f, static_cast<float>(std::cos(-value)), static_cast<float>(-std::sin(-value)),
			    0.0f, static_cast<float>(std::sin(-value)), static_cast<float>(std::cos(-value))};

		case Axis::Y:
			return Matrix3{
			    static_cast<float>(std::cos(-value)), 0.0f, static_cast<float>(std::sin(-value)),
			    0.0f, 1.0f, 0.0f,
			    static_cast<float>(-std::sin(-value)), 0.0f, static_cast<float>(std::cos(-value))};

		case Axis::Z:
			return Matrix3{
			    static_cast<float>(std::cos(-value)), static_cast<float>(-std::sin(-value)), 0.0f,
			    static_cast<float>(std::sin(-value)), static_cast<float>(std::cos(-value)), 0.0f,
			    0.0f, 0.0f, 1.0f};
		default:
			return Matrix3::Identity;
	}
}

Matrix3 CALCDA Matrix3::translation(float X, float Y)
{
	Matrix3 result = Matrix3::Identity;

	result.value.m02 = X;
	result.value.m12 = Y;

	return result;
}

Matrix3 CALCDA Matrix3::translation(Vector2 Point)
{
	Matrix3 result = Matrix3::Identity;

	result.value.m02 = Point.x;
	result.value.m12 = Point.y;

	return result;
}

Matrix3 CALCDA Matrix3::scale(float X, float Y)
{
	Matrix3 result = Matrix3::Identity;

	result.value.m00 = X;
	result.value.m11 = Y;

	return result;
}

Matrix3 CALCDA Matrix3::scale(Vector2 Point)
{
	Matrix3 result = Matrix3::Identity;

	result.value.m00 = Point.x;
	result.value.m11 = Point.y;

	return result;
}

std::string CALCDA Matrix3::toString() const
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << "[";

	for (std::size_t i = 0; i < 3; ++i) {
		stream << "{";

		for (std::size_t j = 0; j < 3; ++j) {
			stream << value.matrix[i][j];

			if (j < 2) {
				stream << ", ";
			}
		}

		stream << "}";

		if (i < 2) {
			stream << ", ";
		}
	}

	stream << "]";

	return stream.str();
}

std::string CALCDA Matrix3::toStringO(unsigned int Padding, unsigned int Precision) const
{
	const std::string paddingString = std::string(Padding, ' ');

	std::stringstream stream;
	stream << std::fixed << std::setprecision(Precision);

	for (std::size_t i = 0; i < 3; ++i) {
		stream << paddingString;
		for (std::size_t j = 0; j < 3; ++j) {
			stream << (value.matrix[i][j] >= 0.0f ? " " : "") << value.matrix[i][j];

			if (j < 2) {
				stream << "  ";
			}
		}

		if (i < 2) {
			stream << "\n";
		}
	}

	return stream.str();
}

//* STATIC VARIABLE *//

const Matrix3 Matrix3::Identity = Matrix3{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f};
} // namespace Calcda