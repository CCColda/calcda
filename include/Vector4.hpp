#ifndef CALCDA_VECTOR4_H
#define CALCDA_VECTOR4_H

#include "Intrinsic.hpp"
#include "Vector2.hpp" // Calcda::Vector2
#include "Vector3.hpp" // Calcda::Vector3

#include <string>
#include <utility>

namespace Calcda {

/**
 * @brief Class for 4-dimensional vectors
 * @see [Reference: Intrinsics](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4_Intrinsics.cs)
 * @see [Reference: Vector4](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4.cs)
 */
class CALCDA Vector4 {
public:
	float x;
	float y;
	float z;
	float w;

public:
	// 0; 0; 0; 0 - Zero vector
	static const Vector4 Zero;

	// 1; 1; 1; 1 - "One" vector
	static const Vector4 One;

	// 1; 0; 0; 0 - X axis vector
	static const Vector4 UnitX;

	// 0; 1; 0; 0 - Y axis vector
	static const Vector4 UnitY;

	// 0; 0; 1; 0 - Z axis vector
	static const Vector4 UnitZ;

	// 0; 0; 0; 1 - W axis vector
	static const Vector4 UnitW;

public:
	Vector4();
	Vector4(float X, float Y, float Z, float W);
	Vector4(Vector2 XY, Vector2 ZW);
	Vector4(Vector3 XYZ, float W);
	Vector4(float X, Vector3 YZW);
	Vector4(const Vector4 &Other);
	~Vector4();

	//! @brief Returns the X and Y elements
	Vector2 xy() const;

	//! @brief Returns the Y and Z elements
	Vector2 yz() const;

	//! @brief Returns the Z and W elements
	Vector2 zw() const;

	//! @brief Returns the X, Y and Z elements
	Vector3 xyz() const;

	//! @brief Returns the Y, Z and W elements
	Vector3 yzw() const;

	//! @brief Returns the same vector
	Vector4 xyzw() const;

	//! @brief Returns the W, Z, Y, and X elements
	Vector4 wzyx() const;

	//! @brief Returns a pointer to the beginning of the data
	float *getData();

	//! @brief Returns a const pointer to the beginning of the data
	const float *getData() const;

	//! @brief Adds the two vectors together
	Vector4 &selfAdd(const Vector4 &Other);

	//! @brief Subtracts @c Other from the current vector
	Vector4 &selfSubtract(const Vector4 &Other);

	//! @brief Multiplies the current vector with @c Other
	Vector4 &selfMultiply(const Vector4 &Other);

	//! @brief Divides the elements of the current vector with @c Amount
	Vector4 &selfDivide(float Amount);

	//! @brief Divides the current vector with @c Other
	Vector4 &selfDivide(const Vector4 &Other);

	//! @brief Normalizes the current vector
	Vector4 &selfNormalize();

	//! @brief Transforms the vector to +X, +Y, +Z, +W space
	Vector4 &selfAbsolute();

	//! @brief Sets the elements to their squares
	Vector4 &selfSqrt();

	//! @brief Negates the vector
	Vector4 &selfNegate();

	//! @brief Adds the two vectors together
	/* [[nodiscard]] */ Vector4 add(const Vector4 &Other) const;

	//! @brief Subtracts @c Other from the current vector
	/* [[nodiscard]] */ Vector4 subtract(const Vector4 &Other) const;

	//! @brief Multiplies the current vector with @c Other
	/* [[nodiscard]] */ Vector4 multiply(const Vector4 &Other) const;

	//! @brief Divides the elements of the current vector with @c Amount
	/* [[nodiscard]] */ Vector4 divide(float Amount) const;

	//! @brief Divides the current vector with @c Other, returns the result
	/* [[nodiscard]] */ Vector4 divide(const Vector4 &Other) const;

	//! @brief Normalizes the current vector
	/* [[nodiscard]] */ Vector4 normalize() const;

	//! @brief Negates the vector
	/* [[nodiscard]] */ Vector4 negate() const;

