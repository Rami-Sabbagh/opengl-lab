#include<iostream>
#include<string>

#include<glad/glad.h>

#include "lab-utils/shaders-utils.hpp"

namespace LabUtils
{

    GLuint compileShader(GLenum type, const char* source, const std::string& name)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        char infoLog[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            int length;
            glGetProgramInfoLog(shader, 512, &length, infoLog);
            if (length > 0)
                std::cout << "Failed to compile shader (" << name << "):\n" << infoLog << std::endl;
            else
                std::cout << "Failed to compile shader (" << name << ")!" << std::endl;

            std::exit(1);
        }

        return shader;
    }

    GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader, const std::string& name)
    {
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        GLint success;
        char infoLog[512];

        glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            int length;
            glGetProgramInfoLog(shaderProgram, 512, &length, infoLog);
            if (length > 0)
                std::cout << "Failed to link shader program (" << name << "):\n" << infoLog << std::endl;
            else
                std::cout << "Failed to link shader progrm (" << name << ")!" << std::endl;

            std::exit(1);
        }

        return shaderProgram;
    }

    GLuint compileAndLinkShaderProgram(const char* vertexSource, const char* fragmentSource, const std::string& name)
    {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource, name + "/vertex.glsl");
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource, name + "/fragment.glsl");

        GLuint shaderProgram = linkShaderProgram(vertexShader, fragmentShader, name);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

}