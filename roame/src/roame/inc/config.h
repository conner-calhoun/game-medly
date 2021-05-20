#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

#include "typedefs.h"

namespace roame {

typedef std::string WindowTitle;

struct WindowSize {
    WindowSize() {}

    WindowSize(uint16_t width, uint16_t height)
        : width(width), height(height) {}

    uint16_t width;
    uint16_t height;
};

struct Config {
    WindowTitle win_title;
    WindowSize win_size;
};

} // namespace roame

#endif // CONFIG_H