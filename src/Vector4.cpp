#include <cmath>
#include <iomanip>
#include <sstream>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Calcda {
const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::One = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::UnitX = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitY = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitZ = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UnitW = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

Vector2 Vector4::xy() const { return Vector2(x, y); }

Vector2 Vector4::yz() const { return Vector2(y, z); }

Vector2 Vector4::zw() const { return Vector2(z, w); }

Vector3 Vector4::xyz() const { return Vector3(x, y, z); }

Vector3 Vector4::yzw() const { return Vector3(y, z, w); }

Vector4 Vector4::xyzw() const { return *this; }

Vector4 Vector4::wzyx() const { return Vector4(w, z, y, x); }

float *Vector4::getData() { return &x; }

const float *Vector4::getData() const { return &x; }

Vector4 &Vector4::selfAdd(const Vector4 &Other) {
    x += Other.x;
    y += Other.y;
    z += Other.z;
    w += Other.w;

    return *this;
}

Vector4 &Vector4::selfSubtract(const Vector4 &Other) {
    x -= Other.x;
    y -= Other.y;
    z -= Other.z;
    w -= Other.w;

    return *this;
}

Vector4 &Vector4::selfMultiply(const Vector4 &Other) {
    x *= Other.x;
    y *= Other.y;
    z *= Other.z;
    w *= Other.w;

    return *this;
}

Vector4 &Vector4::selfDivide(float Amount) {
    float reciprocal = 1.0f / Amount;

    x *= reciprocal;
    y *= reciprocal;
    z *= reciprocal;
    w *= reciprocal;

    return *this;
}

Vector4 &Vector4::selfDivide(const Vector4 &Other) {
    x /= Other.x;
    y /= Other.y;
    z /= Other.z;
    w /= Other.w;

    return *this;
}

Vector4 &Vector4::selfNormalize() {
    float length = std::abs(std::sqrt(x * x + y * y));

    x /= length;
    y /= length;
    z /= length;
    w /= length;

    return *this;
}

Vector4 &Vector4::selfAbsolute() {
    x = std::abs(x);
    y = std::abs(y);
    y = std::abs(z);
    w = std::abs(w);

    return *this;
}

Vector4 &Vector4::selfSqrt() {
    x = std::sqrt(x);
    y = std::sqrt(y);
    z = std::sqrt(z);
    w = std::sqrt(w);

    return *this;
}

Vector4 &Vector4::selfNegate() {
    x = -x;
    y = -y;
    z = -z;
    w = -w;

    return *this;
}

/* [[nodiscard]] */ Vector4 Vector4::add(const Vector4 &Other) const {
    Vector4 result;

    result.x = x + Other.x;
    result.y = y + Other.y;
    result.z = z + Other.z;
    result.w = w + Other.w;

    return result;
}

/* [[nodiscard]] */ Vector4 Vector4::subtract(const Vector4 &Other) const {
    Vector4 result;

    result.x = x - Other.x;
    result.y = y - Other.y;
    result.z = z - Other.z;
    result.w = w - Other.w;

    return result;
}

/* [[nodiscard]] */ Vector4 Vector4::multiply(const Vector4 &Other) const {
    Vector4 result;

    result.x = x * Other.x;
    result.y = y * Other.y;
    result.z = z * Other.z;
    result.w = w * Other.w;

    return result;
}

/* [[nodiscard]] */ Vector4 Vector4::divide(float Amount) const {
    Vector4 result;

    float reciprocal = 1.0f / Amount;

    result.x = x * reciprocal;
    result.y = y * reciprocal;
    result.z = z * reciprocal;
    result.w = w * reciprocal;

    return result;
}

/* [[nodiscard]] */ Vector4 Vector4::divide(const Vector4 &Other) const {
    Vector4 result;

    result.x = x / Other.x;
    result.y = y / Other.y;
    result.z = z / Other.z;
    result.w = w / Other.w;

    return result;
}

/* [[nodiscard]] */ Vector4 Vector4::normalize() const {
    Vector4 result;

    float LengthReciprocal = 1.0f / std::sqrt(x * x + y * y + z * z + w * w);

    result.x = x * LengthReciprocal;
    result.y = y * LengthReciprocal;
    result.z = z * LengthReciprocal;
    result.w = w * LengthReciprocal;

    return result;
}

