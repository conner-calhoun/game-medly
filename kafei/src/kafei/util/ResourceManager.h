#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <memory>

namespace kafei {

class Res {
  public:
    static std::unique_ptr<Res>& GetInstance();

    ~Res() = default;

    void SetResPath(const std::string resFolderPath) {
        resPath = resFolderPath;
    }

    const std::string Get(const std::string& relPath) {
        // TODO: Check if resPath + relPath exists
        return resPath + "/" + relPath;
    }

  private:
    Res() {}

    static std::unique_ptr<Res> instance;

    std::string resPath;
};

} // namespace kafei

#endif // RESOURCE_MANAGER_H