#ifndef KAFEI_WINDOW_H
#define KAFEI_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <ResourceManager.h>
#include <glad/glad.h>
#include <render.h>
#include <shader.h>

namespace kafei {

/// TODO: Have the Kafei class build a world and add entities to the world
class World {
  public:
    World() : r({100.0f, 100.0f}, {100.0f, 100.0f}) {}

    void init() {
        // TODO Set default shader
        auto& res = Res::GetInstance();
        r.SetShader(res->Get("shaders/default.vert"), res->Get("shaders/default.frag"));
        r.SetTexture("c++.png");

        r.Init();
    }

    void update() {
        r.Render();
    }

  private:
    Rect r;
};

class Game {
  public:
    Game() {}

    void set_title(std::string t) {
        title = t;
    }

    void set_world(World* world) {
        active_world.reset(world);
    }

    void engine_update() {
        // Trying to render a rectangle at (10, 10) with a width & height of 10
        active_world->update();
    }

    std::pair<int, int> get_window_size() {
        GLFWwindow* window = glfwGetCurrentContext();
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return std::make_pair(width, height);
    }

    void start() {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return;

        // Create a windowed mode window and its OpenGL context
        // I don't like how I set the title, pass in the config item, but keep
        // the config options maybe?
        window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);
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

        // Setup resource manager
        auto& res = Res::GetInstance();
        res->SetResPath("res");

        // Create the default shader
        // TODO: Use a resource manager class to handle paths, possibly with an ENV_VAR
        // KAFEI_RESOURCE_PATH or something like that.
        Shader def_shader{res->Get("shaders/default.vert"), res->Get("shaders/default.frag")};

        // Setup everything else before the active world
        // TODO: pass in the starting world
        set_world(new World());

        active_world->init();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            def_shader.use();

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            // update loop
            engine_update();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }

  private:
    std::unique_ptr<World> active_world;
    std::string title;
};
} // namespace kafei

#endif // KAFEI_WINDOW_H