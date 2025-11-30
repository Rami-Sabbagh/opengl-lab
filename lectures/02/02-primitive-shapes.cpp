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
مرجع:
-----
glm::sin(x)
glm::cos(x)
glm::tan(x)

glm::pi<float>()
glm::pi<double>()

glm::radians(180.0f) => PI
glm::degrees(3.14f) ~= 180

المهمة:
-------

1. في تابع انشاء الشكل الرباعي، حوّل وضعية الرسم إلى مروحة مثلثات وأجري التعديل المناسب على مصفوفة الرؤوس.
2. في تابع رسم دائرة، غيّر قيمة شعاع الإزاحة لقيمة مناسبة.

طلب اختياري

3. عدّل تابع رسم الدائرة ليرسم بيضوي، عدّل مدخلات التابع كما يجب.

*/

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape axis;
	LabUtils::BasicShape quad, circle;

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

	// تابع انشاء الشكل الرباعي
	LabUtils::BasicShape createQuad(glm::vec3 center, glm::vec2 size, glm::vec3 color)
	{
		LabUtils::BasicVertex TopLeft{
			center + glm::vec3(center.x, size.x * -0.5f, size.y * 0.5f),
			color }; // فوق يسار

		LabUtils::BasicVertex BottomLeft{
			center + glm::vec3(center.x, size.x * -0.5f, size.y * -0.5f),
			color }; // تحت يسار

		LabUtils::BasicVertex BottomRight{
			center + glm::vec3(center.x, size.x * 0.5f, size.y * -0.5f),
			color }; // تحت يمين

		LabUtils::BasicVertex TopRight{
			center + glm::vec3(center.x, size.x * 0.5f, size.y * 0.5f),
			color }; // فوق يمين

		// TASK: حوّل وضعية الرسم إلى مروحة مثلثات وأجري التعديل المناسب على مصفوفة الرؤوس.

		return LabUtils::BasicShape({
			TopLeft, BottomLeft, BottomRight,
			BottomRight, TopRight, TopLeft,
			}, GL_TRIANGLES);
	}

	LabUtils::BasicShape createCircle(glm::vec3 center, float radius, glm::vec3 color, int segments)
	{
		std::vector<LabUtils::BasicVertex> vertices{
			{ center, color }, // احداثيات مركز الدائرة
		};

		for (float theta = 0.0f; theta <= glm::radians(360.1f); theta += glm::radians(360.0f / segments))
		{
			// شعاع الإزاحة
			glm::vec3 offset = glm::vec3{ 0.0f, 0.0f, 0.0f } * radius;
			// TASK: عدّل شعاع الإزاحة لترسم الدائرة بشكل صحيح.

			vertices.push_back({ center + offset, color });
		}

		// Optional: عدّل هذا التابع، او انسخه واجعله يرسم بيضوي، عدّل مدخلات التابع كما يجب.

		return LabUtils::BasicShape(vertices, GL_TRIANGLE_FAN);
	}


	// Called at the start of the application. Useful to initialize resources such as vertex buffers.
	void onInit() override
	{
		createAxis();

		quad = createQuad({ 0.0f, -0.5f, 0.5f }, { 0.5f, 0.5f }, Colors::yellow);
		circle = createCircle({ 0.0f, 0.5f, -0.5f }, 0.25f, Colors::magenta, 10);
	}

	// Called every frame after onUpdate. Given a time counter in seconds since application start,
	// and a measurement of elapsed time between frames. Suitable for drawing operations.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		quad.render(transform, camera);
		circle.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // Make sure the axis is displayed on top of everything. (a hack)
		axis.render(transform, camera);
		glDepthFunc(GL_LESS);
	}
};

// ==========--: Entry-Point :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "Primitive Shapes (L02:P02)");

	return 0;
}