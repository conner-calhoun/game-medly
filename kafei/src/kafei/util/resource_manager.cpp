#include <resource_manager.h>

namespace kafei {

std::unique_ptr<Res> Res::instance = nullptr;

std::unique_ptr<Res>& Res::get_instance() {
    if (instance == nullptr) {
        instance.reset(new Res{});
    }

    return instance;
}

} // namespace kafei