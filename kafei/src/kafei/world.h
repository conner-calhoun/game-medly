#ifndef WORLD_H
#define WORLD_H

#include <quad.h>

namespace kafei {

/**
 * Base class for worlds
 */
class World {
  public:
    World() {}

    virtual void init() {
        std::cout << "Base World Init" << std::endl;
    }

    virtual void update() {
        std::cout << "Base World Update" << std::endl;
    }

  private:
};

} // namespace kafei

#endif // WORLD_H