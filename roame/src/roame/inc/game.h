#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "config.h"
#include "controller.h"
#include "entity_manager.h"
#include "typedefs.h"
#include "world.h"

namespace roame {

struct SDLData {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

/**
 * Main class for the "JoyEngine"
 */
class Game {
  public:
    Game(Config& cfg);

    SDLData& get_sdl_info() { return sdl_data; }

    void run();

    void set_world(World* new_world) {
        active_world.reset(new_world);
        world_init = false;
    }

    void set_world(WorldPtr new_world) {
        active_world = new_world;
        world_init = false;
    };

    void init() {
        active_world->init();
        world_init = true;
    };

    void engine_update() {
        if (!world_init) {
            init();
            world_init = true;
        }
        active_world->update();
    };

  private:
    void init_sdl(const Config& cfg, SDLData& sdl_data);

    SDLData sdl_data;
    WorldPtr active_world;
    bool world_init;
    Controller ctrls;
};

extern Game* game_inst;
Game* get_game_instance();

} // namespace roame

#endif // GAME_H