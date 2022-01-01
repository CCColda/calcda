#ifndef CALCDA_INTRINSIC_H
#define CALCDA_INTRINSIC_H

#include <cstddef>
#include <stdarg.h>

#define CALCDA

#ifndef CALCDA_NO_IF_CONSTEXPR
#	define CALCDA_IF_CONSTEXPR if constexpr
#else
#	define CALCDA_IF_CONSTEXPR if
#endif

namespace Calcda {
namespace Internal {
inline CALCDA std::size_t hash_combine(std::size_t left, std::size_t right)
{
	return left ^ (right + 0x9e3779b9 + (left << 6) + (left >> 2));
}

inline CALCDA std::size_t hash_combine_n(unsigned n, ...) {
	va_list list;
	va_start(list, n);

	std::size_t result = 0;

	for (unsigned i = 0; i < n; ++i)
		hash_combine(result, va_arg(list, std::size_t));
	
	va_end(list);

	return result;
}

#ifdef CALCDA_FUNC_PARAMETER_PACK

template <typename... T>
inline CALCDA std::size_t hash_combine(T... hashes)
{
	std::size_t result = 0;

	const auto fn = [&result](std::size_t value) {
		result = hash_combine(result, value);
	};

	// JNI doesn't like this :(
	(fn(hashes), ...);

	return result;
}

#else

template <typename... T>
inline CALCDA std::size_t hash_combine(T... hashes)
{
	return hash_combine_n(sizeof...(hashes), hashes...);
}
#endif

} // namespace Internal
} // namespace Calcda

#endif // !defined(CALCDA_INTRINSIC_H)