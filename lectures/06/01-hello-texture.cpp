// ---- تضمين المكاتب الخارجية ---- //

#include <glad/glad.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
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

	GLuint texture = 0;

	// ---- مراحل حياة البرنامج ---- //

	void onInit() override
	{
		createAxis();
		using namespace Colors;

		// -- تحميل الصورة -- //

		// قراءة ملف الصورة باستخدام SFML
		sf::Image image;
		if (!image.loadFromFile("assets/Tiles095_1K-JPG_Color.jpg")) std::exit(1);
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
			{ {0.0f, 0.0f, 0.8f }, red, {0.5f, 1.0f} }, // الزاوية العلوية
			{ {0.0f, 0.5f, -0.5f}, green, {1.0f, 0.0f} }, // الزاوية السفلية - اليمينية
			{ {0.0f, -0.5f, -0.5f}, blue, {0.0f, 0.0f} }, // الزاوية السفلية - اليسارية
			}, GL_TRIANGLES);
	}

	void onUpdate(float t, float dt) override
	{
		
	}

	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		shape.render(transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS); // التأكد من رسم محاور مبدأ الاحداثيات فوق كل شي
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
	app.run({ 600, 600 }, "Hello Texture (L06:P01)");

	return 0;
}