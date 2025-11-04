#ifndef LAB_UTILS__SHADERS_UTILS_HPP
#define LAB_UTILS__SHADERS_UTILS_HPP

#include<string>
#include<glad/glad.h>

namespace LabUtils
{
	GLuint compileShader(GLenum type, const char* source, const std::string& name = "-UNNAMED-");
	GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader, const std::string& name = "-UNNAMED-");
	GLuint compileAndLinkShaderProgram(const char* vertexSource, const char* fragmentSource, const std::string& name = "-UNNAMED-");
}

#endif // LAB_UTILS__SHADERS_UTILS_HPP