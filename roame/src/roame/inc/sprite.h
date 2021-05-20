#ifndef SPRITE_H
#define SPRITE_H

#include "string"

namespace roame {

class Sprite {
  public:
    Sprite() {}

    /**
     * Loads an image / sdl texture from the provided path
     */
    void load_image(const std::string& img_path) { this->img_path = img_path; }

  private:
    std::string img_path;
};

} // namespace roame

#endif // SPRITE_H