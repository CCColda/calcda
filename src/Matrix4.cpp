#include "Matrix4.hpp"
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>

namespace Calcda {

CALCDA Matrix4::Matrix4() {
    for (std::size_t index = 0; index < 16; ++index) {
        value.data[index] = 0.0f;
    }
}

CALCDA Matrix4::Matrix4(const std::initializer_list<float> &List) {
    std::size_t count = 0;
    std::size_t rowCount = 0;
    std::size_t colCount = 0;

    for (auto val : List) {
        value.matrix[rowCount][colCount] = val;

        ++count;
        ++colCount;

        if (colCount >= 4) {
            colCount = 0;

            ++rowCount;
        }

        if (count >= 16) {
            break;
        }
    }

    for (; count < 16; ++count) {
        value.matrix[rowCount][colCount] = 0.0f;

        ++colCount;

        if (colCount >= 4) {
            colCount = 0;

            ++rowCount;
        }
    }
}

CALCDA Matrix4::Matrix4(const Matrix4 &Other) {
    for (std::size_t index = 0; index < 16; ++index) {
        value.data[index] = Other.value.data[index];
    }
}

CALCDA Matrix4::Matrix4(const Matrix3 &Base) {
    for (std::size_t row = 0; row < 3; ++row) {
        for (std::size_t column = 0; column < 3; ++column) {
            value.matrix[row][column] = Base.value.matrix[row][column];
        }
    }

    value.matrix[3][0] = 0.0f;
    value.matrix[3][1] = 0.0f;
    value.matrix[3][2] = 0.0f;
    value.matrix[3][3] = 1.0f;
}

CALCDA Matrix4::~Matrix4() {}

Vector4 CALCDA Matrix4::r01() const {
    return Vector4(value.matrix[0][0], value.matrix[0][1], value.matrix[0][2],
                   value.matrix[0][3]);
}

Vector4 CALCDA Matrix4::r02() const {
    return Vector4(value.matrix[1][0], value.matrix[1][1], value.matrix[1][2],
                   value.matrix[1][3]);
}

Vector4 CALCDA Matrix4::r03() const {
    return Vector4(value.matrix[2][0], value.matrix[2][1], value.matrix[2][2],
                   value.matrix[2][3]);
}

Vector4 CALCDA Matrix4::r04() const {
    return Vector4(value.matrix[3][0], value.matrix[3][1], value.matrix[3][2],
                   value.matrix[3][3]);
}

Vector4 CALCDA Matrix4::c01() const {
    return Vector4(value.matrix[0][0], value.matrix[1][0], value.matrix[2][0],
                   value.matrix[3][0]);
}

Vector4 CALCDA Matrix4::c02() const {
    return Vector4(value.matrix[0][1], value.matrix[1][1], value.matrix[2][1],
                   value.matrix[3][1]);
}

Vector4 CALCDA Matrix4::c03() const {
    return Vector4(value.matrix[0][2], value.matrix[1][2], value.matrix[2][2],
                   value.matrix[3][2]);
}

Vector4 CALCDA Matrix4::c04() const {
    return Vector4(value.matrix[0][3], value.matrix[1][3], value.matrix[2][3],
                   value.matrix[3][3]);
}

float *Matrix4::getData() { return &value.data[0]; }

const float *Matrix4::getData() const { return &value.data[0]; }

Matrix4 &CALCDA Matrix4::selfMultiply(const Matrix4 &Other) {
    for (unsigned int i = 0U; i < 4U; i++) {
        for (unsigned int j = 0U; j < 4U; j++) {
            for (unsigned int k = 0U; k < 4U; k++) {
                value.matrix[i][k] *= Other.value.matrix[k][j];
            }
        }
    }

    return *this;
}

Matrix4 &CALCDA Matrix4::selfDivide(const Matrix4 &Other) {
    Matrix4 temporal = Other.calculateInverseTemporal();
    double determinant = Other.calculateDeterminant(&temporal);

    if (determinant != 0.0) {
        return selfMultiply(Other.inverse(&temporal, &determinant));
    } else {
        return *this;
    }
}

Matrix4 CALCDA Matrix4::calculateInverseTemporal() const {
    Matrix4 result;

    result.value.data[0] = (value.data[5] * value.data[10] * value.data[15] -
                            value.data[5] * value.data[11] * value.data[14] -
                            value.data[9] * value.data[6] * value.data[15] +
                            value.data[9] * value.data[7] * value.data[14] +
                            value.data[13] * value.data[6] * value.data[11] -
                            value.data[13] * value.data[7] * value.data[10]);

    result.value.data[4] = (-value.data[4] * value.data[10] * value.data[15] +
                            value.data[4] * value.data[11] * value.data[14] +
                            value.data[8] * value.data[6] * value.data[15] -
                            value.data[8] * value.data[7] * value.data[14] -
                            value.data[12] * value.data[6] * value.data[11] +
                            value.data[12] * value.data[7] * value.data[10]);

    result.value.data[8] = (value.data[4] * value.data[9] * value.data[15] -
                            value.data[4] * value.data[11] * value.data[13] -
                            value.data[8] * value.data[5] * value.data[15] +
                            value.data[8] * value.data[7] * value.data[13] +
                            value.data[12] * value.data[5] * value.data[11] -
                            value.data[12] * value.data[7] * value.data[9]);

    result.value.data[12] = (-value.data[4] * value.data[9] * value.data[14] +
                             value.data[4] * value.data[10] * value.data[13] +
                             value.data[8] * value.data[5] * value.data[14] -
                             value.data[8] * value.data[6] * value.data[13] -
                             value.data[12] * value.data[5] * value.data[10] +
                             value.data[12] * value.data[6] * value.data[9]);

    result.value.data[1] = (-value.data[1] * value.data[10] * value.data[15] +
                            value.data[1] * value.data[11] * value.data[14] +
                            value.data[9] * value.data[2] * value.data[15] -
                            value.data[9] * value.data[3] * value.data[14] -
                            value.data[13] * value.data[2] * value.data[11] +
                            value.data[13] * value.data[3] * value.data[10]);

    result.value.data[5] = (value.data[0] * value.data[10] * value.data[15] -
                            value.data[0] * value.data[11] * value.data[14] -
                            value.data[8] * value.data[2] * value.data[15] +
                            value.data[8] * value.data[3] * value.data[14] +
                            value.data[12] * value.data[2] * value.data[11] -
                            value.data[12] * value.data[3] * value.data[10]);

    result.value.data[9] = (-value.data[0] * value.data[9] * value.data[15] +
                            value.data[0] * value.data[11] * value.data[13] +
                            value.data[8] * value.data[1] * value.data[15] -
                            value.data[8] * value.data[3] * value.data[13] -
                            value.data[12] * value.data[1] * value.data[11] +
                            value.data[12] * value.data[3] * value.data[9]);

    result.value.data[13] = (value.data[0] * value.data[9] * value.data[14] -
                             value.data[0] * value.data[10] * value.data[13] -
                             value.data[8] * value.data[1] * value.data[14] +
                             value.data[8] * value.data[2] * value.data[13] +
                             value.data[12] * value.data[1] * value.data[10] -
                             value.data[12] * value.data[2] * value.data[9]);

    result.value.data[2] = (value.data[1] * value.data[6] * value.data[15] -
                            value.data[1] * value.data[7] * value.data[14] -
                            value.data[5] * value.data[2] * value.data[15] +
                            value.data[5] * value.data[3] * value.data[14] +
                            value.data[13] * value.data[2] * value.data[7] -
                            value.data[13] * value.data[3] * value.data[6]);

    result.value.data[6] = (-value.data[0] * value.data[6] * value.data[15] +
                            value.data[0] * value.data[7] * value.data[14] +
                            value.data[4] * value.data[2] * value.data[15] -
                            value.data[4] * value.data[3] * value.data[14] -
                            value.data[12] * value.data[2] * value.data[7] +
                            value.data[12] * value.data[3] * value.data[6]);

    result.value.data[10] = (value.data[0] * value.data[5] * value.data[15] -
                             value.data[0] * value.data[7] * value.data[13] -
                             value.data[4] * value.data[1] * value.data[15] +
                             value.data[4] * value.data[3] * value.data[13] +
                             value.data[12] * value.data[1] * value.data[7] -
                             value.data[12] * value.data[3] * value.data[5]);

    result.value.data[14] = (-value.data[0] * value.data[5] * value.data[14] +
                             value.data[0] * value.data[6] * value.data[13] +
                             value.data[4] * value.data[1] * value.data[14] -
                             value.data[4] * value.data[2] * value.data[13] -
                             value.data[12] * value.data[1] * value.data[6] +
                             value.data[12] * value.data[2] * value.data[5]);

    result.value.data[3] = (-value.data[1] * value.data[6] * value.data[11] +
                            value.data[1] * value.data[7] * value.data[10] +
                            value.data[5] * value.data[2] * value.data[11] -
                            value.data[5] * value.data[3] * value.data[10] -
                            value.data[9] * value.data[2] * value.data[7] +
                            value.data[9] * value.data[3] * value.data[6]);

    result.value.data[7] = (value.data[0] * value.data[6] * value.data[11] -
                            value.data[0] * value.data[7] * value.data[10] -
                            value.data[4] * value.data[2] * value.data[11] +
                            value.data[4] * value.data[3] * value.data[10] +
                            value.data[8] * value.data[2] * value.data[7] -
                            value.data[8] * value.data[3] * value.data[6]);

    result.value.data[11] = (-value.data[0] * value.data[5] * value.data[11] +
                             value.data[0] * value.data[7] * value.data[9] +
                             value.data[4] * value.data[1] * value.data[11] -
                             value.data[4] * value.data[3] * value.data[9] -
                             value.data[8] * value.data[1] * value.data[7] +
                             value.data[8] * value.data[3] * value.data[5]);

    result.value.data[15] = (value.data[0] * value.data[5] * value.data[10] -
                             value.data[0] * value.data[6] * value.data[9] -
                             value.data[4] * value.data[1] * value.data[10] +
                             value.data[4] * value.data[2] * value.data[9] +
                             value.data[8] * value.data[1] * value.data[6] -
                             value.data[8] * value.data[2] * value.data[5]);

    return result;
}

double CALCDA Matrix4::calculateDeterminant(Matrix4 *iTemporal) const {
    Matrix4 temporal;
    if (iTemporal == nullptr) {
        temporal = calculateInverseTemporal();
    } else {
        temporal = *iTemporal;
    }

    return value.data[0] * temporal.value.data[0] +
           value.data[1] * temporal.value.data[4] +
           value.data[2] * temporal.value.data[8] +
           value.data[3] * temporal.value.data[1];
}

Matrix4 CALCDA Matrix4::inverse(Matrix4 *iTemporal,
                                double *iDeterminant) const {
    Matrix4 result;

    Matrix4 temporal;
    double determinant = 0.0;

    if (iTemporal == nullptr) {
        temporal = calculateInverseTemporal();
    } else {
        temporal = *iTemporal;
    }

    if (iDeterminant == nullptr) {
        determinant = calculateDeterminant(&temporal);
    } else {
        determinant = *iDeterminant;
    }

    if (determinant == 0.0) {
        return Matrix4::Identity;
    } else {
        determinant = 1.0 / determinant;

        for (unsigned int i = 0U; i < 16U; i++) {
            result.value.data[i] =
                static_cast<float>(temporal.value.data[i] * determinant);
        }

        return result;
    }
}

Matrix4 CALCDA Matrix4::divide(const Matrix4 &Other) const {
    Matrix4 Temporal = Other.calculateInverseTemporal();
    double Determinant = Other.calculateDeterminant(&Temporal);

    if (Determinant == 0.0) {
        return Matrix4();
    } else {
        return multiply(Other.inverse(&Temporal, &Determinant));
    }
}

Vector4 CALCDA Matrix4::multiply(const Vector4 &Other) const {
    const float X = (value.m00 * Other.x) + (value.m01 * Other.y) +
                    (value.m02 * Other.z) + (value.m03 * Other.w);
    const float Y = (value.m10 * Other.x) + (value.m11 * Other.y) +
                    (value.m12 * Other.z) + (value.m13 * Other.w);
    const float Z = (value.m20 * Other.x) + (value.m21 * Other.y) +
                    (value.m22 * Other.z) + (value.m23 * Other.w);
    const float W = (value.m30 * Other.x) + (value.m31 * Other.y) +
                    (value.m32 * Other.z) + (value.m33 * Other.w);

    return Vector4(X, Y, Z, W);
}

Matrix4 CALCDA Matrix4::multiply(const Matrix4 &Other) const {
    Matrix4 result;

    for (unsigned int i = 0U; i < 4U; i++) {
        for (unsigned int j = 0U; j < 4U; j++) {
            for (unsigned int k = 0U; k < 4U; k++) {
                result.value.matrix[i][j] +=
                    value.matrix[i][k] * Other.value.matrix[k][j];
            }
        }
    }
    return result;
}

Matrix4 CALCDA Matrix4::transpose() const {
    return Matrix4{value.m00, value.m10, value.m20, value.m30,
                   value.m01, value.m11, value.m21, value.m31,
                   value.m02, value.m12, value.m22, value.m32,
                   value.m03, value.m13, value.m23, value.m33};
}

Matrix4 CALCDA Matrix4::negate() const {
    return Matrix4{-value.m00, -value.m01, -value.m02, -value.m03,
                   -value.m10, -value.m11, -value.m12, -value.m13,
                   -value.m20, -value.m21, -value.m22, -value.m23,
                   -value.m30, -value.m31, -value.m32, -value.m33};
}

Matrix4 CALCDA Matrix4::operator-() const { return negate(); }

Matrix4 CALCDA Matrix4::operator/(const Matrix4 &x) const { return divide(x); }

Matrix4 CALCDA Matrix4::operator*(const Matrix4 &x) const {
    return multiply(x);
}

Vector4 CALCDA Matrix4::operator*(const Vector4 &x) const {
    return multiply(x);
}

Matrix4 &CALCDA Matrix4::operator/=(const Matrix4 &x) { return selfDivide(x); }

Matrix4 &CALCDA Matrix4::operator*=(const Matrix4 &x) {
    return selfMultiply(x);
}

Matrix4 &CALCDA Matrix4::operator=(const Matrix4 &Other) {
    for (unsigned int Iterator = 0; Iterator < 16; ++Iterator) {
        value.data[Iterator] = Other.value.data[Iterator];
    }
    return *this;
}

bool CALCDA Matrix4::operator==(const Matrix4 &Other) const {
    return (value.m00 == Other.value.m00 && value.m01 == Other.value.m01 &&
            value.m02 == Other.value.m02 && value.m03 == Other.value.m03 &&
            value.m10 == Other.value.m10 && value.m11 == Other.value.m11 &&
            value.m12 == Other.value.m12 && value.m13 == Other.value.m13 &&
            value.m20 == Other.value.m20 && value.m21 == Other.value.m21 &&
            value.m22 == Other.value.m22 && value.m23 == Other.value.m23 &&
            value.m30 == Other.value.m30 && value.m31 == Other.value.m31 &&
            value.m32 == Other.value.m32 && value.m33 == Other.value.m33);
}

bool CALCDA Matrix4::operator!=(const Matrix4 &Other) const {
    return (value.m00 != Other.value.m00 || value.m01 != Other.value.m01 ||
            value.m02 != Other.value.m02 || value.m03 != Other.value.m03 ||
            value.m10 != Other.value.m10 || value.m11 != Other.value.m11 ||
            value.m12 != Other.value.m12 || value.m13 != Other.value.m13 ||
            value.m20 != Other.value.m20 || value.m21 != Other.value.m21 ||
            value.m22 != Other.value.m22 || value.m23 != Other.value.m23 ||
            value.m30 != Other.value.m30 || value.m31 != Other.value.m31 ||
            value.m32 != Other.value.m32 || value.m33 != Other.value.m33);
}

Matrix4 CALCDA Matrix4::rotation(Axis x, double value) {
    switch (x) {
        case Axis::X:
            return Matrix4{1.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           static_cast<float>(std::cos(-value)),
                           static_cast<float>(-std::sin(-value)),
                           0.0f,
                           0.0f,
                           static_cast<float>(std::sin(-value)),
                           static_cast<float>(std::cos(-value)),
                           0.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           1.0f};

        case Axis::Y:
            return Matrix4{static_cast<float>(std::cos(-value)),
                           0.0f,
                           static_cast<float>(std::sin(-value)),
                           0.0f,
                           0.0f,
                           1.0f,
                           0.0f,
                           0.0f,
                           static_cast<float>(-std::sin(-value)),
                           0.0f,
                           static_cast<float>(std::cos(-value)),
                           0.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           1.0f};

        case Axis::Z:
            return Matrix4{static_cast<float>(std::cos(-value)),
                           static_cast<float>(-std::sin(-value)),
                           0.0f,
                           0.0f,
                           static_cast<float>(std::sin(-value)),
                           static_cast<float>(std::cos(-value)),
                           0.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           1.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           0.0f,
                           1.0f};
        default:
            return Matrix4::Identity;
    }
}

Matrix4 CALCDA Matrix4::translation(float X, float Y, float Z) {
    Matrix4 result = Matrix4::Identity;

    result.value.m03 = X;
    result.value.m13 = Y;
    result.value.m23 = Z;

    return result;
}

Matrix4 CALCDA Matrix4::translation(Vector3 Point) {
    Matrix4 result = Matrix4::Identity;

    result.value.m03 = Point.x;
    result.value.m13 = Point.y;
    result.value.m23 = Point.z;

    return result;
}

Matrix4 CALCDA Matrix4::scale(float X, float Y, float Z) {
    Matrix4 result = Matrix4::Identity;

    result.value.m00 = X;
    result.value.m11 = Y;
    result.value.m22 = Z;

    return result;
}

Matrix4 CALCDA Matrix4::scale(Vector3 Point) {
    Matrix4 result = Matrix4::Identity;

    result.value.m00 = Point.x;
    result.value.m11 = Point.y;
    result.value.m22 = Point.z;

    return result;
}

Matrix4 CALCDA Matrix4::orthographic(float left, float right, float top,
                                     float bottom, float nearplane,
                                     float farplane) {

    return Matrix4{2.0f / (right - left),
                   0.0f,
                   0.0f,
                   -((right + left) / (right - left)),
                   0.0f,
                   2.0f / (top - bottom),
                   0.0f,
                   -((top + bottom) / (top - bottom)),
                   0.0f,
                   0.0f,
                   -2.0f / (farplane - nearplane),
                   -((farplane + nearplane) / (farplane - nearplane)),
                   0.0f,
                   0.0f,
                   0.0f,
                   1.0f};
}

// https://www.opengl.org/discussion_boards/showthread.php/172280-Constructing-an-orthographic-matrix-for-2D-drawing

Matrix4 CALCDA Matrix4::lookAt(Vector3 Eye, Vector3 Center, Vector3 Up) {
    const Vector3 forward = (Center - Eye).normalize();
    const Vector3 side = Vector3::cross(forward, Up).normalize();
    const Vector3 top = Vector3::cross(side, forward);

    return Matrix4{side.x, side.y, side.z,     0.0f,       top.x,      top.y,
                   top.z,  0.0f,   -forward.x, -forward.y, -forward.z, 0.0f,
                   0.0f,   0.0f,   0.0f,       1.0f} *
           Matrix4::translation(-Eye);
}

Matrix4 CALCDA Matrix4::frustum(float left, float right, float top,
                                float bottom, float nearPlane, float farPlane) {
    /* ~[glhFrustumf2] : https://www.khronos.org/opengl/wiki/GluPerspective_code
     */

    Matrix4 result;

    result.value.matrix[0][0] = (2.0f * nearPlane) / (right - left);
    result.value.matrix[1][0] = 0.0f;
    result.value.matrix[2][0] = 0.0f;
    result.value.matrix[3][0] = 0.0f;
    result.value.matrix[0][1] = 0.0f;
    result.value.matrix[1][1] = (2.0f * nearPlane) / (top - bottom);
    result.value.matrix[2][1] = 0.0f;
    result.value.matrix[3][1] = 0.0f;
    result.value.matrix[0][2] = (right + left) / (right - left);
    result.value.matrix[1][2] = (top + bottom) / (top - bottom);
    result.value.matrix[2][2] =
        (-farPlane - nearPlane) / (farPlane - nearPlane);
    result.value.matrix[3][2] = -1.0f;
    result.value.matrix[0][3] = 0.0f;
    result.value.matrix[1][3] = 0.0f;
    result.value.matrix[2][3] =
        (-2.0f * nearPlane * farPlane) / (farPlane - nearPlane);
    result.value.matrix[3][3] = 0.0f;

    return result;
}

Matrix4 CALCDA Matrix4::perspective(float fovyInRadians, float aspectRatio,
                                    float nearPlane, float farPlane) {
    float ymax = nearPlane * tanf(fovyInRadians);
    float ymin = -ymax;
    float xmin = -ymax * aspectRatio;
    float xmax = ymax * aspectRatio;

    return frustum(xmin, xmax, ymin, ymax, nearPlane, farPlane);
}

Matrix4 CALCDA Matrix4::perspectiveFlippedY(float fovyInRadians,
                                            float aspectRatio, float nearPlane,
                                            float farPlane) {
    float ymax = nearPlane * tanf(fovyInRadians);
    float ymin = -ymax;
    float xmin = -ymax * aspectRatio;
    float xmax = ymax * aspectRatio;

    return frustum(xmin, xmax, ymax, ymin, nearPlane, farPlane);
}

Matrix4 CALCDA Matrix4::projection(float left, float right, float top,
                                   float bottom, float nearPlane,
                                   float farPlane) {
    return Matrix4{(2 * nearPlane) / (right - left),
                   0.0,
                   (right + left) / (right - left),
                   0.0,
                   0.0,
                   (2 * nearPlane) / (top - bottom),
                   (top + bottom) / (top - bottom),
                   0.0,
                   0.0,
                   0.0,
                   -(farPlane + nearPlane) / (farPlane - nearPlane),
                   (-2.0f * farPlane * nearPlane) / (farPlane - nearPlane),
                   0.0,
                   0.0,
                   -1.0,
                   0.0};
}

std::string CALCDA Matrix4::toString() const {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << "[";

    for (std::size_t i = 0; i < 4; ++i) {
        stream << "{";

        for (std::size_t j = 0; j < 4; ++j) {
            stream << value.matrix[i][j];

            if (j < 3) {
                stream << ", ";
            }
        }

        stream << "}";

        if (i < 3) {
            stream << ", ";
        }
    }

    stream << "]";

    return stream.str();
}

std::string CALCDA Matrix4::toStringO(unsigned int Padding,
                                      unsigned int Precision) const {
    const std::string paddingString = std::string(Padding, ' ');

    std::stringstream stream;
    stream << std::fixed << std::setprecision(Precision);

    for (std::size_t i = 0; i < 4; ++i) {
        stream << paddingString;
        for (std::size_t j = 0; j < 4; ++j) {
            stream << (value.matrix[i][j] >= 0.0f ? " " : "")
                   << value.matrix[i][j];

            if (j < 3) {
                stream << "  ";
            }
        }

        if (i < 3) {
            stream << "\n";
        }
    }

    return stream.str();
}

//* STATIC VARIABLE *//

const Matrix4 Matrix4::Identity =
    Matrix4{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
} // namespace Calcda