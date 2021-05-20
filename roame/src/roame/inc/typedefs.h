#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <map>
#include <memory>

namespace roame {

// Forward Defs
class Game;
class World;
class Entity;
class Sprite;

typedef std::unique_ptr<Game> GamePtr;
typedef std::unique_ptr<Sprite> SpritePtr;

typedef std::shared_ptr<World> WorldPtr;
typedef std::shared_ptr<Entity> EntityPtr;

typedef std::map<int, EntityPtr> EntityHash;

} // namespace roame

#endif // TYPEDEFS_H