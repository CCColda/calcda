#include <cmath>
#include <iomanip>
#include <sstream>

#include "Vector3.hpp"

namespace Calcda {

const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::UnitX = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ = Vector3(0.0f, 0.0f, 1.0f);

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(const Vector3 &Other) : x(Other.x), y(Other.y), z(Other.z)
{
}

Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
}

Vector3::Vector3(Vector2 XY, float Z) : x(XY.x), y(XY.y), z(Z)
{
}

Vector3::Vector3(float X, Vector2 YZ) : x(X), y(YZ.x), z(YZ.y)
{
}

Vector3::~Vector3()
{
}

Vector2 CALCDA Vector3::xy() const
{
	return Vector2(x, y);
}

Vector2 CALCDA Vector3::yz() const
{
	return Vector2(y, z);
}

Vector3 CALCDA Vector3::xyz() const
{
	return *this;
}

Vector3 CALCDA Vector3::zyx() const
{
	return Vector3(z, y, x);
}

float *CALCDA Vector3::getData()
{
	return &x;
}

const float *Vector3::getData() const
{
	return &x;
}

Vector3 &CALCDA Vector3::selfAdd(const Vector3 &Other)
{
	x += Other.x;
	y += Other.y;
	z += Other.z;

	return *this;
}

Vector3 &CALCDA Vector3::selfSubtract(const Vector3 &Other)
{
	x -= Other.x;
	y -= Other.y;
	z -= Other.z;

	return *this;
}

Vector3 &CALCDA Vector3::selfMultiply(const Vector3 &Other)
{
	x *= Other.x;
	y *= Other.y;
	z *= Other.z;

	return *this;
}

Vector3 &CALCDA Vector3::selfDivide(float Amount)
{
	float reciprocal = 1.0f / Amount;

	x *= reciprocal;
	y *= reciprocal;
	z *= reciprocal;

	return *this;
}

Vector3 &CALCDA Vector3::selfDivide(const Vector3 &Other)
{
	x /= Other.x;
	y /= Other.y;
	z /= Other.z;

	return *this;
}

Vector3 &CALCDA Vector3::selfNormalize()
{
	float length = std::abs(std::sqrt(x * x + y * y));

	x /= length;
	y /= length;
	z /= length;

	return *this;
}

Vector3 &CALCDA Vector3::selfAbsolute()
{
	x = std::abs(x);
	y = std::abs(y);
	y = std::abs(z);

	return *this;
}

Vector3 &CALCDA Vector3::selfSqrt()
{
	x = std::sqrt(x);
	y = std::sqrt(y);
	z = std::sqrt(z);

	return *this;
}

Vector3 &CALCDA Vector3::selfNegate()
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

[[nodiscard]] Vector3 CALCDA Vector3::add(const Vector3 &Other) const
{
	Vector3 result;

	result.x = x + Other.x;
	result.y = y + Other.y;
	result.z = z + Other.z;

	return result;
}

[[nodiscard]] Vector3 CALCDA Vector3::subtract(const Vector3 &Other) const
{
	Vector3 result;

	result.x = x - Other.x;
	result.y = y - Other.y;
	result.z = z - Other.z;

	return result;
}

[[nodiscard]] Vector3 CALCDA Vector3::multiply(const Vector3 &Other) const
{
	Vector3 result;

	result.x = x * Other.x;
	result.y = y * Other.y;
	result.z = z * Other.z;

	return result;
}

[[nodiscard]] Vector3 CALCDA Vector3::divide(float Amount) const
{
	Vector3 result;

	float reciprocal = 1.0f / Amount;

	result.x = x * reciprocal;
	result.y = y * reciprocal;
	result.z = z * reciprocal;

	return result;
}

[[nodiscard]] Vector3 CALCDA Vector3::divide(const Vector3 &Other) const
{
	Vector3 result;

	result.x = x / Other.x;
	result.y = y / Other.y;
	result.z = z / Other.z;

	return result;
}

[[nodiscard]] Vector3 CALCDA Vector3::normalize() const
{
	Vector3 result;

	float LengthReciprocal = 1.0f / std::sqrt(x * x + y * y + z * z);

	result.x = x * LengthReciprocal;
	result.y = y * LengthReciprocal;
	result.z = z * LengthReciprocal;

	return result;
}

[[nodiscard]] Vector3 CALCDA Vector3::negate() const
{
	return Vector3(-x, -y, -z);
}

Vector3 CALCDA Vector3::operator+(const Vector3 &Other) const
{
	return add(Other);
}

Vector3 CALCDA Vector3::operator-(const Vector3 &Other) const
{
	return subtract(Other);
}

Vector3 CALCDA Vector3::operator*(const Vector3 &Other) const
{
	return multiply(Other);
}

Vector3 CALCDA Vector3::operator/(const Vector3 &Other) const
{
	return divide(Other);
}

