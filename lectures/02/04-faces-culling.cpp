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

1. جرب تشغيل البرنامج وانظر إلى المكعب، حرّك بالفأرة.
2. في تابع الرسم، فعّل عملية إلغاء الوجوه ثم جرب البرنامج.
3. يوجد مثلث ملفوف باتجاه خاطئ في الوجه الأمامي، أصلحه. وجرّب البرنامج.
4. غير عملية إلغاء الوجوه لتلغي الوجوه الأمامية بدل الخلفية باستخدام التعليمة المناسبة في تابع الرسم، ثم جرب البرنامج.

*/

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape axis;
	LabUtils::BasicShape cube;

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

	void createCube()
	{
		// النموذج مطابق للصورة في السلايدات.
		using namespace Colors;

		glm::vec3 A{ -0.5f, -0.5f, 0.5f };
		glm::vec3 B{ 0.5f, -0.5f, 0.5f };
		glm::vec3 C{ 0.5f, 0.5f, 0.5f };
		glm::vec3 D{ -0.5f, 0.5f, 0.5f };

		glm::vec3 E{ -0.5f, -0.5f, -0.5f };
		glm::vec3 F{ 0.5f, -0.5f, -0.5f };
		glm::vec3 G{ 0.5f, 0.5f, -0.5f };
		glm::vec3 H{ -0.5f, 0.5f, -0.5f };

		cube = LabUtils::BasicShape({
			// الوجه العلوي
			{ A, blue }, { B, blue }, { C, blue },
			{ C, blue }, { D, blue }, { A, blue },

			// الوجه الأمامي
			{ B, red }, { F, red }, { C, red },
			{ C, red }, { G, red }, { F, red },

			// الوجه اليميني
			{ C, green }, { G, green }, { D, green },
			{ D, green }, { G, green }, { H, green },

			// الوجه الخلفي
			{ D, magenta }, { H, magenta }, { A, magenta },
			{ A, magenta }, { H, magenta }, { E, magenta },

			// الوجه اليساري
			{ A, yellow }, { E, yellow }, { B, yellow },
			{ B, yellow }, { E, yellow }, { F, yellow },

			// الوجه السفلي
			{ E, cyan }, { H, cyan }, { F, cyan },
			{ F, cyan }, { H, cyan }, { G, cyan },
			});
	}

	// Called at the start of the application. Useful to initialize resources such as vertex buffers.
	void onInit() override
	{
		createAxis();
		createCube();
	}

	// Called every frame after onUpdate. Given a time counter in seconds since application start,
	// and a measurement of elapsed time between frames. Suitable for drawing operations.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// لتفعيل إلغاء الوجوه استخدم التعليمة التالية:
		
		//glEnable(GL_CULL_FACE);
		
		// لتغيير الوجوه الملغاة استخدم التعليمة التالية بالقيمة المناسبة.
		// GL_FRONT: إلغاء الوجوه الأمامية.
		// GL_BACK (Default): إلغاء الوجوه الخلفية.
		
		//glCullFace(GL_BACK);

		cube.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // Make sure the axis is displayed on top of everything. (a hack)
		axis.render(transform, camera);
		glDepthFunc(GL_LESS);
	}
};

// ==========--: Entry-Point :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "Faces Culling (L02:P04)");

	return 0;
}