#include <catch2/catch_all.hpp>
#include <cmath>

#include "Vector2.hpp"
#include "random.hpp"

using Calcda::Vector2;

TEST_CASE("Vector2 operations", "Vector2") {
    using Catch::Approx;
    
    CALCDA_DEFINE_RANDOM(x)

    SECTION("default initialization to 0") {
        auto vec = Vector2();

        REQUIRE(vec.x == 0.0f);
        REQUIRE(vec.y == 0.0f);
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("construction") {
        const auto vec = Vector2(x[0], x[1]);
        REQUIRE(vec.x == x[0]);
        REQUIRE(vec.y == x[1]);
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("initializer list construction") {
        const Vector2 vec = {x[0], x[1]};
        REQUIRE(vec.x == x[0]);
        REQUIRE(vec.y == x[1]);
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("swaps") {
        REQUIRE(Vector2(x[0], x[1]).yx() == Vector2(x[1], x[0]));
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("comparison") {
        REQUIRE(Vector2(x[0], x[1]) == Vector2(x[0], x[1]));
    }

    CALCDA_REQUIRE_RANDOM(x, 1)
    SECTION("scalar construction") {
        REQUIRE(Vector2::scalar(x[0]) == Vector2(x[0], x[0]));
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("length calculation") {
        REQUIRE(Vector2(x[0], x[1]).length() ==
                std::sqrt(x[0] * x[0] + x[1] * x[1]));
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("lengthSquared calculation") {
        REQUIRE(Vector2(x[0], x[1]).lengthSquared() ==
                (x[0] * x[0] + x[1] * x[1]));
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("normalization") {
        const auto v1 = Vector2(x[0], x[1]);
        const auto len = v1.length();

        const auto normalized = v1.normalize();
        const auto manually_normalized = Vector2(x[0] / len, x[1] / len);
        REQUIRE(normalized.x == Approx(manually_normalized.x));
        REQUIRE(normalized.y == Approx(manually_normalized.y));
    }

    CALCDA_REQUIRE_RANDOM(x, 4)
    SECTION("addition") {
        REQUIRE(Vector2(x[0], x[1]) + Vector2(x[2], x[3]) ==
                Vector2(x[0] + x[2], x[1] + x[3]));
    }

    CALCDA_REQUIRE_RANDOM(x, 4)
    SECTION("subtraction") {
        REQUIRE(Vector2(x[0], x[1]) - Vector2(x[2], x[3]) ==
                Vector2(x[0] - x[2], x[1] - x[3]));
    }

    CALCDA_REQUIRE_RANDOM(x, 4)
    SECTION("multiplication") {
        REQUIRE(Vector2(x[0], x[1]) * Vector2(x[2], x[3]) ==
                Vector2(x[0] * x[2], x[1] * x[3]));
    }

    CALCDA_REQUIRE_RANDOM(x, 4)
    SECTION("division") {
        REQUIRE(Vector2(x[0], x[1]) / Vector2(x[2], x[3]) ==
                Vector2(x[0] / x[2], x[1] / x[3]));
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("tuple access") {
        const auto [a, b] = Vector2(x[0], x[1]);
        REQUIRE(a == x[0]);
        REQUIRE(b == x[1]);
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("unary minus operator") {
        const auto negative = -Vector2(x[0], x[1]);
        REQUIRE(negative.x == -x[0]);
        REQUIRE(negative.y == -x[1]);
    }

    CALCDA_REQUIRE_RANDOM(x, 2)
    SECTION("assignment operator") {
        Vector2 vec = Vector2(0.0f, 0.0f);
        vec = Vector2(x[0], x[1]);

        REQUIRE(vec.x == x[0]);
        REQUIRE(vec.y == x[1]);
    }

    CALCDA_REQUIRE_RANDOM_SORTED(x, 10)
    SECTION("clamp") {
        const auto vecUnder = Vector2(x[0], x[1]);
        const auto lowerBound = Vector2(x[2], x[3]);

        const auto vecMiddle = Vector2(x[4], x[5]);

        const auto upperBound = Vector2(x[6], x[7]);
        const auto vecOver = Vector2(x[8], x[9]);

        REQUIRE(Vector2::clamp(vecUnder, lowerBound, upperBound) == lowerBound);
        REQUIRE(Vector2::clamp(vecMiddle, lowerBound, upperBound) == vecMiddle);
        REQUIRE(Vector2::clamp(vecOver, lowerBound, upperBound) == upperBound);
    }

    SECTION("lerp") {
        REQUIRE(Vector2::lerp({-1.0f, -1.0f}, {1.0f, 1.0f}, 0.5f) ==
                Vector2(0.0f, 0.0f));
    }

    CALCDA_REQUIRE_RANDOM(x, 4)
    SECTION("dot") {
        REQUIRE(Vector2::dot({x[0], x[1]}, {x[2], x[3]}) ==
                (x[0] * x[2] + x[1] * x[3]));
    }

    CALCDA_REQUIRE_RANDOM_SORTED(x, 4)
    SECTION("vmin/vmax") {
        const Vector2 v1 = {x[0], x[1]};
        const Vector2 v2 = {x[2], x[3]};

        REQUIRE(Vector2::vmin(v1, v2) == v1);
        REQUIRE(Vector2::vmax(v1, v2) == v2);
    }

    CALCDA_REQUIRE_RANDOM(x, 4)
    SECTION("reflect") {
        const Vector2 v1 = {x[0], x[1]};
        const Vector2 v2 = Vector2(x[2], x[3]).normalize();

        const auto dot = Vector2::dot(v1, v2);

        REQUIRE(Vector2::reflect(v1, v2) ==
                Vector2(v1.x - 2.0f * dot * v2.x, v1.y - 2.0f * dot * v2.y));
    }
}