	Vector4 operator+(const Vector4 &Other) const;
	Vector4 operator-(const Vector4 &Other) const;
	Vector4 operator*(const Vector4 &Other) const;
	Vector4 operator/(const Vector4 &Other) const;
	Vector4 operator/(float Amount) const;
	Vector4 operator-() const;

	Vector4 &operator=(const Vector4 &Other);
	Vector4 &operator+=(const Vector4 &Other);
	Vector4 &operator-=(const Vector4 &Other);
	Vector4 &operator*=(const Vector4 &Other);
	Vector4 &operator/=(const Vector4 &Other);
	Vector4 &operator/=(float Amount);

	bool operator==(const Vector4 &Other) const;
	bool operator!=(const Vector4 &Other) const;

	//! @brief Transforms the vector to +X, +Y, +Z, +W space, returns it
	Vector4 absolute() const;

	//! @brief Returns a vector with the square roots of the current vector's elements
	Vector4 sqrt() const;

	//! @brief distance between the current vector and @c Other
	float distance(const Vector4 &Other) const;

	//! @brief Returns the length of the vector
	float length() const;

	//! @brief Returns the squared length of the vector
	float lengthSquared() const;

	/**
	 * @brief Reflects @c Value on @c Surface
	 * @see [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4.cs "Vector4")
	 * @see [Stack Exchange](https://math.stackexchange.com/a/13266)
	 */
	static Vector4 reflect(const Vector4 &Value, const Vector4 &Surface);

	/**
	 * @brief Clamps @c Value between @c min and @c max
	 * @see [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4.cs "Vector4")
	 */
	static Vector4 clamp(const Vector4 &Value, const Vector4 &min, const Vector4 &max);

	/**
	 * @brief Linear interpolates between @c Value1 and @c Value2 by @c Amount % distance from @c Value1
	 * @see [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4.cs "Vector4")
	 */
	static Vector4 lerp(const Vector4 &Value1, const Vector4 &Value2, float Amount);

	/**
	 * @brief Returns the dot product of @c Value1 and @c Value2
	 * @see [Reference](https://referencesource.microsoft.com/#System.Numerics/System/Numerics/Vector4_Intrinsics.cs "Vector4 Intrinsics")
	 */
	static float dot(const Vector4 &Value1, const Vector4 &Value2);

	//! @brief Returns the smaller vector
	static Vector4 vmin(const Vector4 &Value1, const Vector4 &Value2);

	//! @brief Returns the larger vector
	static Vector4 vmax(const Vector4 &Value1, const Vector4 &Value2);

	//! @brief Returns a scalar of @c Value
	static Vector4 scalar(float Value);

	template <std::size_t I>
	inline std::tuple_element_t<I, Vector4> get() const
	{
		CALCDA_IF_CONSTEXPR (I == 0)
			return x;
		else CALCDA_IF_CONSTEXPR (I == 1)
			return y;
		else CALCDA_IF_CONSTEXPR (I == 2)
			return z;
		else
			return w;
	}

	template <std::size_t I>
	inline std::tuple_element_t<I, Vector4> &get()
	{
		CALCDA_IF_CONSTEXPR (I == 0)
			return x;
		else CALCDA_IF_CONSTEXPR (I == 1)
			return y;
		else CALCDA_IF_CONSTEXPR (I == 2)
			return z;
		else
			return w;
	}

	std::string toString() const;
};

using Point4 = Vector4;
} // namespace Calcda

namespace std {
template <>
struct CALCDA tuple_size<Calcda::Vector4> : integral_constant<size_t, 4> {
};

template <size_t I>
struct CALCDA tuple_element<I, Calcda::Vector4> {
	using type = float;
};

template <>
struct CALCDA hash<Calcda::Vector4> {
	size_t operator()(const Calcda::Vector4 &v) const noexcept
	{
		return Calcda::Internal::hash_combine(hash<float>()(v.x), hash<float>()(v.y), hash<float>()(v.z), hash<float>()(v.w));
	}
};
} // namespace std

#endif // !CALCDA_VECTOR4_H