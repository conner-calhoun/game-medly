#ifndef KAFEI_H
#define KAFEI_H

#include "config.h"
#include "string"
#include "window.h"

/**
 * My idea for this is that the Kafei class is a builder that can build most things,
 * and is the entry point to the API.
 */

namespace kafei {

class Kafei {
   public:
    Kafei() : win(), cfg(){};

    void load(Config& cfg) {
        this->cfg = cfg;
    }

    void start() {
        load_config();
        win.Start();
    }

    Config build_config(const std::string& window_title) {
        Config cfg;
        cfg.set_window_title(window_title);
        return cfg;
    }

   private:
    void load_config() {
        win.SetTitle(cfg.get_title());
    }

    Window win;
    Config cfg;
};
}  // namespace kafei

#endif  // KAFEI_H