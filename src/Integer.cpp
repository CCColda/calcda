#include "Integer.hpp"
#include <cstddef>

namespace Calcda {

namespace Integer {
std::size_t CALCDA countDigits(std::int64_t Signed, std::size_t Radix)
{
	std::int64_t value = Signed;
	std::size_t result = 0;

	do {
		value /= static_cast<std::int64_t>(Radix);

		++result;
	} while (value != 0);

	return result;
}
} // namespace Integer
} // namespace Calcda