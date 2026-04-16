#include <glad/glad.h>

#include "renderer/shader.hpp"
#include "renderer/window.hpp"

// clang-format off
const char *VERT_SRC = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vColor;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)";

const char *FRAG_SRC = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

static float VERTS[] = {
//   x      y      r     g     b
     0.0f,  0.5f,  0.0f, 0.0f, 1.0f,  // top   — blue
    -0.4f, -0.4f,  1.0f, 0.0f, 0.0f,  // left  — red
     0.4f, -0.4f,  0.0f, 1.0f, 0.0f,  // right — green
};
// clang-format on

int main() {
    Window window(1280, 720, "mangoX");
    Shader shader(VERT_SRC, FRAG_SRC);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTS), VERTS, GL_STATIC_DRAW);

    // position: location 0, 2 floats, stride 5 floats, offset 0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color: location 1, 3 floats, stride 5 floats, offset 2 floats
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (window.is_open()) {
        window.poll_events();
        window.clear();
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.swap_buffers();
    }

    return 0;
}
