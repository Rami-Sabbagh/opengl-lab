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
===== مرجع =====

# وضعيات الرسم:

- GL_POINTS
- GL_LINES, GL_LINE_STRIP
- GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN

# توابع لتغيير الشكل:

- glPointSize(size);
- glLineWidth(width);

*/

class DrawModeApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape axis;
	LabUtils::BasicShape points, lines, lineStrip, triangles, triangleStrip, triangleFan;

	unsigned int active = 0;

	glm::mat4 transform = { 1.0f };

	/*
	====================- المهمة 0 -====================
	رسم مبدأ الاحداثيات والمحاور الأساسيّة
	*/

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
			}, GL_TRIANGLES); // TASK: استخدم وضعية الرسم الصحيحة لرسم النقاط.
	}

	/*
	====================- المهمة 1 -====================
	الشكل 1: نقاط بسيطة

	للتغيير بين الأشكال، اضغط رقم الشكل على لوحة المفاتيح.
	*/

	void createPoints()
	{
		using namespace Colors;

		points = LabUtils::BasicShape({
			{{ 0.0f, -0.8f, 0.0f }, red},
			{{ 0.0f, -0.4f, 0.0f }, green},
			{{ 0.0f, 0.4f, 0.0f }, blue},
			// TASK: اضف نقطة رابعة على نفس الاستقامة باللون الذي تريده.

			// OPTIONAL: اضف نقاط اخرى ليست على استقامة مع النقاط السابقة.

			}, GL_POINTS);

		// TASK: في التابع onDraw
		// في أسفل الملف، ابحث عن الفرع الشرطي الخاص بهذا الشكل وغيّر حجم النقاط.
	}

	/*
	====================- المهمة 2 -====================
	الشكل 2: خطوط
	*/

	void createLines()
	{
		using namespace Colors;

		lines = LabUtils::BasicShape({
			{{ 0.0f, -0.4f, -0.8f }, magenta},
			{{ 0.0f, 0.4f, 0.8f }, magenta},


			{{ 0.0f, 0.3f, 0.2f }, yellow},
			{{ 0.2f, 0.2f, 0.4f }, yellow},

			// TASK: اضف خط ثالث بالمكان الّذي تريد وباللون الّذي تريد.

			}, GL_LINES); // <-- لاحظ الوضعية المستخدمة.

		// TASK: في التابع onDraw
		// في أسفل الملف، ابحث عن الفرع الشرطي الخاص بهذا الشكل وغيّر سماكة الخط.
	}

	/*
	====================- المهمة 3 -====================
	الشكل 3: شريط خطوط
	*/

	void createLineStrip()
	{
		using namespace Colors;

		lineStrip = LabUtils::BasicShape({
			{{ 0.0f, -0.8f, 0.5f }, white},
			{{ 0.0f, -0.6f, 0.3f }, yellow},
			{{ 0.0f, -0.3f, 0.6f }, white},

			// TASK: اضف رأس/رؤوس اضافية بالمكان واللون الذي تريد.

			}, GL_LINE_STRIP); // <-- لاحظ الوضعية المستخدمة.
	}

	/*
	====================- المهمة 4 -====================
	الشكل 4: مثلثات
	*/

	void createTriangles()
	{
		using namespace Colors;

		triangles = LabUtils::BasicShape({
			{{ 0.0f, -0.8f, -0.6f }, white},
			{{ 0.0f, -0.5f, -0.5f }, white},
			{{ 0.0f, -0.65f, -0.3f }, white},

			{{ -0.2f, -0.7f, -0.2f }, yellow},
			{{ -0.2f, -0.6f, -0.4f }, yellow},
			{{ 0.2f, -0.3f, -0.1f }, yellow},

			// TASK: اضف مثلث/مثلثات اضافية بالمكان واللون الذي تريد.

			}, GL_TRIANGLES); // <-- لاحظ الوضعية المستخدمة.
	}

	/*
	====================- المهمة 5 -====================
	الشكل 5: شريط مثلثات
	*/

	void createTriangleStrip()
	{
		using namespace Colors;

		triangleStrip = LabUtils::BasicShape({
			{{ 0.0f, 0.6f, 0.8f }, white},
			{{ 0.0f, 0.4f, 0.7f }, white},
			{{ 0.0f, 0.6f, 0.6f }, white},

			{{ 0.0f, 0.4f, 0.5f }, red},
			{{ 0.0f, 0.6f, 0.4f }, green},
			{{ 0.0f, 0.4f, 0.3f }, blue},

			{{ 0.0f, 0.6f, 0.2f }, white},
			{{ 0.0f, 0.4f, 0.1f }, white},
			{{ 0.0f, 0.6f, 0.0f }, white},

			// TASK: اضف رأس/رؤوس اضافية بالمكان واللون الذي تريد.

			}, GL_TRIANGLE_STRIP); // <-- لاحظ الوضعية المستخدمة.
	}

	/*
	====================- المهمة 6 -====================
	الشكل 6: مروحة مثلثات
	*/

	void createTriangleFan()
	{
		using namespace Colors;

		triangleFan = LabUtils::BasicShape({
			{{ -0.1f, 0.0f, 0.0f }, white},
			{{ -0.1f, 0.0f, 0.6f }, white},
			{{ -0.1f, 0.4f, 0.4f }, white},
			{{ -0.1f, 0.6f, 0.0f }, yellow},
			{{ -0.1f, 0.5f, -0.1f}, yellow},

			// TASK: اضف رأس/رؤوس اضافية بالمكان واللون الذي تريد.

			}, GL_TRIANGLE_FAN); // <-- لاحظ الوضعية المستخدمة.
	}

	/*
	====================- تتمة البرنامج -====================
	*/

	// Called at the start of the application. Useful to initialize resources such as vertex buffers.
	void onInit() override
	{
		createAxis();
		createPoints();
		createLines();
		createLineStrip();
		createTriangles();
		createTriangleStrip();
		createTriangleFan();
	}

	// Called every frame after onUpdate. Given a time counter in seconds since application start,
	// and a measurement of elapsed time between frames. Suitable for drawing operations.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (active == 1)
		{
			// TASK: غيّر حجم النقطة.
			glPointSize(1.0f);
			points.render(transform, camera);
		}

		if (active == 2)
		{
			// TASK: غيّر سماكة الخط.
			glLineWidth(1.0f);
			lines.render(transform, camera);
		}

		if (active == 3)
		{
			glLineWidth(3.0f);
			lineStrip.render(transform, camera);
		}

		if (active == 4) triangles.render(transform, camera);
		if (active == 5) triangleStrip.render(transform, camera);
		if (active == 6) triangleFan.render(transform, camera);


		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // Make sure the axis is displayed on top of everything. (a hack)
		axis.render(transform, camera);
		glDepthFunc(GL_LESS);
	}

	// Called whenever a keyboard button is pressed. Repeats when the button is held.
	void onKeyPressed(const sf::Event::KeyPressed& ev) override
	{
		if (ev.code >= sf::Keyboard::Key::Num0 && ev.code <= sf::Keyboard::Key::Num9)
		{
			unsigned int number = static_cast<int>(ev.code) - static_cast<int>(sf::Keyboard::Key::Num0);
			std::cout << "Activated Shape: " << number << std::endl;
			active = number;
		}
	}
};

// ==========--: Entry-Point :--========== //

int main() {
	DrawModeApplication app;
	app.run({ 600, 600 }, "Draw Modes (L02:P01)");

	return 0;
}