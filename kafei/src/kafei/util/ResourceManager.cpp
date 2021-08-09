#include <ResourceManager.h>

namespace kafei {

std::unique_ptr<Res> Res::instance = nullptr;

std::unique_ptr<Res>& Res::GetInstance() {
    if (instance == nullptr) {
        instance.reset(new Res{});
    }

    return instance;
}

} // namespace kafei