Vector3 CALCDA Vector3::operator/(float Amount) const
{
	return divide(Amount);
}

Vector3 CALCDA Vector3::operator-() const
{
	return negate();
}

Vector3 &CALCDA Vector3::operator=(const Vector3 &Other)
{
	x = Other.x;
	y = Other.y;
	z = Other.z;

	return *this;
}

Vector3 &CALCDA Vector3::operator+=(const Vector3 &Other)
{
	return selfAdd(Other);
}

Vector3 &CALCDA Vector3::operator-=(const Vector3 &Other)
{
	return selfSubtract(Other);
}

Vector3 &CALCDA Vector3::operator*=(const Vector3 &Other)
{
	return selfMultiply(Other);
}

Vector3 &CALCDA Vector3::operator/=(const Vector3 &Other)
{
	return selfDivide(Other);
}

Vector3 &CALCDA Vector3::operator/=(float Amount)
{
	return selfDivide(Amount);
}

bool CALCDA Vector3::operator==(const Vector3 &Other) const
{
	return (x == Other.x && y == Other.y && z == Other.z);
}

bool CALCDA Vector3::operator!=(const Vector3 &Other) const
{
	return (x != Other.x || y != Other.y || z != Other.z);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
Vector3 CALCDA Vector3::absolute() const
{
	Vector3 result;

	result.x = std::abs(x);
	result.y = std::abs(y);
	result.z = std::abs(z);

	return result;
}

Vector3 CALCDA Vector3::sqrt() const
{
	Vector3 result;

	result.x = std::sqrt(x);
	result.y = std::sqrt(y);
	result.z = std::sqrt(z);

	return result;
}

float CALCDA Vector3::distance(const Vector3 &Other) const
{
	return subtract(Other).length();
}

float CALCDA Vector3::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

float CALCDA Vector3::lengthSquared() const
{
	return x * x + y * y + z * z;
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs
Vector3 CALCDA Vector3::reflect(const Vector3 &Value, const Vector3 &Surface)
{
	float dotProduct = Value.x * Surface.x + Value.y * Surface.y + Value.z * Surface.z;

	return Vector3(
	    Value.x - 2.0f * dotProduct * Surface.x,
	    Value.y - 2.0f * dotProduct * Surface.y,
	    Value.z - 2.0f * dotProduct * Surface.z);
}

Vector3 CALCDA Vector3::clamp(const Vector3 &Value, const Vector3 &min, const Vector3 &max)
{
	float X = Value.x;
	X = (X > max.x) ? max.x : X;
	X = (X < min.x) ? min.x : X;

	float Y = Value.y;
	Y = (Y > max.y) ? max.y : Y;
	Y = (Y < min.y) ? min.y : Y;

	float Z = Value.z;
	Z = (Z > max.z) ? max.z : Z;
	Z = (Z < min.z) ? min.z : Z;

	return Vector3(X, Y, Z);
}

Vector3 CALCDA Vector3::lerp(const Vector3 &Value1, const Vector3 &Value2, float Amount)
{
	return Vector3(
	    Value1.x + (Value2.x - Value1.x) * Amount,
	    Value1.y + (Value2.y - Value1.y) * Amount,
	    Value1.z + (Value2.z - Value1.z) * Amount);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
float CALCDA Vector3::dot(const Vector3 &Value1, const Vector3 &Value2)
{
	return (
	    Value1.x * Value2.x +
	    Value1.y * Value2.y +
	    Value1.z * Value2.z);
}

Vector3 CALCDA Vector3::cross(const Vector3 &Value1, const Vector3 &Value2)
{
	return Vector3(
	    Value1.y * Value2.z - Value1.z * Value2.y,
	    Value1.z * Value2.x - Value1.x * Value2.z,
	    Value1.x * Value2.y - Value1.y * Value2.x);
}

Vector3 CALCDA Vector3::vmin(const Vector3 &Value1, const Vector3 &Value2)
{
	return Vector3(
	    (Value1.x < Value2.x) ? Value1.x : Value2.x,
	    (Value1.y < Value2.y) ? Value1.y : Value2.y,
	    (Value1.z < Value2.z) ? Value1.z : Value2.z);
}

Vector3 CALCDA Vector3::vmax(const Vector3 &Value1, const Vector3 &Value2)
{
	return Vector3(
	    (Value1.x < Value2.x) ? Value1.x : Value2.x,
	    (Value1.y < Value2.y) ? Value1.y : Value2.y,
	    (Value1.z < Value2.z) ? Value1.z : Value2.z);
}

Vector3 CALCDA Vector3::scalar(float Value)
{
	return Vector3(Value, Value, Value);
}

std::string CALCDA Vector3::toString() const
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(2) << "<" << x << ", " << y << ", " << z << ">";

	return stream.str();
}
} // namespace Calcda