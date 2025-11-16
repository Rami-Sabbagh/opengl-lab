// مكتبة خاصة بمخبر الرسوميّات الحاسوبية، موجودة للتبسيط
// تقدّم هيكل اساسي للبرنامج، يسمح لكم بالإنطلاق مباشرة نحو الأفكار الأساسية
#include "lab-utils/orbit-application.hpp"
#include "lab-utils/basic-shape.hpp"

// GLM: مكتبة رياضيّات خاصة بالرسوميّت الحاسوبيّة. (OpenGL Mathematics Library)
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// تفعيل دعم الطباعة لمتحوّلات المكتبة السابقة
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>

// مكتبة التعامل مع النافذة ووسائل الإدخال
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

// مكاتب اللغة الأساسيّة
#include <iostream>
#include <vector>

// مجموعة مساعدة من الألوان معرّفة مسبقاً يمكنكم استخدامها والإضافة عليها
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


المهمة:
-------


*/


class DrawModeApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape axis;
	LabUtils::BasicShape cube;

	glm::mat4 transform = { 1.0f };

	// يستدعى في بداية البرنامج. مفيد لانشاء أو تحميل أشكال المجسّمات
	void onInit() override
	{
		createAxis();
		createCube();
	}

	// يستدعى قبل كل مرة ترسم فيها الشاشة (حوالي الـ60 مرة في الثانية)، ويعطى عداد للثواني منذ فتح البرنامج
	// وأيضا يعطى قيمة اخرى وهي الثواني الماضية منذ الاستدعاء السابق لهذا التابع.
	// مناسب لتحديث مصفوفات التحويل، مواقع الأجسام، الخ.
	void onUpdate(float t, float dt) override
	{

	}

	/*
	====================- تتمة البرنامج -====================
	(من المفيد الاطلاع ومحاولة فهم البرنامج سطر بسطر)
	*/

	// يستدعى كل مرة ترسم فيها الشاشة (حوالي الـ60 مرة في الثانية)، ويعطى عداد للثواني منذ فتح البرنامج
	// وأيضا يعطى قيمة اخرى وهي الثواني الماضية منذ الاستدعاء السابق لهذا التابع.
	// يجب اجراء عمليات الرسم دخل هذا التابع.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // التأكد من رسم محاور مبدأ الاحداثيات فوق كل شي
		axis.render(glm::identity<glm::mat4>(), camera);
		glDepthFunc(GL_LESS);
	}

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
			{ C, red }, { F, red }, { G, red },

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
};

// ==========--: نقطة دخول البرنامج :--========== //

int main() {
	DrawModeApplication app;
	app.run({ 600, 600 }, "Transformations (L03:P01)");

	return 0;
}