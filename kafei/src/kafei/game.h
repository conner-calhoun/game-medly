#ifndef KAFEI_WINDOW_H
#define KAFEI_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <quad.h>
#include <resource_manager.h>
#include <shader.h>
#include <world.h>
#include <world_manager.h>

namespace kafei {

class Game {
  public:
    Game() : wm() {}

    void set_title(std::string t) {
        title = t;
    }

    void engine_update() {
        wm.update();
    }

    void load_config(Config& cfg) {
        set_title(cfg.get_title());
    }

    void set_world(World* world) {
        wm.set_world(world);
    }

    void set_default_world(World* world) {
        wm.set_default_world(world);
    }

    std::pair<int, int> get_window_size() {
        GLFWwindow* window = glfwGetCurrentContext();
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return std::make_pair(width, height);
    }

    virtual void start() final {
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
        auto& res = Res::get_instance();
        res->set_res_path("res");

        // Create the default shader
        // TODO: Use a resource manager class to handle paths, possibly with an ENV_VAR
        // KAFEI_RESOURCE_PATH or something like that.
        Shader default_shader{res->get("shaders/default.vert"), res->get("shaders/default.frag")};

        // Setup everything else before 'initing' the default world
        wm.init();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            default_shader.use();

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
    WorldManager wm;
    std::string title;
    bool setup;
};
} // namespace kafei

#endif // KAFEI_WINDOW_H