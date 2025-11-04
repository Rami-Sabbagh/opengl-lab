// Standard C++ Libraries
#include <iostream>

// GLM: OpenGL Mathematics Library
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Enable std::cout support for GLM values.
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>

using namespace std;

/*
Exercises:
----------

# Vectors Initialization

- Basic Creation.
- Single Value.
- Vec2.
- Mixing Vec2 with Vec3.
- Mixing Vec2 with Vec4.

# Arithmetic Operations

- Add
- Substract
- Dot

# Trigonometry

- Pi
- Radian conversion
- Sin
- Cos

*/

void main()
{
	glm::vec3 a{1.0f, 2.0f, 3.0f};

	cout << "GLM Vector: " << a << endl;
}