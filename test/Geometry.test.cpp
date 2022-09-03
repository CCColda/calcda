#include <catch2/catch_all.hpp>
#include "Geometry.hpp"

TEST_CASE("Polygon intersections", "Polygon") {
    using namespace Calcda;
    using Calcda::Polygon;

    Polygon square = Polygon{Vector2(0.0f, 0.0f), Vector2(0.0f, 1.0f),
                             Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f)};

    SECTION("intersection with slope 1 line") {
        auto intersections = square.intersectLine(
            Vector2(0.25, -0.5f), Vector2(1.0f, 1.0f), LineType::RAY);

        REQUIRE_THAT(intersections,
                     Catch::Matchers::UnorderedEquals(std::vector<Vector2>{
                         Vector2(1.0f, 1.0f), Vector2(0.5f, 0.0f)}));
    }
}