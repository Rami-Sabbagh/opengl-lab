// عزيزي الطالب، هذا ملف مثال، ولك كامل الحرية في تعديله
// ذكرت الغاية والمراجع لجميع المكاتب المستخدمة.

// ---- تضمين المكاتب الخارجية ---- //

// من أجل استخدام اصدار حديث من الأوبن جي ال
// لا بد من استخدام مكتبة وسيطة
// GLAD: https://github.com/Dav1dde/glad, https://glad.dav1d.de/
// المرجع: https://docs.gl/ أو https://devdocs.io/
#include <glad/glad.h>

// لإنشاء نافذة البرنامج، وتحميل الصور على الذاكرة، ومعالجة دخل المستخدم
// نستخدم مكتبة وسيطة بدل التعامل مع توابع نظام التشغيل مباشرة
// SFML: Simple and Fast Multimedia Library: https://www.sfml-dev.org/
// مرجع التوابع: https://www.sfml-dev.org/documentation/3.0.2/
// دليل المتسخدم: https://www.sfml-dev.org/tutorials/3.0/
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

// للتعامل مع الأشعة والمصفوفات الرياضية
// وانشاء مصفوفات تحويلات هندسية وإسقاط
// GLM: OpenGL Mathematics: https://github.com/g-truc/glm/
// دليل المستخدم: https://github.com/g-truc/glm/blob/master/manual.md
// لربما من الأحسن الإعتماد على التتمة التلقائية أثناء الكتابة،
// أو قراءة ملفات التوريس مباشرة.
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// لتفعيل دعم الطباعة بالمكتبة السابقة
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>

// ---- تضمين المكاتب الاساسية ---- //

#include <string>
#include <vector>
#include <iostream>

// ---- تضمين ترويسات المشروع ---- //

#include "lab-utils/basic-shape.hpp"
#include "lab-utils/textured-shape.hpp"
#include "lab-utils/orbit-application.hpp"

// ---- قيم مساعدة ---- //

// تعريف مجموعة من الألوان
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

// ---- البرنامج ---- //

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	// ---- متحولات البرنامج ---- //

	LabUtils::BasicShape axis;
	LabUtils::TexturedShape shape;

	glm::mat4 transform = { 1.0f };

	// ---- مراحل حياة البرنامج ---- //

	// تابع يستدعى مرة واحدة عند بدئ البرنامج.
	// مناسب لإنشاء النماذج وتحديد موضعها الابتدائي
	// وتحميل الصور على الذاكرة.
	void onInit() override
	{
		createAxis();
		using namespace Colors;

		// -- تعريف الشكل -- //

		shape = LabUtils::TexturedShape({
			// الموقع (x, y, z), اللون
			{ {0.0f, 0.0f, 0.8f }, red, {0.5f, 1.0f} }, // الزاوية العلوية
			{ {0.0f, 0.5f, -0.5f}, green, {1.0f, 0.0f} }, // الزاوية السفلية - اليمينية
			{ {0.0f, -0.5f, -0.5f}, blue, {0.0f, 0.0f} }, // الزاوية السفلية - اليسارية
			}, GL_TRIANGLES);
	}

	// تابع يستدعى في كل مرّة ترسم فيها الشاشة
	// يستدعى قبل التابع onDraw
	// يأخذ معطيين: عدّاد للثواني منذ تشغيل البرنامج
	// وعدّاد للثواني بين كل مرة تسرم فيها الشاشة
	// مناسب لإجراء لتحديث مواضع المجسّمات.
	void onUpdate(float t, float dt) override
	{
		
	}

	// تابع يستدعى في كل مرّة ترسم فيها الشاشة
	// يستدعى بعد التابع onDraw
	// يأخذ معطيين: عدّاد للثواني منذ تشغيل البرنامج
	// وعدّاد للثواني بين كل مرة تسرم فيها الشاشة
	// مناسب لإجراء لتحديث مواضع المجسّمات.
	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shape.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // التأكد من رسم محاور مبدأ الاحداثيات فوق كل شي
		axis.render(glm::identity<glm::mat4>(), camera);
		glDepthFunc(GL_LESS);
	}

	// تابع يستدعى مرة واحدة عند نهاية البرنامج
	// مناسب لحفظ تقدّم المستخدم في اللعبة أو إعدادات البرنامج.
	void onExit()
	{

	}

	// ---- توابع مساعدة ---- //

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
	PracticeApplication app;
	app.run({ 600, 600 }, "Hello Texture (L06:P01)");

	return 0;
}