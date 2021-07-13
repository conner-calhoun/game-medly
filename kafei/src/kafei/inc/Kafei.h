#ifndef KAFEI_H
#define KAFEI_H

#include "Config.h"
#include "Window.h"
#include "string"

/**
 * My idea for this is that the Kafei class is a builder that can build most things,
 * and is the entry point to the API.
 */

namespace kafei {

class Kafei {
   public:
    Kafei() : _win(), _cfg(){};

    void Load(Config& cfg) {
        _cfg = cfg;
    }

    void Start() {
        LoadConfig();
        _win.Start();
    }

    Config BuildConfig(const std::string& windowTitle) {
        Config cfg;
        cfg.SetWindowTitle(windowTitle);
        return cfg;
    }

   private:
    void LoadConfig() {
        _win.SetTitle(_cfg.GetTitle());
    }

    Window _win;
    Config _cfg;
};
}  // namespace kafei

#endif  // KAFEI_H