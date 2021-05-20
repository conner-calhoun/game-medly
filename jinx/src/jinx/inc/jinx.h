#ifndef JINX_H
#define JINX_H

#include "string"
#include "window.h"

namespace jinx {

class Config {
  public:
    Config() {}
    void SetTitle(std::string title) { _mainTitle = title; }
    std::string GetTitle() { return _mainTitle; }

  private:
    std::string _mainTitle;
};

class Jinx {
  public:
    Jinx(Config& cfg) {
        // create a window
        Window win{};
        win.SetTitle(cfg.GetTitle());
        win.Start();
    };
};
} // namespace jinx

#endif // JINX_H