/* [[nodiscard]] */ Vector4 Vector4::negate() const {
    return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(const Vector4 &Other) const { return add(Other); }

Vector4 Vector4::operator-(const Vector4 &Other) const {
    return subtract(Other);
}

Vector4 Vector4::operator*(const Vector4 &Other) const {
    return multiply(Other);
}

Vector4 Vector4::operator/(const Vector4 &Other) const { return divide(Other); }

Vector4 Vector4::operator/(float Amount) const { return divide(Amount); }

Vector4 Vector4::operator-() const { return negate(); }

Vector4 &Vector4::operator=(const Vector4 &Other) {
    x = Other.x;
    y = Other.y;
    z = Other.z;
    w = Other.w;

    return *this;
}

Vector4 &Vector4::operator+=(const Vector4 &Other) { return selfAdd(Other); }

Vector4 &Vector4::operator-=(const Vector4 &Other) {
    return selfSubtract(Other);
}

Vector4 &Vector4::operator*=(const Vector4 &Other) {
    return selfMultiply(Other);
}

Vector4 &Vector4::operator/=(const Vector4 &Other) { return selfDivide(Other); }

Vector4 &Vector4::operator/=(float Amount) { return selfDivide(Amount); }

bool Vector4::operator==(const Vector4 &Other) const {
    return (x == Other.x && y == Other.y && z == Other.z && w == Other.w);
}

bool Vector4::operator!=(const Vector4 &Other) const {
    return (x != Other.x || y != Other.y || z != Other.z || w != Other.w);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
Vector4 Vector4::absolute() const {
    Vector4 result;

    result.x = std::abs(x);
    result.y = std::abs(y);
    result.z = std::abs(z);
    result.w = std::abs(w);

    return result;
}

Vector4 Vector4::sqrt() const {
    Vector4 result;

    result.x = std::sqrt(x);
    result.y = std::sqrt(y);
    result.z = std::sqrt(z);
    result.w = std::sqrt(w);

    return result;
}

float Vector4::distance(const Vector4 &Other) const {
    return subtract(Other).length();
}

float Vector4::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::lengthSquared() const { return x * x + y * y + z * z + w * w; }

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4.cs
Vector4 Vector4::reflect(const Vector4 &Value, const Vector4 &Surface) {
    float DotProduct = Value.x * Surface.x + Value.y * Surface.y +
                       Value.z * Surface.z + Value.w * Surface.w;

    return Vector4(Value.x - 2.0f * DotProduct * Surface.x,
                   Value.y - 2.0f * DotProduct * Surface.y,
                   Value.z - 2.0f * DotProduct * Surface.z,
                   Value.w - 2.0f * DotProduct * Surface.w);
}

Vector4 Vector4::clamp(const Vector4 &Value, const Vector4 &min,
                       const Vector4 &max) {
    float X = Value.x;
    X = (X > max.x) ? max.x : X;
    X = (X < min.x) ? min.x : X;

    float Y = Value.y;
    Y = (Y > max.y) ? max.y : Y;
    Y = (Y < min.y) ? min.y : Y;

    float Z = Value.z;
    Z = (Z > max.z) ? max.z : Z;
    Z = (Z < min.z) ? min.z : Z;

    float W = Value.w;
    W = (W > max.w) ? max.w : W;
    W = (W < min.w) ? min.w : W;

    return Vector4(X, Y, Z, W);
}

Vector4 Vector4::lerp(const Vector4 &Value1, const Vector4 &Value2,
                      float Amount) {
    return Vector4(Value1.x + (Value2.x - Value1.x) * Amount,
                   Value1.y + (Value2.y - Value1.y) * Amount,
                   Value1.z + (Value2.z - Value1.z) * Amount,
                   Value1.w + (Value2.w - Value1.w) * Amount);
}

// https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
float Vector4::dot(const Vector4 &Value1, const Vector4 &Value2) {
    return (Value1.x * Value2.x + Value1.y * Value2.y + Value1.z * Value2.z +
            Value1.w * Value2.w);
}

Vector4 Vector4::vmin(const Vector4 &Value1, const Vector4 &Value2) {
    return Vector4((Value1.x < Value2.x) ? Value1.x : Value2.x,
                   (Value1.y < Value2.y) ? Value1.y : Value2.y,
                   (Value1.z < Value2.z) ? Value1.z : Value2.z,
                   (Value1.w < Value2.w) ? Value1.w : Value2.w);
}

Vector4 Vector4::vmax(const Vector4 &Value1, const Vector4 &Value2) {
    return Vector4((Value1.x < Value2.x) ? Value1.x : Value2.x,
                   (Value1.y < Value2.y) ? Value1.y : Value2.y,
                   (Value1.z < Value2.z) ? Value1.z : Value2.z,
                   (Value1.w < Value2.w) ? Value1.w : Value2.w);
}

Vector4 Vector4::scalar(float Value) {
    return Vector4(Value, Value, Value, Value);
}

std::string Vector4::toString() const {
    std::stringstream stream;

    stream << std::fixed << std::setprecision(2) << "<" << x << ", " << y
           << ", " << z << ", " << w << ">";

    return stream.str();
}
} // namespace Calcda