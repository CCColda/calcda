#ifndef CALCDA_VECTOR3_H
#define CALCDA_VECTOR3_H

#include "Intrinsic.hpp"
#include "Vector2.hpp" // Calcda::Vector2

#include <string>
#include <utility>

namespace Calcda {
/**
 * @brief Class for 3-dimensional vectors
 *
 * @see [Reference:
 * Intrinsics](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3_Intrinsics.cs),
 * @see [Reference:
 * Vector3](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs)
 */
class Vector3 {
  public:
    float x;
    float y;
    float z;

    friend class Vector4;

  public:
    // 0; 0; 0 - Zero vector
    static const Vector3 Zero;

    // 1; 1; 1 - "One" vector
    static const Vector3 One;

    // 1; 0; 0 - X axis vector
    static const Vector3 UnitX;

    // 0; 1; 0 - Y axis vector
    static const Vector3 UnitY;

    // 0; 0; 1 - Z axis vector
    static const Vector3 UnitZ;

  public:
    Vector3();
    Vector3(float X, float Y, float Z);
    Vector3(Vector2 XY, float Z);
    Vector3(float X, Vector2 YZ);
    Vector3(const Vector3 &Other);
    ~Vector3();

    //! @brief Returns the X and Y elements
    Vector2 xy() const;

    //! @brief Returns the Y and Z elements
    Vector2 yz() const;

    //! @brief Returns the same vector (convinience)
    Vector3 xyz() const;

    //! @brief Returns the Z, Y, X elements
    Vector3 zyx() const;

    //! @brief Returns a pointer to the beginning of the data
    float *getData();

    //! @brief Returns a const pointer to the beginning of the data
    const float *getData() const;

    //! @brief Adds the two vectors together
    Vector3 &selfAdd(const Vector3 &Other);

    //! @brief Subtracts @c Other from the current vector
    Vector3 &selfSubtract(const Vector3 &Other);

    //! @brief Multiplies the current vector with @c Other
    Vector3 &selfMultiply(const Vector3 &Other);

    //! @brief Divides the elements of the current vector with @c Amount
    Vector3 &selfDivide(float Amount);

    //! @brief Divides the current vector with @c Other
    Vector3 &selfDivide(const Vector3 &Other);

    //! @brief Normalizes the current vector
    Vector3 &selfNormalize();

    //! @brief Transforms the vector into +X +Y +Z space
    Vector3 &selfAbsolute();

    //! @brief Transforms the vector to have the values of its elements' square
    //! roots
    Vector3 &selfSqrt();

    //! @brief Negates the vector
    Vector3 &selfNegate();

    //! @brief Adds the two vectors together
    /* [[nodiscard]] */ Vector3 add(const Vector3 &Other) const;

    //! @brief Subtracts @c Other from the current vector
    /* [[nodiscard]] */ Vector3 subtract(const Vector3 &Other) const;

    //! @brief Multiplies the current vector with @c Other
    /* [[nodiscard]] */ Vector3 multiply(const Vector3 &Other) const;

    //! @brief Divides the elements of the current vector with @c Amount
    /* [[nodiscard]] */ Vector3 divide(float Amount) const;

    //! @brief Divides the current vector with @c Other, returns the result
    /* [[nodiscard]] */ Vector3 divide(const Vector3 &Other) const;

    //! @brief Normalizes the current vector
    /* [[nodiscard]] */ Vector3 normalize() const;

    //! @brief Negates the vector
    /* [[nodiscard]] */ Vector3 negate() const;

    Vector3 operator+(const Vector3 &Other) const;
    Vector3 operator-(const Vector3 &Other) const;
    Vector3 operator*(const Vector3 &Other) const;
    Vector3 operator/(const Vector3 &Other) const;
    Vector3 operator/(float Amount) const;
    Vector3 operator-() const;

    Vector3 &operator=(const Vector3 &Other);
    Vector3 &operator+=(const Vector3 &Other);
    Vector3 &operator-=(const Vector3 &Other);
    Vector3 &operator*=(const Vector3 &Other);
    Vector3 &operator/=(const Vector3 &Other);
    Vector3 &operator/=(float Amount);

    bool operator==(const Vector3 &Other) const;
    bool operator!=(const Vector3 &Other) const;

    //! @brief Transforms the vector into +X +Y +Z space
    Vector3 absolute() const;

    //! @brief Returns a vector with the square roots of the current vector's
    //! elements
    Vector3 sqrt() const;

    //! @brief distance between the current vector and @c Other
    float distance(const Vector3 &Other) const;

    //! @brief Returns the length of the vector
    float length() const;

    //! @brief Returns the squared length of the vector
    float lengthSquared() const;

    // https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs

    /**
     * @brief Reflects @c Value on @c Surface
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs
     * "Vector3")
     */
    static Vector3 reflect(const Vector3 &Value, const Vector3 &Surface);

    /**
     * @brief Clamps @c Value between @c min and @c max
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs
     * "Vector3")
     */
    static Vector3 clamp(const Vector3 &Value, const Vector3 &min,
                         const Vector3 &max);

    /**
     * @brief Linear interpolates between @c Value1 and @c Value2 by @c Amount %
     * distance from @c Value1
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs
     * "Vector3")
     */
    static Vector3 lerp(const Vector3 &Value1, const Vector3 &Value2,
                        float Amount);

    /**
     * @brief Returns the cross product of @c Value1 and @c Value2
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3.cs
     * "Vector3")
     */
    static Vector3 cross(const Vector3 &Value1, const Vector3 &Value2);

    // https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3_Intrinsics.cs

    /**
     * @brief Returns the dot product of @c Value1 and @c Value2
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector3_Intrinsics.cs
     * "Vector3 Intrinsics")
     */
    static float dot(const Vector3 &Value1, const Vector3 &Value2);

    //! @brief Returns the smaller vector
    static Vector3 vmin(const Vector3 &Value1, const Vector3 &Value2);

    //! @brief Returns the larger vector
    static Vector3 vmax(const Vector3 &Value1, const Vector3 &Value2);

    //! @brief Returns a scalar vector of @c Value
    static Vector3 scalar(float Value);

    template <std::size_t I>
    inline std::tuple_element_t<I, Vector3> get() const {
        CALCDA_IF_CONSTEXPR(I == 0)
        return x;
        else CALCDA_IF_CONSTEXPR(I == 1) return y;
        else return z;
    }

    template <std::size_t I> inline std::tuple_element_t<I, Vector3> &get() {
        CALCDA_IF_CONSTEXPR(I == 0)
        return x;
        else CALCDA_IF_CONSTEXPR(I == 1) return y;
        else return z;
    }

    std::string toString() const;
};

using Point3 = Vector3;
} // namespace Calcda

namespace std {
template <>
struct tuple_size<Calcda::Vector3> : integral_constant<size_t, 3> {};

template <size_t I> struct tuple_element<I, Calcda::Vector3> {
    using type = float;
};

template <> struct hash<Calcda::Vector3> {
    size_t operator()(const Calcda::Vector3 &v) const noexcept {
        return Calcda::Internal::hash_combine(
            hash<float>()(v.x), hash<float>()(v.y), hash<float>()(v.z));
    }
};
} // namespace std

#endif // !CALCDA_VECTOR3_H