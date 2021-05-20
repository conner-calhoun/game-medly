#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include "component.h"
#include "object.h"

namespace roame {

class Entity : Object {
  public:
    Entity() {}

    virtual void init() {}

    virtual void update() {
        for (auto& component : component_list) {
            component->update();
        }
    }

    void register_component(std::shared_ptr<Component> new_comp) {
        component_list.emplace_back(new_comp);
    }

    void add_tag(const std::string& tag) { tags.emplace_back(tag); }

    void set_friendly_name(const std::string& fn) { friendly_name = fn; }
    const std::string& get_friendly_name() { return friendly_name; };

  private:
    std::vector<std::shared_ptr<Component>> component_list;
    std::vector<std::string> tags;
    std::string friendly_name;
};

} // namespace roame

#endif // ENTITY_H