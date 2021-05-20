#include "component.h"

struct Vector2 {
    float x;
    float y;
};

class TestComponent : public roame::Component {
  public:
    TestComponent() : position{0.0, 0.0} {}

    void update() override {
        position.x += 0.1f;
        position.y += 0.1f;
    }

    Vector2 get_pos() { return position; }

  private:
    Vector2 position;
};