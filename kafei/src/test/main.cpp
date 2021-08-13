#include <iostream>

// All kafei includes come from here
#include <kafei.h>

#include <filesystem>

class TestWorld : public kafei::World {
  public:
    // TestWorld() : q({100.0f, 100.0f}, {100.0f, 100.0f}) {}
    TestWorld() : kgl() {}

    void init() override {
        // TODO Set default shader
        // auto& res = kafei::Res::get_instance();
        // q.set_shader(res->get("shaders/texture.vert"), res->get("shaders/texture.frag"));
        // q.set_texture("c++.png");

        // q.init();
        kgl.init();

        kgl.vertices.emplace_back(kafei::KglVertex::pos_vert(0.5f, -0.5f, 0.0f));
        kgl.vertices.emplace_back(kafei::KglVertex::pos_vert(0.0f, 0.5f, 0.0f));
        kgl.vertices.emplace_back(kafei::KglVertex::pos_vert(-0.5f, -0.5f, 0.0f));
    }

    void update() override {
        // q.render();
        kgl.update();
    }

  private:
    // kafei::Quad q;
    kafei::Kgl kgl;
};

class MyGame : public kafei::Game {
  public:
    MyGame(){};
};

// Engine Testing Code
int main(char argc, char** argv) {
    // This will need to be loaded into the resource manager.
    // That way we know where our config and resources are
    std::filesystem::path exePath = argv[0];

    kafei::Config game_cfg;
    game_cfg.set_window_title("Kafei");

    MyGame game;

    // These need to be done before start can be called
    game.load_config(game_cfg);
    game.set_default_world(new TestWorld());

    game.start();
}