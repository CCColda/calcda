cmake_minimum_required(VERSION 3.0.0)
project(calcda VERSION 1.0.0)

# toggle testing to be off by default
option(BUILD_TESTING "Build the test executable using Catch2" OFF)
include(CTest)
include(CPack)

enable_testing()

set(CALCDA_SRC_DIR src)
set(CALCDA_TEST_DIR test)
set(CALCDA_CATCH_FILE ${CALCDA_TEST_DIR}/catch.hpp)
set(
	CALCDA_HEADER_FILES
	${CALCDA_SRC_DIR}/Calcda.hpp
	${CALCDA_SRC_DIR}/Vector2.hpp
	${CALCDA_SRC_DIR}/Vector3.hpp
	${CALCDA_SRC_DIR}/Vector4.hpp
	${CALCDA_SRC_DIR}/Matrix3.hpp
	${CALCDA_SRC_DIR}/Matrix4.hpp
	${CALCDA_SRC_DIR}/Intrinsic.hpp
	${CALCDA_SRC_DIR}/Rotation.hpp
	${CALCDA_SRC_DIR}/Geometry.hpp
)

add_library(
	calcda
	${CALCDA_SRC_DIR}/Geometry.cpp
	${CALCDA_SRC_DIR}/Integer.cpp
	${CALCDA_SRC_DIR}/Matrix3.cpp
	${CALCDA_SRC_DIR}/Matrix4.cpp
	${CALCDA_SRC_DIR}/Rotation.cpp
	${CALCDA_SRC_DIR}/Vector2.cpp
	${CALCDA_SRC_DIR}/Vector3.cpp
	${CALCDA_SRC_DIR}/Vector4.cpp
	${CALCDA_HEADER_FILES}
)

if (${BUILD_TESTING})
	add_executable(
		tests
		${CALCDA_TEST_DIR}/test.cpp
		${CALCDA_TEST_DIR}/Vector2.cpp
		${CALCDA_TEST_DIR}/Geometry.cpp
		${CALCDA_TEST_DIR}/string.hpp
		${CALCDA_HEADER_FILES}
		${CALCDA_CATCH_FILE}
	)
	target_include_directories(tests PRIVATE ${CALCDA_SRC_DIR})
	target_include_directories(tests PRIVATE ${CALCDA_TEST_DIR})
	target_link_libraries(tests calcda)
	target_compile_features(tests PRIVATE cxx_std_17)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

target_compile_features(calcda PRIVATE cxx_std_17)
