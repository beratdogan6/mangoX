#include <cstdio>
#include <glad/glad.h>

#include "shader.hpp"

Shader::Shader(const char *vertex_src, const char *fragment_src) {
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertex_src, nullptr);
    glCompileShader(vert);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_src, nullptr);
    glCompileShader(fragment);

    int success;
    char log[512];

    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert, 512, nullptr, log);
        fprintf(stderr, "Vertex shader error: %s\n", log);
    }

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, log);
        fprintf(stderr, "Fragment shader error: %s\n", log);
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vert);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    glDeleteShader(vert);
    glDeleteShader(fragment);
}

Shader::~Shader() { glDeleteProgram(m_id); }

void Shader::use() { glUseProgram(m_id); }

void Shader::set_vec2(const char *name, float x, float y) {
    int location = glGetUniformLocation(m_id, name);
    glUniform2f(location, x, y);
}
