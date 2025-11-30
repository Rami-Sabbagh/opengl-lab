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

/*
المهمة:
-------

1. جرب تشغيل البرنامج وانظر إلى المكعب، حرّك بالفأرة.
2. في تابع الرسم، فعّل عملية إلغاء الوجوه ثم جرب البرنامج.
3. يوجد مثلث ملفوف باتجاه خاطئ في الوجه الأمامي، أصلحه. وجرّب البرنامج.
4. غير عملية إلغاء الوجوه لتلغي الوجوه الأمامية بدل الخلفية باستخدام التعليمة المناسبة في تابع الرسم، ثم جرب البرنامج.

*/

// ---- البرنامج ---- //

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

	// ---- مراحل حياة البرنامج ---- //

	// تابع يستدعى مرة واحدة عند بدئ البرنامج.
	// مناسب لإنشاء النماذج وتحديد موضعها الابتدائي
	// وتحميل الصور على الذاكرة.
	void onInit() override
	{
		createAxis();
		createCube();
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

	// تابع يستدعى مرة واحدة عند نهاية البرنامج
	// مناسب لحفظ تقدّم المستخدم في اللعبة أو إعدادات البرنامج.
	void onExit()
	{

	}
};

// ==========--: نقطة دخول البرنامج :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "Faces Culling (L02:P04)");

	return 0;
}