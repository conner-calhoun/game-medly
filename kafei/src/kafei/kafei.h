#ifndef KAFEI_H
#define KAFEI_H

#include <config.h>
#include <game.h>

#include <iostream>

/**
 * TODO: Eliminate this class
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

  private:
    void load_config() {
        game.set_title(cfg.get_title());
    }

    Game game;
    Config cfg;
};
} // namespace kafei

#endif // KAFEI_H