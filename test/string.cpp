#include <catch2/catch_all.hpp>
#include "Calcda.hpp"

#define DEFINE_STRING_MAKER_FOR(target_class)                                  \
    template <> struct StringMaker<target_class> {                             \
        static std::string convert(target_class const &value) {                \
            return value.toString();                                           \
        }                                                                      \
    };

namespace Catch {
DEFINE_STRING_MAKER_FOR(Calcda::Vector2)
DEFINE_STRING_MAKER_FOR(Calcda::Vector3)
DEFINE_STRING_MAKER_FOR(Calcda::Vector4)
DEFINE_STRING_MAKER_FOR(Calcda::Matrix3)
DEFINE_STRING_MAKER_FOR(Calcda::Matrix4)
} // namespace Catch
