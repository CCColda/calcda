#ifndef CALCDA_INTEGER_H
#define CALCDA_INTEGER_H

#include <cstddef>
#include <cstdint>

#include "Intrinsic.hpp"

namespace Calcda {
namespace Integer {
//! @brief Counts the digits of @c Signed, in base @c Radix
std::size_t countDigits(std::int64_t Signed, std::size_t Radix = 10);
} // namespace Integer
} // namespace Calcda

#endif // !CALCDA_INTEGER_H