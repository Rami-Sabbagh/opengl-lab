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
#include "lab-utils/shaded-shape.hpp"
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
	LabUtils::ShadedShape cube;

	glm::mat4 transform = { 1.0f };

	GLuint texture = 0;

	// ---- مراحل حياة البرنامج ---- //

	void onInit() override
	{
		createAxis();
		createCube({
			glm::vec3{ 0.05f }, // Ambient
			glm::vec3{ 0.8f }, // Diffuse
			glm::vec3{ 1.0f }, // Specular
			256.0f // Shininess
			});
	}

	void onUpdate(float t, float dt) override
	{
		transform = glm::identity<glm::mat4>();
		transform = glm::scale(transform, { 0.5f, 0.5f, 0.5f });
		transform = glm::rotate(transform, glm::radians(t * -5.0f), { 0.0f, 0.0f, 1.0f });
	}

	void onDraw(float t, float dt) override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.setUniform("lightPosition", {
			1.0f, 0.0f, glm::sin(glm::radians(t * 45.0f)) * 0.3f
			});
		cube.render(transform, camera, cameraPosition);

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

	void createCube(const LabUtils::ShadedMaterial& material)
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

		glm::vec3 UP{ 0.0f, 0.0f, 1.0f };
		glm::vec3 DOWN{ 0.0f, 0.0f, -1.0f };
		glm::vec3 RIGHT{ 0.0f, 1.0f, 0.0f };
		glm::vec3 LEFT{ 0.0f, -1.0f, 0.0f };
		glm::vec3 FRONT{ 1.0f, 0.0f, 0.0f };
		glm::vec3 BACK{ -1.0f, 0.0f, 0.0f };

		cube = LabUtils::ShadedShape({
			// الوجه العلوي
			{ A, UP }, { B, UP }, { C, UP },
			{ C, UP }, { D, UP }, { A, UP },

			// الوجه الأمامي
			{ B, FRONT }, { F, FRONT }, { C, FRONT },
			{ C, FRONT }, { F, FRONT }, { G, FRONT },

			// الوجه اليميني
			{ C, RIGHT }, { G, RIGHT }, { D, RIGHT },
			{ D, RIGHT }, { G, RIGHT }, { H, RIGHT },

			// الوجه الخلفي
			{ D, BACK }, { H, BACK }, { A, BACK },
			{ A, BACK }, { H, BACK }, { E, BACK },

			// الوجه اليساري
			{ A, LEFT }, { E, LEFT }, { B, LEFT },
			{ B, LEFT }, { E, LEFT }, { F, LEFT },

			// الوجه السفلي
			{ E, DOWN }, { H, DOWN }, { F, DOWN },
			{ F, DOWN }, { H, DOWN }, { G, DOWN },
			},
			GL_TRIANGLES,
			material);
	}
};

// ==========--: نقطة دخول البرنامج :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "Lighting (L07:P02)");

	return 0;
}