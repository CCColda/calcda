#include "Vector2.hpp"
#include "catch.hpp"
#include "string.hpp"
#include <random>

std::vector<float> generateRandomFloats(unsigned count, float min, float max) {
    std::random_device dev;
    std::mt19937 gen(dev());

    std::uniform_real_distribution<float> distribution(min, max);

    std::vector<float> result(count, 0.0f);
    for (unsigned i = 0; i < count; ++i)
        result[i] = distribution(gen);

    return result;
}

#define CALCDA_RANDOM_BLOCK(varname, count, code)                              \
    {                                                                          \
        const auto varname = generateRandomFloats(count, 1.0f, 20.0f);         \
        { code }                                                               \
    }

using Calcda::Vector2;

TEST_CASE("Vector2 operations", "Vector2") {
    SECTION("default initialization to 0") {
        auto vec = Vector2();

        REQUIRE(vec.x == 0.0f);
        REQUIRE(vec.y == 0.0f);
    }

    CALCDA_RANDOM_BLOCK(
        x, 2, SECTION("construction") {
            auto vec = Vector2(x[0], x[1]);
            REQUIRE(vec.x == x[0]);
            REQUIRE(vec.y == x[1]);
        })

    CALCDA_RANDOM_BLOCK(
        x, 2, SECTION("comparison") {
            REQUIRE(Vector2(x[0], x[1]) == Vector2(x[0], x[1]));
        })

    CALCDA_RANDOM_BLOCK(
        x, 1, SECTION("scalar construction") {
            REQUIRE(Vector2::scalar(x[0]) == Vector2(x[0], x[0]));
        })

    SECTION("length calculation") {
        REQUIRE(Vector2(3.0f, 4.0f).length() == 5.0f);
    }

    SECTION("lengthSquared calculation") {
        REQUIRE(Vector2(3.0f, 4.0f).lengthSquared() == 25.0f);
    }

    CALCDA_RANDOM_BLOCK(
        x, 4, SECTION("addition") {
            REQUIRE(Vector2(x[0], x[1]) + Vector2(x[2], x[3]) ==
                    Vector2(x[0] + x[2], x[1] + x[3]));
        })

    CALCDA_RANDOM_BLOCK(
        x, 4, SECTION("subtraction") {
            REQUIRE(Vector2(x[0], x[1]) - Vector2(x[2], x[3]) ==
                    Vector2(x[0] - x[2], x[1] - x[3]));
        })

    CALCDA_RANDOM_BLOCK(
        x, 4, SECTION("multiplication") {
            REQUIRE(Vector2(x[0], x[1]) * Vector2(x[2], x[3]) ==
                    Vector2(x[0] * x[2], x[1] * x[3]));
        })

    CALCDA_RANDOM_BLOCK(
        x, 4, SECTION("division") {
            REQUIRE(Vector2(x[0], x[1]) / Vector2(x[2], x[3]) ==
                    Vector2(x[0] / x[2], x[1] / x[3]));
        })

    /* TODO */
    /* CALCDA_RANDOM_BLOCK(
        x, 2, SECTION("tuple access") {
            const auto [a, b] = Vector2(x[0], x[1]);
            REQUIRE(a == x[0]);
            REQUIRE(b == x[1]);
        }) */

    CALCDA_RANDOM_BLOCK(
        x, 2, SECTION("unary minus operator") {
            const auto negative = -Vector2(x[0], x[1]);
            REQUIRE(negative.x == -x[0]);
            REQUIRE(negative.y == -x[1]);
        })

    CALCDA_RANDOM_BLOCK(
        x, 2, SECTION("assignment operator") {
            Vector2 vec = Vector2(0.0f, 0.0f);
            vec = Vector2(x[0], x[1]);

            REQUIRE(vec.x == x[0]);
            REQUIRE(vec.y == x[1]);
        })

    SECTION("clamp") {
        const auto vecUnder = Vector2(0.0f, 0.0f);
        const auto vecMiddle = Vector2(5.0f, 5.0f);
        const auto vecOver = Vector2(10.0f, 10.0f);

        const auto upperBound = Vector2(6.0f, 5.0f);
        const auto lowerBound = Vector2(5.0f, 4.0f);

        REQUIRE(Vector2::clamp(vecUnder, lowerBound, upperBound) == lowerBound);
        REQUIRE(Vector2::clamp(vecMiddle, lowerBound, upperBound) == vecMiddle);
        REQUIRE(Vector2::clamp(vecOver, lowerBound, upperBound) == upperBound);
    }

    SECTION("lerp") {
        REQUIRE(Vector2::lerp({-1.0f, -1.0f}, {1.0f, 1.0f}, 0.5f) ==
                Vector2(0.0f, 0.0f));
    }

    SECTION("dot") { /* TODO */
    }

    SECTION("reflect") { /*TODO*/
    }

    SECTION("vmin") {
        REQUIRE(Vector2::vmin({0.0f, 1.0f}, {-1.0f, 2.0f}) ==
                Vector2(-1.0f, 1.0f));
    }

    SECTION("vmax") {
        REQUIRE(Vector2::vmax({0.0f, 1.0f}, {-1.0f, 2.0f}) ==
                Vector2(-1.0f, 1.0f));
    }
}