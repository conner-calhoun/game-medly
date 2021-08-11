#ifndef TEXTURE_H
#define TEXTURE_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <common.h>
#include <glad/glad.h>
#include <resource_manager.h>
#include <shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

namespace kafei {

class Texture {
  public:
    /**
     * NOTE: texPath will be relative to the resources folder
     */
    Texture(const std::string& text_path) : path(Res::get_instance()->get(text_path)) {}

    void load() {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nr_chans;
        stbi_set_flip_vertically_on_load(true);
        uchar* data = stbi_load(path.c_str(), &width, &height, &nr_chans, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    uint get_texture() {
        return texture;
    }

  private:
    uint texture;
    std::string path;
};

} // namespace kafei

#endif // TEXTURE_H