#ifndef CALCDA_MATRIX4_H
#define CALCDA_MATRIX4_H

#include <initializer_list> // std::initializer_list

#include "Intrinsic.hpp"

#include "Matrix3.hpp"  // Calcda::Matrix3
#include "Rotation.hpp" // Calcda::Rotation
#include "Vector3.hpp"  // Calcda::Vector3
#include "Vector4.hpp"  // Calcda::Vector4

#include <string>

namespace Calcda {
//! @brief Class for handling 4x4 matrices
class Matrix4 {
  public:
    //! @brief Containing union type
    union container_t {
        struct {
            float m00;
            float m01;
            float m02;
            float m03;
            float m10;
            float m11;
            float m12;
            float m13;
            float m20;
            float m21;
            float m22;
            float m23;
            float m30;
            float m31;
            float m32;
            float m33;
        };

        //! @brief 4 by 4 layout
        float matrix[4][4];

        //! @brief row matrix layout
        float data[16];
    } value;

  public:
    Matrix4();
    Matrix4(const std::initializer_list<float> &List);
    Matrix4(const Matrix4 &Other);
    Matrix4(const Matrix3 &Base);
    ~Matrix4();

    //! @brief Requests the 1st row
    Vector4 r01() const;

    //! @brief Requests the 2nd row
    Vector4 r02() const;

    //! @brief Requests the 3rd row
    Vector4 r03() const;

    //! @brief Requests the 4th row
    Vector4 r04() const;

    //! @brief Requests the 1st column
    Vector4 c01() const;

    //! @brief Requests the 2nd column
    Vector4 c02() const;

    //! @brief Requests the 3rd column
    Vector4 c03() const;

    //! @brief Requests the 4th column
    Vector4 c04() const;

    //! @brief Returns a pointer to the beginning of the data
    float *getData();

    //! @brief Returns a const pointer to the beginning of the data
    const float *getData() const;

    //! @brief Multiplies the matrix by @c Other
    Matrix4 &selfMultiply(const Matrix4 &Other);

    //! @brief Divides the matrix by @c Other (multiplies by the inverse of @c
    //! Other)
    Matrix4 &selfDivide(const Matrix4 &Other);

    //! @brief Calculates the inverse temporal of the current matrix
    Matrix4 calculateInverseTemporal() const;

    /**
     * @brief Calculates the determinant for the current matrix
     * @param InverseTemporal inverse temporal of the current matrix, optional
     */
    double calculateDeterminant(Matrix4 *InverseTemporal = nullptr) const;

    /**
     * @brief Calculates the inverse of the current matrix
     * @param InverseTemporal Optional; inverse temporal of the matrix
     * @param Determinant Optional; determinant of the matrix
     */
    Matrix4 inverse(Matrix4 *InverseTemporal = nullptr,
                    double *Determinant = nullptr) const;

    //! @brief Returns the current matrix divided by @c Other
    Matrix4 divide(const Matrix4 &Other) const;

    //! @brief Returns the current matrix multiplied by @c Other
    Matrix4 multiply(const Matrix4 &Other) const;

    //! @brief Multiplies the current matrix with the vector @c Other, then
    //! returns the vector result
    Vector4 multiply(const Vector4 &Other) const;

    //! @brief Transposes the current matrix (flips it along its top-left to
    //! bottom-right diagonal)
    Matrix4 transpose() const;

    //! @brief Negates every value in the matrix
    Matrix4 negate() const;

    Matrix4 operator*(const Matrix4 &Other) const;
    Vector4 operator*(const Vector4 &Other) const;
    Matrix4 operator/(const Matrix4 &Other) const;
    Matrix4 operator-() const;

    Matrix4 &operator*=(const Matrix4 &Other);
    Matrix4 &operator/=(const Matrix4 &Other);
    Matrix4 &operator=(const Matrix4 &Other);

    bool operator==(const Matrix4 &Other) const;
    bool operator!=(const Matrix4 &Other) const;

    /**
     * @brief Calculates a rotation on @c RotateAxis
     * @param RotateAxis X, Y, or Z axis, for the rotation to be calculated on
     * @param Amount Amount of rotation, in radians
     */
    static Matrix4 rotation(Axis RotateAxis, double Amount);

    //! @brief Transforms the matrix with @c X, @c Y, @c Z
    static Matrix4 translation(float X, float Y, float Z);

    //! @brief Transforms the matrix with @c Point.x, @c Point.y, @c Point.z
    static Matrix4 translation(Vector3 Point);

    //! @brief Scales the matrix with @c X, @c Y, @c Z
    static Matrix4 scale(float X, float Y, float Z);

    //! @brief Scales the matrix with @c Point.x, @c Point.y, @c Point.z
    static Matrix4 scale(Vector3 Point);

    /**
     * @brief Returns an orthographic projection matrix.
     * [orthographic
     * projection](https://en.wikipedia.org/wiki/Orthographic_projection)
     *
     * @param Left Left side of the view box
     * @param Right Right side of the view box
     * @param Top Top side of the view box
     * @param Bottom Bottom side of the view box
     * @param Near Near plane
     * @param Far Far plane
     */
    static Matrix4 orthographic(float Left, float Right, float Top,
                                float Bottom, float Near, float Far);

    /**
     * @brief Returns a camera projection
     *
     * @param EyePosition Position of the eye
     * @param Center Position to look at
     * @param Up Up direction
     */
    static Matrix4 lookAt(Vector3 EyePosition, Vector3 Center, Vector3 Up);

    /**
     * @brief Returns a frustum projection
     * [Viewing frustum](https://en.wikipedia.org/wiki/Viewing_frustum)
     */
    static Matrix4 frustum(float Left, float Right, float Top, float Bottom,
                           float Near, float Far);

    /**
     * @brief Returns a perspective projection, with @c Fov in radians
     *
     * @param Fov Field of View, measured in degrees
     * @param AspectRatio Aspect ratio of the projection
     * @param Near Near plane
     * @param Far Far plane
     */
    static Matrix4 perspective(float Fov, float AspectRatio, float Near,
                               float Far);

    /**
     * @brief Returns a perspective projection, with @c Fov in radians, flipped
     * vertically
     *
     * @param Fov Field of View, measured in degrees
     * @param AspectRatio Aspect ratio of the projection
     * @param Near Near plane
     * @param Far Far plane
     */
    static Matrix4 perspectiveFlippedY(float Fov, float AspectRatio, float Near,
                                       float Far);

    //! @brief Returns a projection matrix
    static Matrix4 projection(float Left, float Right, float Top, float Bottom,
                              float Near, float Far);

    std::string toString() const;
    std::string toStringO(unsigned int Padding = 0,
                          unsigned int Precision = 2) const;

    //! @brief Identity matrix, 0 everywhere, except the top-left to
    //! bottom-right diagonal, where it is 1
    static const Matrix4 Identity;
};

} // namespace Calcda

#endif // !CALCDA_MATRIX4_H