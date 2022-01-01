#include <cmath>
#include <iomanip>
#include <sstream>

#include "Vector2.hpp"

namespace Calcda {

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::UnitX = Vector2(1.0f, 0.0f);
const Vector2 Vector2::UnitY = Vector2(0.0f, 1.0f);

Vector2::Vector2() : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(const Vector2 &Other) : x(Other.x), y(Other.y)
{
}

Vector2::Vector2(float X, float Y) : x(X), y(Y)
{
}

Vector2::~Vector2()
{
}
Vector2 CALCDA Vector2::xy() const
{
	return Vector2(x, y);
}

Vector2 CALCDA Vector2::yx() const
{
	return Vector2(y, x);
}

float *CALCDA Vector2::getData()
{
	return &x;
}

const float *Vector2::getData() const
{
	return &x;
}

Vector2 &CALCDA Vector2::selfAdd(const Vector2 &Other)
{
	x += Other.x;
	y += Other.y;

	return *this;
}

Vector2 &CALCDA Vector2::selfSubtract(const Vector2 &Other)
{
	x -= Other.x;
	y -= Other.y;

	return *this;
}

Vector2 &CALCDA Vector2::selfMultiply(const Vector2 &Other)
{
	x *= Other.x;
	y *= Other.y;

	return *this;
}

Vector2 &CALCDA Vector2::selfDivide(float Amount)
{
	float reciprocal = 1.0f / Amount;

	x *= reciprocal;
	y *= reciprocal;

	return *this;
}

Vector2 &CALCDA Vector2::selfDivide(const Vector2 &Other)
{
	x /= Other.x;
	y /= Other.y;

	return *this;
}

Vector2 &CALCDA Vector2::selfNormalize()
{
	float lengthReciprocal = 1.0f / std::abs(std::sqrt(x * x + y * y));

	x *= lengthReciprocal;
	y *= lengthReciprocal;

	return *this;
}

Vector2 &CALCDA Vector2::selfAbsolute()
{
	x = std::abs(x);
	y = std::abs(y);

	return *this;
}

Vector2 &CALCDA Vector2::selfSqrt()
{
	x = std::sqrt(x);
	y = std::sqrt(y);

	return *this;
}

Vector2 &CALCDA Vector2::selfNegate()
{
	x = -x;
	y = -y;

	return *this;
}

[[nodiscard]] Vector2 CALCDA Vector2::add(const Vector2 &Other) const
{
	Vector2 result;

	result.x = x + Other.x;
	result.y = y + Other.y;

	return result;
}

[[nodiscard]] Vector2 CALCDA Vector2::subtract(const Vector2 &Other) const
{
	Vector2 result;

	result.x = x - Other.x;
	result.y = y - Other.y;

	return result;
}

[[nodiscard]] Vector2 CALCDA Vector2::multiply(const Vector2 &Other) const
{
	Vector2 result;

	result.x = x * Other.x;
	result.y = y * Other.y;

	return result;
}

[[nodiscard]] Vector2 CALCDA Vector2::divide(float Amount) const
{
	Vector2 result;

	float Reciprocal = 1.0f / Amount;

	result.x = x * Reciprocal;
	result.y = y * Reciprocal;

	return result;
}

[[nodiscard]] Vector2 CALCDA Vector2::divide(const Vector2 &Other) const
{
	Vector2 result;

	result.x = x / Other.x;
	result.y = y / Other.y;

	return result;
}

[[nodiscard]] Vector2 CALCDA Vector2::normalize() const
{
	Vector2 result;

	float LengthReciprocal = 1.0f / std::abs(std::sqrt(x * x + y * y));

	result.x = x * LengthReciprocal;
	result.y = y * LengthReciprocal;

	return result;
}

[[nodiscard]] Vector2 CALCDA Vector2::negate() const
{
	return Vector2(-x, -y);
}

Vector2 CALCDA Vector2::operator+(const Vector2 &Other) const
{
	return add(Other);
}

Vector2 CALCDA Vector2::operator-(const Vector2 &Other) const
{
	return subtract(Other);
}

Vector2 CALCDA Vector2::operator*(const Vector2 &Other) const
{
	return multiply(Other);
}

Vector2 CALCDA Vector2::operator/(const Vector2 &Other) const
{
	return divide(Other);
}

Vector2 CALCDA Vector2::operator/(float Amount) const
{
	return divide(Amount);
}

Vector2 CALCDA Vector2::operator-() const
{
	return negate();
}

Vector2 &CALCDA Vector2::operator=(const Vector2 &Other)
{
	x = Other.x;
	y = Other.y;

	return *this;
}

Vector2 &CALCDA Vector2::operator+=(const Vector2 &Other)
{
	return selfAdd(Other);
}

Vector2 &CALCDA Vector2::operator-=(const Vector2 &Other)
{
	return selfSubtract(Other);
}

Vector2 &CALCDA Vector2::operator*=(const Vector2 &Other)
{
	return selfMultiply(Other);
}

Vector2 &CALCDA Vector2::operator/=(const Vector2 &Other)
{
	return selfDivide(Other);
}

Vector2 &CALCDA Vector2::operator/=(float Amount)
{
	return selfDivide(Amount);
}

bool CALCDA Vector2::operator==(const Vector2 &Other) const
{
	return (x == Other.x && y == Other.y);
}

bool CALCDA Vector2::operator!=(const Vector2 &Other) const
{
	return (x != Other.x || y != Other.y);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
Vector2 CALCDA Vector2::absolute() const
{
	Vector2 result;

	result.x = std::abs(x);
	result.y = std::abs(y);

	return result;
}

Vector2 CALCDA Vector2::sqrt() const
{
	Vector2 result;

	result.x = std::sqrt(x);
	result.y = std::sqrt(y);

	return result;
}

float CALCDA Vector2::distance(const Vector2 &Other) const
{
	return subtract(Other).length();
}

float CALCDA Vector2::length() const
{
	return std::sqrt(x * x + y * y);
}

float CALCDA Vector2::lengthSquared() const
{
	return x * x + y * y;
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2.cs
Vector2 CALCDA Vector2::reflect(const Vector2 &Value, const Vector2 &Surface)
{
	float dotProduct = Value.x * Surface.x + Value.y * Surface.y;

	return Vector2(
	    Value.x - 2.0f * dotProduct * Surface.x,
	    Value.y - 2.0f * dotProduct * Surface.y);
}

Vector2 CALCDA Vector2::clamp(const Vector2 &Value, const Vector2 &min, const Vector2 &max)
{
	float X = Value.x;
	X = (X > max.x) ? max.x : X;
	X = (X < min.x) ? min.x : X;

	float Y = Value.y;
	Y = (Y > max.y) ? max.y : Y;
	Y = (Y < min.y) ? min.y : Y;

	return Vector2(X, Y);
}

Vector2 CALCDA Vector2::lerp(const Vector2 &Value1, const Vector2 &Value2, float Amount)
{
	return Vector2(
	    Value1.x + (Value2.x - Value1.x) * Amount,
	    Value1.y + (Value2.y - Value1.y) * Amount);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
float CALCDA Vector2::dot(const Vector2 &Value1, const Vector2 &Value2)
{
	return (
	    Value1.x * Value2.x +
	    Value1.y * Value2.y);
}

Vector2 CALCDA Vector2::vmin(const Vector2 &Value1, const Vector2 &Value2)
{
	return Vector2(
	    (Value1.x < Value2.x) ? Value1.x : Value2.x,
	    (Value1.y < Value2.y) ? Value1.y : Value2.y);
}

Vector2 CALCDA Vector2::vmax(const Vector2 &Value1, const Vector2 &Value2)
{
	return Vector2(
	    (Value1.x < Value2.x) ? Value1.x : Value2.x,
	    (Value1.y < Value2.y) ? Value1.y : Value2.y);
}

Vector2 CALCDA Vector2::scalar(float Value)
{
	return Vector2(Value, Value);
}

std::string CALCDA Vector2::toString() const
{
	std::stringstream Stream;

	Stream << std::fixed << std::setprecision(2) << "<" << x << ", " << y << ">";

	return Stream.str();
}
} // namespace Calcda