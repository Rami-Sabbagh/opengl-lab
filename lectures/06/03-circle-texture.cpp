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

1. صحّح احداثيّات فضاء الصورة لتظهر الصورة على الدائرة بشكل صحيح.
2. غيّر احداثيات مركز الدائرة ليصبح الشكل أشبه بمخروط.
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
		if (!image.loadFromFile("../../../../../assets/sy-gov-logo.jpg")) std::exit(1);
		image.flipVertically(); // كي تتوافق مع صيغة الأوبن جي ال

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// نقل الصورة إلى ذاكرة الرسوميّات
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			image.getSize().x, image.getSize().y,
			0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

		// -- تعريف الشكل -- //

		std::vector<LabUtils::TexturedVertex> vertices{
			{{ 0.0f, 0.0f, 0.0f }, white, { 0.5f, 0.5f }}, // مركز الدائرة
		};

		float segments = 16, radius = 0.5f;
		float step = glm::radians(360.0f) / segments;

		for (float angle = 0.0f; angle <= glm::radians(360.1f); angle += step)
			vertices.push_back({
				{0.0f, glm::cos(angle) * radius, glm::sin(angle) * radius},
				white,
				{0.0f, 0.0f}, // TASK: صحّح احداثيات فضاء الصورة
			});

		shape = LabUtils::TexturedShape(vertices, GL_TRIANGLE_FAN);
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
	app.run({ 600, 600 }, "Circle Texture (L06:P03)");

	return 0;
}