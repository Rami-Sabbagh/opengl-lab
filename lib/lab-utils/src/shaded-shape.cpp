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
#include "lab-utils/shaded-shape.hpp"

// ---- الشيدر البسيط للرسم من دون إضاءة ---- //

static const char* SHADED_VERTEX_SHADER_SRC = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 worldPosition;
out vec3 normal;

uniform mat4 camera;
uniform mat4 transform;
uniform mat3 nTransform;

void main() {
	gl_Position = camera * transform * vec4(aPos, 1.0);
	
	worldPosition = vec3(transform * vec4(aPos, 1.0));
	normal = nTransform * aNormal;
}
)";

static const char* SHADED_FRAMGENT_SHADER_SRC = R"(
#version 330 core
out vec4 FragColor;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 worldPosition;
in vec3 normal;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

uniform Material material;

void main() {
	// Light wannabe Uniforms
	vec3 lightColor = vec3(1.0);

	// Intermediate values
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - worldPosition);
	vec3 cameraDirection = normalize(cameraPosition - worldPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);

	// Ambient Lighting
	vec3 ambient = lightColor * material.ambient;

	// Diffuse Lighting
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = lightColor * diff * material.diffuse;

	// Specular Lighting
	float spec = pow(max(dot(cameraDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = lightColor * spec * material.specular;

	// Mixing colors
	//vec3 result = specular;
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}
)";

// ---- الصف المساعد لرسم الأشكاء ---- //

namespace LabUtils
{
	GLuint ShadedShape::shaderProgram = 0;

	void ShadedShape::compileShapeShader()
	{
		if (shaderProgram != 0) return; // Shader already compiled.
		shaderProgram = compileAndLinkShaderProgram(SHADED_VERTEX_SHADER_SRC, SHADED_FRAMGENT_SHADER_SRC, "shaded-shader");
	}

	ShadedShape::ShadedShape()
	{
		verticesCount = 0;
	}

	ShadedShape::ShadedShape(const std::vector<ShadedVertex>& vertices, GLenum drawMode, const ShadedMaterial& material)
	{
		verticesCount = vertices.size();
		if (verticesCount == 0) return; // Don't render empty shapes.

		this->drawMode = drawMode;

		compileShapeShader(); // Ensure the shader is compiled.

		// Upload Vertex Data
		int size = verticesCount * sizeof(ShadedVertex);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

		// Configure Attributes
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// - Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShadedVertex), (void*)(offsetof(ShadedVertex, position)));
		glEnableVertexAttribArray(0);
		// - Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShadedVertex), (void*)(offsetof(ShadedVertex, normal)));
		glEnableVertexAttribArray(1);

		// Send constant uniforms
		setUniform("material", material);
	}

	ShadedShape::~ShadedShape()
	{
		if (verticesCount == 0) return;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);

		verticesCount = 0;
	}

	ShadedShape& ShadedShape::operator=(ShadedShape&& other) noexcept
	{
		if (this != &other)
		{
			// free existing resources
			if (verticesCount != 0) this->~ShadedShape();

			// steal resources
			verticesCount = other.verticesCount;
			shaderProgram = other.shaderProgram;
			uniforms = std::move(other.uniforms);
			VAO = other.VAO;
			VBO = other.VBO;

			drawMode = other.drawMode;

			// leave other in null state
			other.verticesCount = 0;
		}

		return *this;
	}

	void ShadedShape::render(
		const glm::mat4& transform,
		const glm::mat4& camera,
		const glm::vec3& cameraPosition
	) {
		if (verticesCount == 0) return;

		glm::mat3 nTransform = glm::mat3(glm::transpose(glm::inverse(transform)));

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		setUniform("transform", transform);
		setUniform("nTransform", nTransform);

		setUniform("camera", camera);
		setUniform("cameraPosition", cameraPosition);
		glDrawArrays(drawMode, 0, verticesCount);
	}

	GLuint ShadedShape::getUniformLocation(const std::string& name)
	{
		auto iter = uniforms.find(name);
		if (iter != uniforms.end()) return iter->second;

		GLuint location = glGetUniformLocation(shaderProgram, name.c_str());
		if (location == -1)
		{
			std::cerr << "Uniform '" << name << "' not found." << std::endl;
			std::exit(1);
		}

		uniforms[name] = location;
		return location;
	}

	void ShadedShape::setUniform(const std::string& name, float value)
	{
		glUseProgram(shaderProgram);
		glUniform1f(getUniformLocation(name), value);
	}

	void ShadedShape::setUniform(const std::string& name, const glm::vec3& value)
	{
		glUseProgram(shaderProgram);
		glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
	}

	void ShadedShape::setUniform(const std::string& name, const glm::mat3& value)
	{
		glUseProgram(shaderProgram);
		glUniformMatrix3fv(getUniformLocation(name), 1, false, glm::value_ptr(value));
	}

	void ShadedShape::setUniform(const std::string& name, const glm::mat4& value)
	{
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(getUniformLocation(name), 1, false, glm::value_ptr(value));
	}

	void ShadedShape::setUniform(const std::string& name, const ShadedMaterial& value)
	{
		setUniform(name + ".ambient", value.ambient);
		setUniform(name + ".diffuse", value.diffuse);
		setUniform(name + ".specular", value.specular);
		setUniform(name + ".shininess", value.shininess);
	}
}

