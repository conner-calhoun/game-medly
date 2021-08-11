#ifndef WORLD_H
#define WORLD_H

#include <quad.h>

namespace kafei {

/**
 * Base class for worlds
 */
class World {
  public:
    World() : q({100.0f, 100.0f}, {100.0f, 100.0f}) {}

    void init() {
        // TODO Set default shader
        auto& res = Res::get_instance();
        q.set_shader(res->get("shaders/default.vert"), res->get("shaders/default.frag"));
        q.set_texture("c++.png");

        q.init();
    }

    void update() {
        q.render();
    }

  private:
    Quad q;
};

} // namespace kafei

#endif // WORLD_H