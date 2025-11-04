// A library made for this OpenGL laboratory to simplify some stuff.
// It provides some boilerplate so you can jump right into the graphics.
#include "lab-utils/orbit-application.hpp"
#include "lab-utils/basic-shape.hpp"

// GLM: OpenGL Mathematics Library
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Standard C++ libraries we're using.
#include <iostream>

class TrianglesApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape shape;
	glm::mat4 transform = { 1.0f };

	// Called at the start of the application. Useful to initialize resources such as vertex buffers.
	void onInit() override
	{
		// Colors (r, g, b)
		glm::vec3 white = { 1.0f, 1.0f, 1.0f };

		shape = LabUtils::BasicShape({
			// Position (x, y, z), Color
			{ {-0.5f, -0.5f, 0.0f}, white }, // Bottom-left Corner
			{ {0.5f, -0.5f, 0.0f}, white }, // Bottom-right Corner
			{ {0.0f, 0.5f, 0.0f}, white }, // Top Corner
		}, GL_TRIANGLES);
	}

	// Called every frame after onUpdate. Given a time counter in seconds since application start,
	// and a measurement of elapsed time between frames. Suitable for drawing operations.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shape.render(transform, camera);
	}
};

// ==========--: Entry-Point :--========== //

int main() {
	TrianglesApplication app;
	app.run({ 800, 600 }, "Drawing Triangles (L01:P03)");

	return 0;
}