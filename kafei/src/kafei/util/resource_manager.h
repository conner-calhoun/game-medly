#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <filesystem>
#include <iostream>
#include <memory>

namespace kafei {

class Res {
  public:
    static std::unique_ptr<Res>& get_instance();

    ~Res() = default;

    void set_res_path(const std::string res_folder) {
        res_path = res_folder;
    }

    const std::string get(const std::string& rel_path) {
        // TODO: Check if resPath + relPath exists
        std::filesystem::path p = res_path + "/" + rel_path;

        return res_path + "/" + rel_path;
    }

  private:
    Res() {}

    static std::unique_ptr<Res> instance;

    std::string res_path;
};

} // namespace kafei

#endif // RESOURCE_MANAGER_H