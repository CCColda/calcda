#include "catch.hpp"
#include "string.hpp"
#include "Vector2.hpp"

using Calcda::Vector2;

TEST_CASE( "Vector2 operations", "Vector2" ) {
	SECTION( "default initialization to 0" ) {
		auto vec = Vector2();

		REQUIRE(vec.x == 0.0f);
		REQUIRE(vec.y == 0.0f);
	}

	SECTION( "construction" ) {
		auto vec = Vector2(1.0f, 2.0f);
		REQUIRE(vec.x == 1.0f);
		REQUIRE(vec.y == 2.0f);
	}

	SECTION( "comparison" ) {
		REQUIRE(Vector2(2.0f, 1.0f) == Vector2(2.0f, 1.0f));
	}

	SECTION( "scalar construction" ) {
		REQUIRE(Vector2::scalar(1.0f) == Vector2(1.0f, 1.0f));
	}

	SECTION ( "length calculation" ) {
		REQUIRE(Vector2(3.0f, 4.0f).length() == 5.0f);
	}

	SECTION ( "lengthSquared calculation" ) {
		REQUIRE(Vector2(3.0f, 4.0f).lengthSquared() == 25.0f);
	}

	SECTION ( "addition" ) {
		REQUIRE(Vector2(1.0f, 2.0f) + Vector2(3.0f, 4.0f) == Vector2(4.0f, 6.0f));
	}

	SECTION ( "subtraction" ) {
		REQUIRE(Vector2(1.0f, 2.0f) - Vector2(0.5f, 1.0f) == Vector2(0.5f, 1.0f));
	}

	SECTION ( "multiplication" ) {
		REQUIRE(Vector2(2.0f, 2.0f) * Vector2(3.0f, 4.0f) == Vector2(6.0f, 8.0f));
	}

	SECTION ( "division" ) {
		REQUIRE(Vector2(5.0f, 8.0f) / Vector2(2.5f, 4.0f) == Vector2(2.0f, 2.0f));
	}

	/* TODO: 
		- test tuple access
		- unary minus
		- assignment operator
		- reflect
		- clamp
		- lerp
		- dot
		- vmin/vmax
	*/
}