#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <memory>

namespace kafei {

class ResourceManager {
  public:
    static std::unique_ptr<ResourceManager>& GetInstance();

    ~ResourceManager() = default;

    void SetResPath(const std::string resFolderPath) {
        resPath = resFolderPath;
    }

    const std::string Get(const std::string& relPath) {
        // TODO: Check if resPath + relPath exists
        return resPath + "/" + relPath;
    }

  private:
    ResourceManager() {}

    static std::unique_ptr<ResourceManager> instance;

    std::string resPath;
};

} // namespace kafei

#endif // RESOURCE_MANAGER_H