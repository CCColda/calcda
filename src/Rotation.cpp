#include "Rotation.hpp"

namespace Calcda {
namespace Conversion {
float CALCDA degreeToRadian(float Degree)
{
	return Degree * (CALCDA_PIf / 180.0f);
}

float CALCDA radianToDegree(float Radian)
{
	return Radian / (CALCDA_PIf / 180.0f);
}
} // namespace Conversion
} // namespace Calcda