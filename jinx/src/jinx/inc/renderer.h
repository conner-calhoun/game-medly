#ifndef JINX_RENDERER_H
#define JINX_RENDERER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <memory>
#include <vector>

/**
 * OpenGL Rendering code will go here
 * right now this code is in window.h
 */

namespace jinx {

struct Point {
    float x;
    float y;
};

struct Triangle {
    Point _left;
    Point _right;
    Point _top;

    Triangle() {}

    Triangle(Point left, Point right, Point top) {
        _left = left;
        _right = right;
        _top = top;
    }

    std::vector<float> ToVertices() {
        return {_left.x, _left.y, 0.0f,   _right.x, _right.y,
                0.0f,    _top.x,  _top.y, 0.0f};
    }
};

/**
 * Singleton class for rendering things.
 */
class Renderer {
  public:
    static std::unique_ptr<Renderer>& GetInstance();

    ~Renderer() = default;

    void RenderTriangle(Triangle t) {
        // get vertices from triangle
        std::vector<float> vertices = t.ToVertices();

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                     &vertices.front(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);

        // draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // TODO: one VAO isn't correct, each "batch" should have a VAO, work on this
    void SetupVAO() {
        unsigned int VAO;
        glGenBuffers(1, &VAO);
        glBindVertexArray(VAO);
    }

    bool SetupShaders();

  private:
    Renderer() {}

    bool CheckShaderCompilation(unsigned int shader) {
        int success;
        char info_log[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << info_log << std::endl;
        }

        return success;
    }

    bool CheckShaderLinking(unsigned int shaderProgram) {
        int success;
        char info_log[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
        }

        return success;
    }

    // singleton instance
    static std::unique_ptr<Renderer> _instance;
};

} // namespace jinx

#endif // JINX_RENDERER_H