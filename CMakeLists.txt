cmake_minimum_required(VERSION 3.0.0)
project(calcda
	VERSION      1.0.0
	DESCRIPTION  "Calcda - Math and geometry classes written in C++"
	HOMEPAGE_URL "https://github.com/CCColda/calcda#readme"
	LANGUAGES    "CXX"
)

# toggle testing to be off by default
option(CALCDA_TEST "Build the test executable using Catch2" OFF)
option(CALCDA_JNI "Build the java library using SWIG" OFF)
option(CALCDA_JNI_SOURCE_ONLY "Build the java library using SWIG" OFF)
set(CALCDA_JNI_PACKAGE_NAME "org.colda.calcda" CACHE STRING "JNI package name")
set(CALCDA_JNI_JAVA_DIR ${PROJECT_BINARY_DIR}/jni CACHE PATH "Output directory for the JNI files")
set(CALCDA_JNI_CPP_DIR ${PROJECT_BINARY_DIR}/cpp CACHE PATH "Output directory for the JNI cxx file")
file(RELATIVE_PATH CALCDA_RELATIVE_JNI ${PROJECT_BINARY_DIR} ${CALCDA_JNI_CPP_DIR})

set(CMAKE_SWIG_FLAGS -package ${CALCDA_JNI_PACKAGE_NAME})

set(CALCDA_SRC_DIR src)
set(CALCDA_INCLUDE_DIR include)
set(CALCDA_TEST_DIR test)
set(CALCDA_INTERFACE_FILE interface/Calcda.i)
set(
	CALCDA_HEADER_FILES
	${CALCDA_INCLUDE_DIR}/Calcda.hpp
	${CALCDA_INCLUDE_DIR}/Vector2.hpp
	${CALCDA_INCLUDE_DIR}/Vector3.hpp
	${CALCDA_INCLUDE_DIR}/Vector4.hpp
	${CALCDA_INCLUDE_DIR}/Matrix3.hpp
	${CALCDA_INCLUDE_DIR}/Matrix4.hpp
	${CALCDA_INCLUDE_DIR}/Intrinsic.hpp
	${CALCDA_INCLUDE_DIR}/Rotation.hpp
	${CALCDA_INCLUDE_DIR}/Geometry.hpp
)
set(
	CALCDA_SOURCE_FILES
	${CALCDA_SRC_DIR}/Geometry.cpp
	${CALCDA_SRC_DIR}/Integer.cpp
	${CALCDA_SRC_DIR}/Matrix3.cpp
	${CALCDA_SRC_DIR}/Matrix4.cpp
	${CALCDA_SRC_DIR}/Rotation.cpp
	${CALCDA_SRC_DIR}/Vector2.cpp
	${CALCDA_SRC_DIR}/Vector3.cpp
	${CALCDA_SRC_DIR}/Vector4.cpp
)

add_library(
	calcda
	${CALCDA_SOURCE_FILES}
	${CALCDA_HEADER_FILES}
)

add_library(
	colda::calcda ALIAS calcda
)

target_include_directories(
	calcda
	PUBLIC
	${CALCDA_INCLUDE_DIR}
)

if (${CALCDA_TEST})
	Include(FetchContent)

	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v3.0.1
	)

	FetchContent_MakeAvailable(Catch2)	

	add_executable(
		calcda_test
		${CALCDA_TEST_DIR}/Vector2.test.cpp
		${CALCDA_TEST_DIR}/Geometry.test.cpp
		${CALCDA_TEST_DIR}/string.cpp
	)

	target_include_directories(calcda_test PRIVATE ${CALCDA_INCLUDE_DIR})
	target_include_directories(calcda_test PRIVATE ${CALCDA_TEST_DIR})
	target_link_libraries(calcda_test colda::calcda Catch2::Catch2WithMain)
	target_compile_features(calcda_test PRIVATE cxx_std_17)
	set_target_properties(
		calcda_test
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
	)

	list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
	include(CTest)
	include(Catch)

	catch_discover_tests(calcda_test)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_target_properties(
	calcda
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_features(calcda PRIVATE cxx_std_17)


if(${CALCDA_JNI_SOURCE_ONLY})
	find_package(SWIG REQUIRED)

	file(MAKE_DIRECTORY ${CALCDA_JNI_JAVA_DIR})
	file(MAKE_DIRECTORY ${CALCDA_JNI_CPP_DIR})
	add_custom_command(
		TARGET ${PROJECT_NAME}
		COMMAND ${SWIG_EXECUTABLE} -java -package ${CALCDA_JNI_PACKAGE_NAME} -outdir ${CALCDA_JNI_JAVA_DIR} -o ${CALCDA_RELATIVE_JNI}/calcda.cxx -c++ ${PROJECT_SOURCE_DIR}/${CALCDA_INTERFACE_FILE}
	)
endif()

if(${CALCDA_JNI})
	cmake_policy(SET CMP0086 NEW) # UseSWIG module name
	cmake_policy(SET CMP0078 NEW) # UseSWIG target names

	find_package(SWIG REQUIRED)
	find_package(JNI)

	include(UseSWIG)
	
	set_property(SOURCE ${CALCDA_INTERFACE_FILE} PROPERTY CPLUSPLUS ON)
	swig_add_library(
		calcda_jni
		TYPE MODULE
		LANGUAGE java
		OUTPUT_DIR ${CALCDA_JNI_JAVA_DIR}
		OUTFILE_DIR ${CALCDA_JNI_OUTFILE_DIR}
		SOURCES ${CALCDA_INTERFACE_FILE}
			${CALCDA_HEADER_FILES}
			${CALCDA_SOURCE_FILES}
	)

	if(JNI_FOUND)
		target_include_directories(calcda_jni PRIVATE ${JNI_INCLUDE_DIRS})
		target_link_libraries(calcda_jni calcda ${JNI_LIBRARIES})
	endif()
endif()