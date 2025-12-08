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
#include "lab-utils/textured-shape.hpp"

// ---- الشيدر البسيط للرسم من دون إضاءة ---- //

static const char* TEXTURED_VERTEX_SHADER_SRC = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aUV;

out vec3 vertexColor;
out vec2 textureCoord;

uniform mat4 camera;
uniform mat4 transform;

void main() {
gl_Position = camera * transform * vec4(aPos, 1.0);
vertexColor = aColor;
textureCoord = aUV;
}
)";

static const char* TEXTURED_FRAMGENT_SHADER_SRC = R"(
#version 330 core

in vec3 vertexColor;
in vec2 textureCoord;

out vec4 FragColor;

uniform sampler2D shapeTexture;

void main() {
FragColor = texture(shapeTexture, textureCoord) * vec4(vertexColor, 1.0);
}
)";

// ---- الصف المساعد لرسم الأشكاء ---- //

namespace LabUtils
{
	GLuint TexturedShape::shaderProgram = 0;

	void TexturedShape::compileShapeShader()
	{
		if (shaderProgram != 0) return; // Shader already compiled.
		shaderProgram = compileAndLinkShaderProgram(TEXTURED_VERTEX_SHADER_SRC, TEXTURED_FRAMGENT_SHADER_SRC, "textured-shader");
	}

	TexturedShape::TexturedShape()
	{
		verticesCount = 0;
	}

	TexturedShape::TexturedShape(const std::vector<TexturedVertex>& vertices, GLenum drawMode)
	{
		verticesCount = vertices.size();
		if (verticesCount == 0) return; // Don't render empty shapes.

		this->drawMode = drawMode;

		compileShapeShader(); // Ensure the shader is compiled.

		// Upload Vertex Data
		int size = verticesCount * sizeof(TexturedVertex);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

		// Configure Attributes
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// - Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)(offsetof(TexturedVertex, position)));
		glEnableVertexAttribArray(0);
		// - Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)(offsetof(TexturedVertex, color)));
		glEnableVertexAttribArray(1);
		// - UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)(offsetof(TexturedVertex, uv)));
		glEnableVertexAttribArray(2);

		// Get Uniforms Locations
		cameraLocation = glGetUniformLocation(shaderProgram, "camera");
		transformLocation = glGetUniformLocation(shaderProgram, "transform");
	}

	TexturedShape::~TexturedShape()
	{
		if (verticesCount == 0) return;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);

		verticesCount = 0;
	}

	TexturedShape& TexturedShape::operator=(TexturedShape&& other) noexcept
	{
		if (this != &other)
		{
			// free existing resources
			if (verticesCount != 0) this->~TexturedShape();

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

	void TexturedShape::render(const glm::mat4& transform, const glm::mat4& camera) const
	{
		if (verticesCount == 0) return;

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glUniformMatrix4fv(cameraLocation, 1, false, glm::value_ptr(camera));
		glUniformMatrix4fv(transformLocation, 1, false, glm::value_ptr(transform));
		glDrawArrays(drawMode, 0, verticesCount);
	}
}

