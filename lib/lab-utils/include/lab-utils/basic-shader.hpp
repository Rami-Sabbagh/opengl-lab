#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/vec3.hpp>

#include "lab-utils/shaders-utils.hpp"

namespace LabUtils
{
    struct BasicVertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };

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

    static inline GLuint createBasicShaderProgram()
    {
        return compileAndLinkShaderProgram(BASIC_VERTEX_SHADER_SRC, BASIC_FRAMGENT_SHADER_SRC, "basic-shader");
    }
}