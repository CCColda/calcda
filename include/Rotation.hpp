#ifndef CALCDA_ROTATION_H
#define CALCDA_ROTATION_H

//! @brief [π](https://en.wikipedia.org/wiki/Pi) (double) value of pi accurate up to 11 decimal places
#define CALCDA_PI 3.14159265359

//! @brief [π](https://en.wikipedia.org/wiki/Pi) (float) value of pi accurate up to 11 decimal places
#define CALCDA_PIf 3.14159265359f

#include "Intrinsic.hpp"

namespace Calcda {
//! @brief Enumerator for handling axes
enum class Axis {
	X,
	Y,
	Z
};

namespace Conversion {
float CALCDA degreeToRadian(float Degree);
float CALCDA radianToDegree(float Radian);
} // namespace Conversion
} // namespace Calcda

#endif // !CALCDA_ROTATION_H