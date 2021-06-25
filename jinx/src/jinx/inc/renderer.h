#ifndef JINX_RENDERER_H
#define JINX_RENDERER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <memory>
#include <tuple>
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
    Point left;
    Point right;
    Point top;

    Triangle() {}

    Triangle(Point left, Point right, Point top);

    std::vector<float> ToVertices();
};

struct Rect {
    Triangle l;
    Triangle r;

    Rect(float x, float y, float w, float h);

    void Render();
};

/**
 * Singleton class for rendering things.
 */
class Renderer {
   public:
    static std::unique_ptr<Renderer>& GetInstance();

    ~Renderer() = default;

    void RenderTriangle(Triangle& t);

    std::pair<int, int> GetWindowSize();

    // TODO: one VAO isn't correct, each "batch" should have a VAO, work on this
    void SetupVAO();

    bool SetupShaders();

   private:
    Renderer() {}

    bool CheckShaderCompilation(unsigned int shader);

    bool CheckShaderLinking(unsigned int shaderProgram);

    // singleton instance
    static std::unique_ptr<Renderer> _instance;
};

}  // namespace jinx

#endif  // JINX_RENDERER_H