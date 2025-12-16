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
#include "lab-utils/alpha-shape.hpp"
#include "lab-utils/orbit-application.hpp"

// ---- قيم مساعدة ---- //

// الألوان المساعدة أصبحت ضمن ترويسات المشروع
#include "lab-utils/colors.hpp"
// using namespace LabUtils::Colors;

// ---- البرنامج ---- //

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	// ---- متحولات البرنامج ---- //

	LabUtils::BasicShape axis;
	LabUtils::BasicShape cube;
	LabUtils::AlphaShape plane;

	glm::mat4 cube_transform = { 1.0f };
	glm::mat4 plane_transform = { 1.0f };

	GLuint texture = 0;

	// ---- مراحل حياة البرنامج ---- //

	void onInit() override
	{
		createAxis();
		createCube();
		createPlane();

		// -- Transformations -- //

		cube_transform = glm::scale(cube_transform, { 0.5f, 0.5f, 0.5f });
		cube_transform = glm::translate(cube_transform, { -0.75f, 0.0f, 0.0f });

		plane_transform = glm::translate(plane_transform, { 0.25f, 0.0f, 0.0f });

		// -- Enable Blending -- //

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
	}

	void onUpdate(float t, float dt) override
	{

	}

	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.render(cube_transform, camera);
		plane.render(plane_transform, camera);

		glLineWidth(3.0f);
		glDepthFunc(GL_ALWAYS);
		axis.render(glm::identity<glm::mat4>(), camera);
		glDepthFunc(GL_LESS);
	}

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

	void createCube()
	{
		// النموذج مطابق للصورة في السلايدات.
		using namespace LabUtils::Colors;

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

	void createPlane()
	{
		glm::vec4 color{ 0.0f, 1.0f, 1.0f, 0.2f };

		plane = LabUtils::AlphaShape({
			{ { 0.0f, -0.5f, -0.5f }, color },
			{ { 0.0f, 0.5f, -0.5f }, color },
			{ { 0.0f, 0.5f, 0.5f }, color },
			{ { 0.0f, -0.5f, 0.5f }, color },
			}, GL_TRIANGLE_FAN);
	}
};

// ==========--: نقطة دخول البرنامج :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "Blending (L07:P01)");

	return 0;
}