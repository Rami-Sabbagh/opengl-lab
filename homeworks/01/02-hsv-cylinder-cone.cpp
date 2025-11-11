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
glm::sin(x)
glm::cos(x)
glm::tan(x)

glm::pi<float>()
glm::pi<double>()

glm::radians(180.0f) => PI
glm::degrees(3.14f) ~= 180

المهمة:
-------

البحث عن تابع للتحويل من صيغة الألوان المطلوبة إلى الصيغة القابلة للاستخدام
(HSV to RGB)

وتعديل توابع انشاء الاسطوانة والمخروط لتتلون بشكل مماثل للصور في اعلان الوظيفة.
*/

class DrawModeApplication : public LabUtils::LabOrbitApplication
{
	LabUtils::BasicShape axis;
	LabUtils::BasicShape cylinder, cone;
	unsigned int active = 0; // عدّل الرقم التالي أو استخدم ارقام لوحة المفاتيل لتبديل الشكل المرسوم.

	glm::mat4 transform = { 1.0f };

	/*
	====================- المهمة 1 -====================
	تابع تحويل صيغة الألوان
	*/

	glm::vec3 hsv2rgb(glm::vec3 rgb)
	{
		// TASK: ابحث بالانترنت عن كيفية اجراء هذا التحويل، من الممكن نسخ كود، لكن ربما تحتاج تعديله ليعمل مع الصيغة المستخدمة.

	}

	/*
	====================- المهمة 2 -====================
	تابع إنشاء اسطوانة
	*/

	LabUtils::BasicShape createCylinder(float height, float radius, int segments)
	{
		using namespace Colors;

		std::vector<LabUtils::BasicVertex> vertices{
			// من الممكن وضع نقاط ثابتة هنا.
			{ { 0.0f, 0.0f, 0.0f }, white }, // مثال، يمكن حذفه.
		};

		vertices.push_back({ { 0.0f, 0.0f, 0.0f }, white }); // مثال يمكن حذفه.

		return LabUtils::BasicShape(vertices, GL_TRIANGLE_FAN);
	}

	/*
	====================- المهمة 3 -====================
	تابع إنشاء مخروط
	*/

	LabUtils::BasicShape createCone(float height, float radius, int segments)
	{
		using namespace Colors;

		std::vector<LabUtils::BasicVertex> vertices{
			// من الممكن وضع نقاط ثابتة هنا.
			{ { 0.0f, 0.0f, 0.0f }, white }, // مثال، يمكن حذفه.
		};

		vertices.push_back({ { 0.0f, 0.0f, 0.0f }, white }); // مثال يمكن حذفه.

		return LabUtils::BasicShape(vertices, GL_TRIANGLE_FAN);
	}

	/*
	====================- تتمة البرنامج -====================
	*/

	// يستدعى في بداية البرنامج. مفيد لانشاء أو تحميل أشكال المجسّمات
	void onInit() override
	{
		createAxis();

		cylinder = createCylinder(0.8f, 0.25f, 32);
		cone = createCone(0.6f, 0.25f, 32);
	}

	// يستدعى كل مرة ترسم فيها الشاشة (حوالي الـ60 مرة في الثانية)، ويعطى عداد للثواني منذ فتح البرنامج
	// وأيضا يعطى قيمة اخرى وهي الثواني الماضية منذ الاستدعاء السابق لهذا التابع.
	// يجب اجراء عمليات الرسم دخل هذا التابع.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (active == 0) cylinder.render(transform, camera);
		if (active == 1) cone.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // التأكد من رسم محاور مبدأ الاحداثيات فوق كل شي
		axis.render(transform, camera);
		glDepthFunc(GL_LESS);
	}

	// يستدعى كل مرّة يضغط فيها زر من لوحة المفاتيح
	void onKeyPressed(const sf::Event::KeyPressed& ev) override
	{
		if (ev.code >= sf::Keyboard::Key::Num0 && ev.code <= sf::Keyboard::Key::Num9)
		{
			unsigned int number = static_cast<int>(ev.code) - static_cast<int>(sf::Keyboard::Key::Num0);
			std::cout << "Activated Shape: " << number << std::endl;
			active = number;
		}
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
};

// ==========--: نقطة دخول البرنامج :--========== //

int main() {
	DrawModeApplication app;
	app.run({ 600, 600 }, "Homework - HSV Cylinder & Cone (H01:P02)");

	return 0;
}