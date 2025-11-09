// A library made for this OpenGL laboratory to simplify some stuff.
// It provides some boilerplate so you can jump right into the graphics.
#include "lab-utils/orbit-application.hpp"
#include "lab-utils/basic-shape.hpp"

// GLM: OpenGL Mathematics Library
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Standard C++ libraries we're using.
#include <iostream>
#include <vector>

class TriangleApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape shape;
	glm::mat4 transform = { 1.0f };

	// Called at the start of the application. Useful to initialize resources such as vertex buffers.
	void onInit() override
	{
		// Colors (r, g, b)
		glm::vec3 red = { 1.0f, 0.0f, 0.0f };
		glm::vec3 green = { 0.0f, 1.0f, 0.0f };
		glm::vec3 blue = { 0.0f, 0.0f, 1.0f };

		shape = LabUtils::BasicShape({
			// Position (x, y, z), Color
			{ {0.0f, -0.5f, -0.5f}, red }, // Bottom-left Corner
			{ {0.0f, 0.5f, -0.5f}, green }, // Bottom-right Corner
			{ {0.0f, 0.0f, 0.8f }, blue }, // Top Corner
			});
	}

	// Called every frame before onDraw. Given a time counter in seconds since application start,
	// and a measurement of elapsed time between frames. Suitable for updating your geometry/transforms.
	void onUpdate(float t, float dt) override
	{
		// Reset transform to identity.
		transform = glm::identity<glm::mat4>();

		// Translate on the X axis, based on time (t)
		transform = glm::translate(transform, { -glm::sin(glm::radians(t * 90.0f)) - 1, 0.0f, 0.0f });

		// Rotate around Z axis, based on time (t).
		transform = glm::rotate(transform, glm::radians(t * 60.0f), { 0.0f, 0.0f, 1.0f });

		// Rotate around X axis, based on time (t).
		transform = glm::rotate(transform, glm::radians(t * 5.0f), { 1.0f, 0.0f, 0.0f });
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
	TriangleApplication app;
	app.run({ 800, 600 }, "Hello Triangle (L01:P01)");

	return 0;
}