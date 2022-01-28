#ifndef CALCDA_MATRIX3_H
#define CALCDA_MATRIX3_H

#include <initializer_list> // std::initializer_list

#include "Intrinsic.hpp"

#include "Rotation.hpp" // Calcda::Rotation
#include "Vector2.hpp"  // Calcda::Vector2
#include "Vector3.hpp"  // Calcda::Vector3

#include <string>

namespace Calcda {
//! @brief Class for handling 3x3 matrices
class Matrix3 {
  public:
    //! @brief Containing union type
    union container_t {
        //! @brief Per-item layout
        struct {
            float m00;
            float m01;
            float m02;
            float m10;
            float m11;
            float m12;
            float m20;
            float m21;
            float m22;
        };

        //! @brief 3 by 3 layout
        float matrix[3][3];

        //! @brief row matrix layout
        float data[9];
    } value;

  public:
    Matrix3();
    Matrix3(const std::initializer_list<float> &List);
    Matrix3(const Matrix3 &Other);
    ~Matrix3();

    //! @brief Requests the 1st row
    Vector3 r01() const;

    //! @brief Requests the 2nd row
    Vector3 r02() const;

    //! @brief Requests the 3rd row
    Vector3 r03() const;

    //! @brief Requests the 1st column
    Vector3 c01() const;

    //! @brief Requests the 2nd column
    Vector3 c02() const;

    //! @brief Requests the 3rd column
    Vector3 c03() const;

    //! @brief Returns a pointer to the beginning of the data
    float *getData();

    //! @brief Returns a const pointer to the beginning of the data
    const float *getData() const;

    //! @brief Multiplies the matrix by @c Other
    Matrix3 &selfMultiply(const Matrix3 &Other);

    //! @brief Divides the matrix by @c Other (multiplies by the inverse of @c
    //! Other)
    Matrix3 &selfDivide(const Matrix3 &Other);

    //! @brief Calculates the adjugate of the current matrix
    Matrix3 calculateAdjugate() const;

    //! @brief Calculates the determinant for the current matrix
    double calculateDeterminant() const;

    /**
     * @brief Calculates the inverse of the current matrix
     * @param adjugate Optional; adjugate of the matrix
     * @param determinant Optional; determinant of the matrix
     */
    Matrix3 inverse(Matrix3 *adjugate = nullptr,
                    double *determinant = nullptr) const;

    //! @brief Returns the current matrix divided by @c Other
    Matrix3 divide(const Matrix3 &Other) const;

    //! @brief Returns the current matrix multiplied by @c Other
    Matrix3 multiply(const Matrix3 &Other) const;

    //! @brief Multiplies the current matrix with the vector @c Other, then
    //! returns the vector result
    Vector3 multiply(const Vector3 &Other) const;

    //! @brief Transposes the current matrix (flips it along its top-left to
    //! bottom-right diagonal)
    Matrix3 transpose() const;

    //! @brief Negates every value in the matrix
    Matrix3 negate() const;

    Matrix3 operator*(const Matrix3 &Other) const;
    Vector3 operator*(const Vector3 &Other) const;
    Matrix3 operator/(const Matrix3 &Other) const;
    Matrix3 operator-() const;

    Matrix3 &operator*=(const Matrix3 &Other);
    Matrix3 &operator/=(const Matrix3 &Other);
    Matrix3 &operator=(const Matrix3 &Other);

    bool operator==(const Matrix3 &Other) const;
    bool operator!=(const Matrix3 &Other) const;

    /**
     * @brief Calculates a rotation on @c RotateAxis
     * @param RotateAxis X, Y, or Z axis, for the rotation to be calculated on
     * @param Amount Amount of rotation, in radians
     */
    static Matrix3 rotation(Axis RotateAxis, double Amount);

    //! @brief Transforms the matrix with @c X, @c Y
    static Matrix3 translation(float X, float Y);

    //! @brief Transforms the matrix with @c Point.x, @c Point.y
    static Matrix3 translation(Vector2 Point);

    //! @brief Scales the matrix with @c X, @c Y
    static Matrix3 scale(float X, float Y);

    //! @brief Scales the matrix with @c Point.x, @c Point.y
    static Matrix3 scale(Vector2 Point);

    std::string toString() const;
    std::string toStringO(unsigned int Padding = 0,
                          unsigned int Precision = 2) const;

    //! @brief Identity matrix, 0 everywhere, except the top-left to
    //! bottom-right diagonal, where it is 1
    static const Matrix3 Identity;
};

} // namespace Calcda

#endif // !CALCDA_MATRIX4_H