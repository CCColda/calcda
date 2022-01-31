# `calcda` math library

A little project - originally made for personal use - as a library.

## Vectors
Vectors are defined for 2, 3 and 4 dimensions.
```cpp
using Calcda::Vector2;

Vector2 vec = Vector2{0.0f, 0.0f} + Vector2{10.0f, -5.0f};
std::cout << vec.toString() << std::endl // prints: <10.0, -5.0>
	<< vec.x + vec.y << std::endl; // prints: 5.0f
```

## Matrix4
`Matrix4.hpp` includes a `Matrix4` (4x4) class, with methods for perspective, frustum and orthographic projections, and a `lookAt` method.

An example of a VP matrix would be:
```cpp
using Calcda::Matrix4, Calcda::Vector3;

Matrix4 mat =
	Matrix4::perspective(
		75.0f, // fov
		4.0f / 3.0f, // aspect ratio
		0.0f, // near plane
		100.0f // far plane
	) *
	Matrix4::lookAt(
		Vector3(0.0f, 4.0f, 9.0f), // eye position
		Vector3(0.0f, 0.0f, 0.0f), // point to look at
		Vector3::UnitY // up direction
	);
```

For printing out matrices, use:
```cpp
using Calcda::Matrix4;

Matrix4 mat = /* some matrix */;

std::cout
	<< "one-line representation: " << mat.toString() << std::endl
	<< "multi-line representation: " << mat.toStringO(2 /* padding */, 2 /* precision */) << std::endl;
```


## How to use
If you want to use this library with CMake, you can do one of these things:
### 1. Add as submodule
Inside a git repository,
```bash
git submodule add "https://github.com/CCColda/calcda.git" libs/calcda
```

In your CMakeLists.txt:
```CMake
add_submodule(libs/calcda)
target_link_libraries(my_target calcda)
```

### 2. Use CMake FetchContent
In your CMakeLists.txt:
```CMake
include(FetchContent)

FetchContent_Declare(
	calcda
	GIT_REPOSITORY "https://github.com/CCColda/calcda.git"
	GIT_TAG "main"
)

FetchContent_MakeAvailable(calcda)
target_link_libraries(my_target calcda)
```
