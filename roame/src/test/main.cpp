#include <iostream>
#include <memory>

#include "SDL.h"
#include "config.h"
#include "entity_manager.h"
#include "game.h"
#include "typedefs.h"
#include "world.h"

#include "test_component.h"

using namespace std;

class TestingHall : public roame::World {
  public:
    TestingHall() {}
    void init() override {
        // Create the player, then add it to the world's entity manager
        player = make_shared<roame::Entity>();
        test_component = make_shared<TestComponent>();

        player->register_component(test_component);
        player->set_friendly_name("Player");

        add_entity(player);
    }

    void update() override {
        // must call super
        roame::World::update();

        std::cout << "X: " << test_component->get_pos().x
                  << " Y: " << test_component->get_pos().y << std::endl;
    }

  private:
    shared_ptr<roame::Entity> player;
    shared_ptr<TestComponent> test_component;
};

int main(int argc, char** argv) {
    roame::Config cfg{};

    cfg.win_title = "Roame";
    cfg.win_size = roame::WindowSize(640, 480);

    roame::Game game(cfg);

    // Set the active world
    game.set_world(new TestingHall());

    game.run();

    return 0;
}
