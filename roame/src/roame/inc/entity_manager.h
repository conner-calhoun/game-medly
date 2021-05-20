#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "typedefs.h"
#include <iostream>

#include <map>
#include <memory>
#include <vector>

namespace roame {

class EntityManager {
  public:
    EntityManager(){};

    // EntityPtr get_entity(int id) { return entities.at(id); }

    const std::vector<Entity> get_entities_by_tag(const std::string& tag) {
        std::vector<Entity> entity_list;

        // TODO: populate entity list with entities that have the given tag

        return entity_list;
    }

    // Updates all entities in the list
    void update_all() {
        for (auto& it : entities) {
            it.second->update();
        }
    }

    void add_entity(EntityPtr ent) { entities.insert({0, ent}); }

    EntityHash& get_all() { return entities; }

  private:
    EntityHash entities;
    std::vector<int> entity_ids;
};

} // namespace roame

#endif // ENTITY_MANAGER_H