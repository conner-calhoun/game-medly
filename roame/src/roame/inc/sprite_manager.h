#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "component.h"
#include "sprite.h"
#include "typedefs.h"
#include <vector>

namespace roame {

class SpriteManager : public Component {
  public:
    SpriteManager() : active_sprite(nullptr) {}

    void update() {}

    void add(Sprite& spr) { sprite_list.emplace_back(spr); }

  private:
    SpritePtr active_sprite;
    std::vector<Sprite> sprite_list;
};

} // namespace roame

#endif // SPRITE_MANAGER_H