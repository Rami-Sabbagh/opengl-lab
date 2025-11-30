// عزيزي الطالب، هذا ملف مثال، ولك كامل الحرية في تعديله
// ذكرت الغاية والمراجع لجميع المكاتب المستخدمة.

// ---- تضمين المكاتب الخارجية ---- //

// من أجل استخدام اصدار حديث من الأوبن جي ال
// لا بد من استخدام مكتبة وسيطة
// GLAD: https://github.com/Dav1dde/glad, https://glad.dav1d.de/
// المرجع: https://docs.gl/ أو https://devdocs.io/
#include <glad/glad.h>

// ---- تضمين المكاتب الاساسية ---- //

#include <iostream>
#include <string>

// ---- تضمين ترويسات المشروع ---- //

#include "lab-utils/shader-utils.hpp"
#include "lab-utils/basic-shape.hpp"

// ---- الشيدر البسيط للرسم من دون إضاءة ---- //

static const char* BASIC_VERTEX_SHADER_SRC = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 camera;
uniform mat4 transform;

void main() {
gl_Position = camera * transform * vec4(aPos, 1.0);
vertexColor = aColor;
}
)";

static const char* BASIC_FRAMGENT_SHADER_SRC = R"(
#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main() {
FragColor = vec4(vertexColor, 1.0);
}
)";

// ---- الصف المساعد لرسم الأشكاء ---- //

namespace LabUtils
{
	BasicShape::BasicShape()
	{
		verticesCount = 0;
	}

	BasicShape::BasicShape(const std::vector<BasicVertex>& vertices, GLenum drawMode)
	{
		verticesCount = vertices.size();
		if (verticesCount == 0) return; // Don't render empty shapes.

		this->drawMode = drawMode;

		shaderProgram = compileAndLinkShaderProgram(BASIC_VERTEX_SHADER_SRC, BASIC_FRAMGENT_SHADER_SRC, "basic-shader");

		// Upload Vertex Data
		int size = verticesCount * sizeof(BasicVertex);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

		// Configure Attributes
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// - Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)(offsetof(BasicVertex, position)));
		glEnableVertexAttribArray(0);
		// - Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)(offsetof(BasicVertex, color)));
		glEnableVertexAttribArray(1);

		// Get Uniforms Locations
		cameraLocation = glGetUniformLocation(shaderProgram, "camera");
		transformLocation = glGetUniformLocation(shaderProgram, "transform");
	}

	BasicShape::~BasicShape()
	{
		if (verticesCount == 0) return;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);

		verticesCount = 0;
	}

	BasicShape& BasicShape::operator=(BasicShape&& other) noexcept
	{
		if (this != &other)
		{
			// free existing resources
			if (verticesCount != 0) this->~BasicShape();

			// steal resources
			verticesCount = other.verticesCount;
			shaderProgram = other.shaderProgram;
			cameraLocation = other.cameraLocation;
			transformLocation = other.transformLocation;
			VAO = other.VAO;
			VBO = other.VBO;

			drawMode = other.drawMode;

			// leave other in null state
			other.verticesCount = 0;
		}

		return *this;
	}

	void BasicShape::render(const glm::mat4& transform, const glm::mat4& camera) const
	{
		if (verticesCount == 0) return;

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glUniformMatrix4fv(cameraLocation, 1, false, glm::value_ptr(camera));
		glUniformMatrix4fv(transformLocation, 1, false, glm::value_ptr(transform));
		glDrawArrays(drawMode, 0, verticesCount);
	}
}

