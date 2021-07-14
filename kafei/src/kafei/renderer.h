#ifndef KAFEI_RENDERER_H
#define KAFEI_RENDERER_H

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

namespace kafei {

struct Vec2 {
    float x, y;
};

struct Tri {
    Vec2 left;
    Vec2 right;
    Vec2 top;

    Tri() {}
    Tri(Vec2 left, Vec2 right, Vec2 top);
    std::vector<float> ToVertices();
    void Render();
};

struct Rect {
    Vec2 pos, size;
    unsigned int indices[6] = {
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    Rect(Vec2 pos, Vec2 size);
    std::vector<float> ToVertices();
    void Render();
};

/**
 * Singleton class for rendering things.
 */
class Renderer {
   public:
    static std::unique_ptr<Renderer>& GetInstance();

    ~Renderer() = default;

    std::pair<int, int> GetWindowSize();

    bool SetupShaders();

   private:
    Renderer() {}

    bool CheckShaderCompilation(unsigned int shader);

    bool CheckShaderLinking(unsigned int shaderProgram);

    // singleton instance
    static std::unique_ptr<Renderer> _instance;
};

}  // namespace kafei

#endif  // KAFEI_RENDERER_H