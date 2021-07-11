#ifndef KAFEI_WINDOW_H
#define KAFEI_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <renderer.h>

namespace kafei {

class Window {
   public:
    Window() {}

    void SetTitle(std::string t) { _title = t; }

    void EngineUpdate() {
        // Trying to render a rectangle at (10, 10) with a width & height of 10

        Rect r{{100.0f, 100.0f}, {100.0f, 100.0f}};
        r.Render();
    }

    void Start() {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit()) return;

        // Create a windowed mode window and its OpenGL context
        // I don't like how I set the title, pass in the config item, but keep
        // the config options maybe?
        window = glfwCreateWindow(640, 480, _title.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            return;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            // TODO: replace cout's with a logger
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // register shaders, not sure how to change shaders later tho..
        if (!Renderer::GetInstance()->SetupShaders()) {
            std::cout << "shaders not set up correctly" << std::endl;
            return;
        }

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            // update loop
            EngineUpdate();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }

   private:
    std::string _title;
};
}  // namespace kafei

#endif  // KAFEI_WINDOW_H