#ifndef KAFEI_H
#define KAFEI_H

#include "config.h"
#include "game.h"
#include "string"

/**
 * My idea for this is that the Kafei class is a builder that can build most things,
 * and is the entry point to the API.
 */

namespace kafei {

class Kafei {
   public:
    Kafei() : game(), cfg(){};

    void load(Config& cfg) {
        this->cfg = cfg;
    }

    void start() {
        load_config();
        game.start();
    }

    Config build_config(const std::string& window_title) {
        Config cfg;
        cfg.set_window_title(window_title);
        return cfg;
    }

    World* build_world() {
        return new World();
    }

    void set_world(World* world) {
        game.set_world(world);
    }

   private:
    void load_config() {
        game.set_title(cfg.get_title());
    }

    Game game;
    Config cfg;
};
}  // namespace kafei

#endif  // KAFEI_H