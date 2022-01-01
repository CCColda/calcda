# `calcda` math library

A little project originally made for personal use as a library.

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
