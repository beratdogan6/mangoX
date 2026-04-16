#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

class Window {
  public:
    Window(int width, int height, const char *title);
    ~Window();

    bool is_open() const;
    void poll_events();
    void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);
    void swap_buffers();
    GLFWwindow *handle() const;

  private:
    GLFWwindow *m_handle;

    static void error_callback(int error, const char *description);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif // !WINDOW_HPP
