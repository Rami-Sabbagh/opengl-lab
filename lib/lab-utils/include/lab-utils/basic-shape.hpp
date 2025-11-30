#pragma once

#include <vector>
#include <glm/mat4x4.hpp>

#include "lab-utils/basic-shader.hpp"

namespace LabUtils
{
	class BasicShape
	{
	protected:
		int verticesCount = 0;

		GLuint shaderProgram = 0;
		GLuint cameraLocation = 0, transformLocation = 0;
		GLuint VAO = 0, VBO = 0;

		GLenum drawMode = GL_TRIANGLES;

	public:
		BasicShape();
		BasicShape(const std::vector<BasicVertex>& vertices, GLenum drawMode = GL_TRIANGLES);
		~BasicShape();

		BasicShape& operator=(BasicShape&& other) noexcept;

		void render(const glm::mat4& transform = {1.0f}, const glm::mat4& camera = { 1.0f }) const;
	};
}