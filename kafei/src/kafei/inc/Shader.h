#ifndef SHADER_H
#define SHADER_H

#include <Typedefs.h>
#include <glad/glad.h>

#include <string>

namespace kafei {

class Shader {
    uint ID;
    Shader(const std::string& vertPath, const std::string& fragPath);

    void Use();
    void SetBool(const std::string& name, bool val) const;
    void SetInt(const std::string& name, int val) const;
    void SetFloat(const std::string& name, float val) const;
};

}  // namespace kafei

#endif  // SHADER_H