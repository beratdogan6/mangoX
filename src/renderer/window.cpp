#include "window.hpp"
#include "GLFW/glfw3.h"
#include <cstdio>

Window::Window(int width, int height, const char *title) : m_handle(nullptr) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_handle) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_handle);
    glfwSetFramebufferSizeCallback(m_handle, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return;
    }

    glViewport(0, 0, width, height);
}

Window::~Window() { glfwTerminate(); }

bool Window::is_open() const { return m_handle && !glfwWindowShouldClose(m_handle); }

void Window::poll_events() {
    if (glfwGetKey(m_handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_handle, true);

    glfwPollEvents();
}

void Window::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap_buffers() { glfwSwapBuffers(m_handle); }

GLFWwindow *Window::handle() const { return m_handle; }

void Window::error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

void Window::framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}
