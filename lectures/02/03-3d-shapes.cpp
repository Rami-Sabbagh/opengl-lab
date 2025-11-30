// A library made for this OpenGL laboratory to simplify some stuff.
// It provides some boilerplate so you can jump right into the graphics.
#include "lab-utils/orbit-application.hpp"
#include "lab-utils/basic-shape.hpp"

// GLM: OpenGL Mathematics Library
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Enable std::cout support for GLM values.
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>

// Standard C++ libraries we're using.
#include <iostream>
#include <vector>

// Handy pre-defined colors you can make use of.
namespace Colors
{
	glm::vec3 red{ 1.f, 0.f, 0.f };
	glm::vec3 green{ 0.f, 1.f, 0.f };
	glm::vec3 blue{ 0.f, 0.f, 1.f };

	glm::vec3 white{ 1.f, 1.f, 1.f };
	glm::vec3 black{ 0.f, 0.f, 0.f };

	glm::vec3 yellow{ 1.f, 1.f, 0.f };
	glm::vec3 magenta{ 1.f, 0.f, 1.f };
	glm::vec3 cyan{ 0.f, 1.f, 1.f };
}

/*
المهمة:
-------

أجري التعديلات المناسبة لجعل قاعدة الهرم مربّعاً.
(أي يصبح هرم رباعي)

*/

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape axis;
	LabUtils::BasicShape pyramid;

	glm::mat4 transform = { 1.0f };

	void createAxis()
	{
		axis = LabUtils::BasicShape({
			// X Axis, Red
			{{.0f, .0f, .0f}, { 1.f, 0.f, 0.f }},
			{{.1f, .0f, .0f}, { 1.f, 0.f, 0.f }},

			// Y Axis, Green
			{{.0f, .0f, .0f}, { 0.f, 1.f, 0.f }},
			{{.0f, .1f, .0f}, { 0.f, 1.f, 0.f }},

			// Z Axis, Blue
			{{.0f, .0f, .0f}, { 0.f, 0.f, 1.f }},
			{{.0f, .0f, .1f}, { 0.f, 0.f, 1.f }},
			}, GL_LINES);
	}

	void createPyramid()
	{
		// النموذج مطابق للصورة في السلايدات.
		using namespace Colors;

		glm::vec3 A{ 0.0f,   0.0f,  0.5f };
		glm::vec3 B{ 0.5f,  -0.5f, -0.5f };
		glm::vec3 C{ 0.5f,   0.5f, -0.5f };
		glm::vec3 D{ -0.5f,   0.5f, -0.5f };

		pyramid = LabUtils::BasicShape({
			{ A, magenta }, { B, magenta },{ C, magenta },
			{ A, yellow }, { C, yellow }, { D, yellow },
			{ A, cyan }, { D, cyan }, { B, cyan },

			// وجه القاعدة
			{ B, white }, { C, white }, { D, white },

			}, GL_TRIANGLES);
	}

	// Called at the start of the application. Useful to initialize resources such as vertex buffers.
	void onInit() override
	{
		createAxis();
		createPyramid();
	}

	// Called every frame after onUpdate. Given a time counter in seconds since application start,
	// and a measurement of elapsed time between frames. Suitable for drawing operations.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pyramid.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // Make sure the axis is displayed on top of everything. (a hack)
		axis.render(transform, camera);
		glDepthFunc(GL_LESS);
	}
};

// ==========--: Entry-Point :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "3D Shapes (L02:P03)");

	return 0;
}