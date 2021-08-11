#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include <world.h>

#include <memory>

namespace kafei {

class WorldManager {
  public:
    WorldManager() : current_world(nullptr){};

    void set_default_world(World* world) {
        current_world.reset(world);
    }

    void set_world(World* world) {
        current_world.reset(world);
        current_world->init();
    };

    void init() {
        current_world->init();
    }

    void update() {
        current_world->update();
    }

  private:
    std::unique_ptr<World> current_world;
};

} // namespace kafei

#endif // WORLD_MANAGER_H