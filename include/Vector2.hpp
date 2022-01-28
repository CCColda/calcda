#ifndef CALCDA_VECTOR2_H
#define CALCDA_VECTOR2_H

#include "Intrinsic.hpp"

#include <string>
#include <utility>

namespace Calcda {
/**
 * @brief Class for describing 2 dimensional vectors
 * @see [Reference:
 * Intrinsics](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs)
 * @see [Reference:
 * Vector2](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2.cs)
 */
class Vector2 {
  public:
    float x;
    float y;

    friend class Vector3;
    friend class Vector4;

  public:
    // 0; 0 - Zero vector
    static const Vector2 Zero;

    // 1; 1 - One vector
    static const Vector2 One;

    // 1; 0 - X axisvector
    static const Vector2 UnitX;

    // 0; 1 - Y axisvector
    static const Vector2 UnitY;

  public:
    Vector2();
    Vector2(const Vector2 &Other);
    Vector2(float X, float Y);
    ~Vector2();

    //! @brief Returns the same vector (convinience)
    Vector2 xy() const;

    //! @brief Returns the Y and X elements
    Vector2 yx() const;

    //! @brief Returns a pointer to the beginning of the data
    float *getData();

    //! @brief Returns a const pointer to the beginning of the data
    const float *getData() const;

    //! @brief Adds two vectors together
    Vector2 &selfAdd(const Vector2 &Other);

    //! @brief Subtracts two vectors
    Vector2 &selfSubtract(const Vector2 &Other);

    //! @brief Multiplies two vectors
    Vector2 &selfMultiply(const Vector2 &Other);

    //! @brief Divides the elements of the current vector by @c Amount
    Vector2 &selfDivide(float Amount);

    //! @brief Divides two vectors
    Vector2 &selfDivide(const Vector2 &Other);

    //! @brief Normalizes the current vector
    Vector2 &selfNormalize();

    //! @brief Puts the vector in +X +Y space
    Vector2 &selfAbsolute();

    //! @brief Sets the X and Y elements to their square roots
    Vector2 &selfSqrt();

    //! @brief Negates the vector
    Vector2 &selfNegate();

    //! @brief Returns the two vectors added together
    /* [[nodiscard]] */ Vector2 add(const Vector2 &Other) const;

    //! @brief Returns the two vectors subtracted
    /* [[nodiscard]] */ Vector2 subtract(const Vector2 &Other) const;

    //! @brief Returns the two vectors multiplied
    /* [[nodiscard]] */ Vector2 multiply(const Vector2 &Other) const;

    //! @brief Returns the elements of the current vector divided by @c Amount
    /* [[nodiscard]] */ Vector2 divide(float Amount) const;

    //! @brief Returns the two vectors divided
    /* [[nodiscard]] */ Vector2 divide(const Vector2 &Other) const;

    //! @brief Returns the current vector normalized
    /* [[nodiscard]] */ Vector2 normalize() const;

    //! @brief Returns the vector negated
    /* [[nodiscard]] */ Vector2 negate() const;

    Vector2 operator+(const Vector2 &Other) const;
    Vector2 operator-(const Vector2 &Other) const;
    Vector2 operator*(const Vector2 &Other) const;
    Vector2 operator/(const Vector2 &Other) const;
    Vector2 operator/(float Amount) const;
    Vector2 operator-() const;

    Vector2 &operator=(const Vector2 &Other);
    Vector2 &operator+=(const Vector2 &Other);
    Vector2 &operator-=(const Vector2 &Other);
    Vector2 &operator*=(const Vector2 &Other);
    Vector2 &operator/=(const Vector2 &Other);
    Vector2 &operator/=(float Amount);

    bool operator==(const Vector2 &Other) const;
    bool operator!=(const Vector2 &Other) const;

    //! @brief Returns the vector in +X +Y space
    Vector2 absolute() const;

    //! @brief Returns the vector with its X and Y elements set to their square
    //! roots
    Vector2 sqrt() const;

    //! @brief Returns the distance between @c this and @c Other
    float distance(const Vector2 &Other) const;

    //! @brief Returns the length of the vector
    float length() const;

    //! @brief Returns the squared length of the vector
    float lengthSquared() const;

    /**
     * @brief Reflects @c Value on @c Surface
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2.cs
     * "Vector2")
     */
    static Vector2 reflect(const Vector2 &Value, const Vector2 &Surface);

    /**
     * @brief Sets @c Value between @c min and @c max in 2-dimensional space
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2.cs
     * "Vector2")
     */
    static Vector2 clamp(const Vector2 &Value, const Vector2 &min,
                         const Vector2 &max);

    /**
     * @brief Linear interpolates between @c Value1 and @c Value2, with @c
     * Amount % distance from @c Value1
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2.cs
     * "Vector2")
     */
    static Vector2 lerp(const Vector2 &Value1, const Vector2 &Value2,
                        float Amount);

    /**
     * @brief Returns the dot product of @c Value1 and @c Value2
     * @see
     * [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector2_Intrinsics.cs
     * "Vector2 Intrinsics")
     */
    static float dot(const Vector2 &Value1, const Vector2 &Value2);

    //! @brief Returns the smaller vector from @c Value1 to @c Value2
    static Vector2 vmin(const Vector2 &Value1, const Vector2 &Value2);

    //! @brief Returns the smaller vector from @c Value1 to @c Value2
    static Vector2 vmax(const Vector2 &Value1, const Vector2 &Value2);

    //! @brief Returns a scalar vector of @c Value
    static Vector2 scalar(float Value);

    template <std::size_t I>
    inline std::tuple_element_t<I, Vector2> get() const {
        CALCDA_IF_CONSTEXPR(I == 0)
        return x;
        else return y;
    }

    template <std::size_t I> inline std::tuple_element_t<I, Vector2> &get() {
        CALCDA_IF_CONSTEXPR(I == 0)
        return x;
        else return y;
    }

    std::string toString() const;
};

using Point2 = Vector2;
} // namespace Calcda

namespace std {
template <>
struct tuple_size<Calcda::Vector2> : integral_constant<size_t, 2> {};

template <size_t I> struct tuple_element<I, Calcda::Vector2> {
    using type = float;
};

template <> struct hash<Calcda::Vector2> {
    size_t operator()(const Calcda::Vector2 &v) const noexcept {
        return Calcda::Internal::hash_combine(hash<float>()(v.x),
                                              hash<float>()(v.y));
    }
};
} // namespace std

#endif // !CALCDA_VECTOR2_H