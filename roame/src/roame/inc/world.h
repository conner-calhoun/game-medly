#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "entity_manager.h"

namespace roame {

class World {
  public:
    World() : em{} {}
    ~World() {}

    // Optionally override these
    virtual void init() {}
    virtual void update() { em.update_all(); }

    void add_entity(EntityPtr e) { em.add_entity(e); }

  private:
    EntityManager em;
};

} // namespace roame

#endif // WORLD_H