#ifndef KAFEI_H
#define KAFEI_H

#include "Window.h"
#include "string"

namespace kafei {

class Config {
   public:
    Config() {}
    void SetWindowTitle(std::string title) { _mainTitle = title; }
    std::string GetTitle() { return _mainTitle; }

   private:
    std::string _mainTitle;
};

class Kafei {
   public:
    Kafei(Config& cfg) {
        // create a window
        Window win{};
        win.SetTitle(cfg.GetTitle());
        win.Start();
    };
};
}  // namespace kafei

#endif  // KAFEI_H