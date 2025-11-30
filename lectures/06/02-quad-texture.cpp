// ---- تضمين المكاتب الخارجية ---- //

#include <glad/glad.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

// ---- تضمين المكاتب الاساسية ---- //

#include <string>
#include <vector>
#include <iostream>

// ---- تضمين ترويسات المشروع ---- //

#include "lab-utils/basic-shape.hpp"
#include "lab-utils/textured-shape.hpp"
#include "lab-utils/orbit-application.hpp"

// ---- قيم مساعدة ---- //

// الألوان المساعدة أصبحت ضمن ترويسات المشروع
#include "lab-utils/colors.hpp"
// using namespace LabUtils::Colors;

// ---- البرنامج ---- //

/*
مهام التمرين:
=============

1. أضف الرأس اللازم أو غيّر رؤوس الشكل المجود ليصبح مربّعاً يعرض الصورة بأكملها.

2. غيّر الصورة المستخدمة إلى
sy-gov-logo.jpg

3. غيّر احداثيات فضاء الصورة لتصبح خارج المجال الأساسي

4. غيّر آلية التعامل مع الاحداثيات خارج المجال الأساسي لتصبح تعمل بالتكرار مع العكس
(Mirror)

5. جرّب تغيير وضعية الـ
Filter
وجرّب وضعيات الـ
Wrap
المختلفة.
*/

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	// ---- متحولات البرنامج ---- //

	LabUtils::BasicShape axis;
	LabUtils::TexturedShape shape;

	glm::mat4 transform = { 1.0f };

	GLuint texture = 0;

	// ---- مراحل حياة البرنامج ---- //

	void onInit() override
	{
		createAxis();
		using namespace LabUtils::Colors;

		// -- تحميل الصورة -- //

		// قراءة ملف الصورة باستخدام SFML
		sf::Image image;
		if (!image.loadFromFile("../../../../../assets/Tiles095_1K-JPG_Color.jpg")) std::exit(1);
		image.flipVertically(); // كي تتوافق مع صيغة الأوبن جي ال

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// نقل الصورة إلى ذاكرة الرسوميّات
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			image.getSize().x, image.getSize().y,
			0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

		// -- تعريف الشكل -- //

		shape = LabUtils::TexturedShape({
			// الموقع (x, y, z), اللون
			{ {0.0f, -0.5f, -0.5f }, white, {0.0f, 0.0f} },
			{ {0.0f, 0.5f, -0.5f}, white, {1.0f, 0.0f} },
			{ {0.0f, -0.5f, 0.5f}, white, {0.0f, 1.0f} },
			// TASK: أضف الرأس اللازم أو أعد تعريف الشكل ليصبح مربّع
			}, GL_TRIANGLE_STRIP);
	}

	void onUpdate(float t, float dt) override
	{

	}

	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Texture Wrap Options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Texture Filter Options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Border Color
		glm::vec4 border_color{ 1.0f, 0.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));

		// تفعيل الصورة
		glBindTexture(GL_TEXTURE_2D, texture);

		shape.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS);
		axis.render(glm::identity<glm::mat4>(), camera);
		glDepthFunc(GL_LESS);
	}

	void onExit()
	{
		glDeleteTextures(1, &texture);
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
	app.run({ 600, 600 }, "Quad Texture (L06:P02)");

	return 0;
}