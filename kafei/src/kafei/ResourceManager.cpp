#include <ResourceManager.h>

namespace kafei {

std::unique_ptr<ResourceManager> ResourceManager::instance = nullptr;

std::unique_ptr<ResourceManager>& ResourceManager::GetInstance() {
    if (instance == nullptr) {
        instance.reset(new ResourceManager{});
    }

    return instance;
}

} // namespace kafei