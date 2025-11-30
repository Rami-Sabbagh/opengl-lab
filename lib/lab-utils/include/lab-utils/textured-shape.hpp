#pragma once

// ---- تضمين المكاتب الخارجية ---- //

// من أجل استخدام اصدار حديث من الأوبن جي ال
// لا بد من استخدام مكتبة وسيطة
// GLAD: https://github.com/Dav1dde/glad, https://glad.dav1d.de/
// المرجع: https://docs.gl/ أو https://devdocs.io/
#include <glad/glad.h>

// للتعامل مع الأشعة والمصفوفات الرياضية
// وانشاء مصفوفات تحويلات هندسية وإسقاط
// GLM: OpenGL Mathematics: https://github.com/g-truc/glm/
// دليل المستخدم: https://github.com/g-truc/glm/blob/master/manual.md
// لربما من الأحسن الإعتماد على التتمة التلقائية أثناء الكتابة،
// أو قراءة ملفات التوريس مباشرة.
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace LabUtils
{
	struct TexturedVertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 uv;
	};

	class TexturedShape
	{
	protected:
		int verticesCount = 0;

		GLuint cameraLocation = 0, transformLocation = 0;
		GLuint VAO = 0, VBO = 0;

		GLenum drawMode = GL_TRIANGLES;

	public:
		static GLuint shaderProgram;
		static void compileShapeShader();

		TexturedShape();
		TexturedShape(const std::vector<TexturedVertex>& vertices, GLenum drawMode = GL_TRIANGLES);
		~TexturedShape();

		TexturedShape& operator=(TexturedShape&& other) noexcept;

		void render(const glm::mat4& transform = { 1.0f }, const glm::mat4& camera = { 1.0f }) const;
	};
}