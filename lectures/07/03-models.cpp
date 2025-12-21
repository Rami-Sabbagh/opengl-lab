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
#include "lab-utils/orbit-application.hpp"

#include "learnopengl/shader.h"
#include "learnopengl/model.h"

// ---- قيم مساعدة ---- //

// الألوان المساعدة أصبحت ضمن ترويسات المشروع
#include "lab-utils/colors.hpp"
// using namespace LabUtils::Colors;

// ---- البرنامج ---- //

class PracticeApplication : public LabUtils::LabOrbitApplication
{
	// ---- متحولات البرنامج ---- //

	LabUtils::BasicShape axis;

	Shader shader;
	Model model;
	glm::mat4 transform{ 1.0f };

	// ---- مراحل حياة البرنامج ---- //

	void onInit() override
	{
		createAxis();

		shader = Shader(
			"../../../../../assets/shaders/model.vert",
			"../../../../../assets/shaders/model.frag"
		);

		std::cout << "Loading model... ";

		model = Model(
			"../../../../../assets/backpack/backpack.obj"
		);

		std::cout << "Loaded." << std::endl;

		transform = glm::translate(transform, { 0.3f, 0.0f, 0.0f });
		transform = glm::rotate(transform, glm::radians(90.0f), { 0.0f, 0.0f, 1.0f });
		transform = glm::rotate(transform, glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
		transform = glm::scale(transform, glm::vec3{ 0.25f });
	}

	void onUpdate(float t, float dt) override
	{

	}

	void onDraw(float t, float dt) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setMat4("model", transform);
		model.Draw(shader);

		glLineWidth(3.0f);
		//glDepthFunc(GL_ALWAYS);
		axis.render(glm::identity<glm::mat4>(), camera);
		//glDepthFunc(GL_LESS);
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
};

// ==========--: نقطة دخول البرنامج :--========== //

int main() {
	PracticeApplication app;
	app.run({ 600, 600 }, "Models (L07:P03)");

	return 0;
}