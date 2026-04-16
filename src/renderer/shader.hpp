#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
  public:
    Shader(const char *vertex_src, const char *fragment_src);
    Shader(Shader &&) = default;
    Shader(const Shader &) = default;
    Shader &operator=(Shader &&) = default;
    Shader &operator=(const Shader &) = default;
    ~Shader();
    void use();
    void set_vec2(const char *name, float x, float y);

  private:
    unsigned int m_id;
};
#endif // !SHADER_HPP
