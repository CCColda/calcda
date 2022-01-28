#include <cmath>
#include <iomanip>
#include <sstream>

#include "Vector2.hpp"

namespace Calcda {

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::UnitX = Vector2(1.0f, 0.0f);
const Vector2 Vector2::UnitY = Vector2(0.0f, 1.0f);

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(const Vector2 &Other) : x(Other.x), y(Other.y) {}

Vector2::Vector2(float X, float Y) : x(X), y(Y) {}

Vector2::~Vector2() {}
Vector2 Vector2::xy() const { return Vector2(x, y); }

Vector2 Vector2::yx() const { return Vector2(y, x); }

float *Vector2::getData() { return &x; }

const float *Vector2::getData() const { return &x; }

Vector2 &Vector2::selfAdd(const Vector2 &Other) {
    x += Other.x;
    y += Other.y;

    return *this;
}

Vector2 &Vector2::selfSubtract(const Vector2 &Other) {
    x -= Other.x;
    y -= Other.y;

    return *this;
}

Vector2 &Vector2::selfMultiply(const Vector2 &Other) {
    x *= Other.x;
    y *= Other.y;

    return *this;
}

Vector2 &Vector2::selfDivide(float Amount) {
    float reciprocal = 1.0f / Amount;

    x *= reciprocal;
    y *= reciprocal;

    return *this;
}

Vector2 &Vector2::selfDivide(const Vector2 &Other) {
    x /= Other.x;
    y /= Other.y;

    return *this;
}

Vector2 &Vector2::selfNormalize() {
    float lengthReciprocal = 1.0f / std::abs(std::sqrt(x * x + y * y));

    x *= lengthReciprocal;
    y *= lengthReciprocal;

    return *this;
}

Vector2 &Vector2::selfAbsolute() {
    x = std::abs(x);
    y = std::abs(y);

    return *this;
}

Vector2 &Vector2::selfSqrt() {
    x = std::sqrt(x);
    y = std::sqrt(y);

    return *this;
}

Vector2 &Vector2::selfNegate() {
    x = -x;
    y = -y;

    return *this;
}

/* [[nodiscard]] */ Vector2 Vector2::add(const Vector2 &Other) const {
    Vector2 result;

    result.x = x + Other.x;
    result.y = y + Other.y;

    return result;
}

/* [[nodiscard]] */ Vector2 Vector2::subtract(const Vector2 &Other) const {
    Vector2 result;

    result.x = x - Other.x;
    result.y = y - Other.y;

    return result;
}

/* [[nodiscard]] */ Vector2 Vector2::multiply(const Vector2 &Other) const {
    Vector2 result;

    result.x = x * Other.x;
    result.y = y * Other.y;

    return result;
}

/* [[nodiscard]] */ Vector2 Vector2::divide(float Amount) const {
    Vector2 result;

    float Reciprocal = 1.0f / Amount;

    result.x = x * Reciprocal;
    result.y = y * Reciprocal;

    return result;
}

/* [[nodiscard]] */ Vector2 Vector2::divide(const Vector2 &Other) const {
    Vector2 result;

    result.x = x / Other.x;
    result.y = y / Other.y;

    return result;
}

/* [[nodiscard]] */ Vector2 Vector2::normalize() const {
    Vector2 result;

    float LengthReciprocal = 1.0f / std::abs(std::sqrt(x * x + y * y));

    result.x = x * LengthReciprocal;
    result.y = y * LengthReciprocal;

    return result;
}

/* [[nodiscard]] */ Vector2 Vector2::negate() const { return Vector2(-x, -y); }

Vector2 Vector2::operator+(const Vector2 &Other) const { return add(Other); }

Vector2 Vector2::operator-(const Vector2 &Other) const {
    return subtract(Other);
}

Vector2 Vector2::operator*(const Vector2 &Other) const {
    return multiply(Other);
}

Vector2 Vector2::operator/(const Vector2 &Other) const { return divide(Other); }

Vector2 Vector2::operator/(float Amount) const { return divide(Amount); }

Vector2 Vector2::operator-() const { return negate(); }

Vector2 &Vector2::operator=(const Vector2 &Other) {
    x = Other.x;
    y = Other.y;

    return *this;
}

Vector2 &Vector2::operator+=(const Vector2 &Other) { return selfAdd(Other); }

Vector2 &Vector2::operator-=(const Vector2 &Other) {
    return selfSubtract(Other);
}

Vector2 &Vector2::operator*=(const Vector2 &Other) {
    return selfMultiply(Other);
}

Vector2 &Vector2::operator/=(const Vector2 &Other) { return selfDivide(Other); }

Vector2 &Vector2::operator/=(float Amount) { return selfDivide(Amount); }

bool Vector2::operator==(const Vector2 &Other) const {
    return (x == Other.x && y == Other.y);
}

bool Vector2::operator!=(const Vector2 &Other) const {
    return (x != Other.x || y != Other.y);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
Vector2 Vector2::absolute() const {
    Vector2 result;

    result.x = std::abs(x);
    result.y = std::abs(y);

    return result;
}

Vector2 Vector2::sqrt() const {
    Vector2 result;

    result.x = std::sqrt(x);
    result.y = std::sqrt(y);

    return result;
}

float Vector2::distance(const Vector2 &Other) const {
    return subtract(Other).length();
}

float Vector2::length() const { return std::sqrt(x * x + y * y); }

float Vector2::lengthSquared() const { return x * x + y * y; }

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2.cs
Vector2 Vector2::reflect(const Vector2 &value, const Vector2 &surface) {
    float dotProduct = value.x * surface.x + value.y * surface.y;

    return Vector2(value.x - 2.0f * dotProduct * surface.x,
                   value.y - 2.0f * dotProduct * surface.y);
}

Vector2 Vector2::clamp(const Vector2 &value, const Vector2 &min,
                       const Vector2 &max) {
    float X = value.x;
    X = (X > max.x) ? max.x : X;
    X = (X < min.x) ? min.x : X;

    float Y = value.y;
    Y = (Y > max.y) ? max.y : Y;
    Y = (Y < min.y) ? min.y : Y;

    return Vector2(X, Y);
}

Vector2 Vector2::lerp(const Vector2 &value1, const Vector2 &value2,
                      float Amount) {
    return Vector2(value1.x + (value2.x - value1.x) * Amount,
                   value1.y + (value2.y - value1.y) * Amount);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
float Vector2::dot(const Vector2 &value1, const Vector2 &value2) {
    return (value1.x * value2.x + value1.y * value2.y);
}

Vector2 Vector2::vmin(const Vector2 &value1, const Vector2 &value2) {
    return Vector2((value1.x < value2.x) ? value1.x : value2.x,
                   (value1.y < value2.y) ? value1.y : value2.y);
}

Vector2 Vector2::vmax(const Vector2 &value1, const Vector2 &value2) {
    return Vector2((value1.x > value2.x) ? value1.x : value2.x,
                   (value1.y > value2.y) ? value1.y : value2.y);
}

Vector2 Vector2::scalar(float value) { return Vector2(value, value); }

std::string Vector2::toString() const {
    std::stringstream Stream;

    Stream << std::fixed << std::setprecision(2) << "<" << x << ", " << y
           << ">";

    return Stream.str();
}
} // namespace Calcda