#ifndef KAFEI_RENDERER_H
#define KAFEI_RENDERER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <shader.h>
#include <typedefs.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

/**
 * OpenGL Rendering code will go here
 * right now this code is in window.h
 */

namespace kafei {

struct Vec2 {
    float x, y;
};

class Texture {
  public:
    /**
     * NOTE: texPath will be relative to the resources folder
     */
    Texture(const std::string& texPath) : path(Res::GetInstance()->Get(texPath)) {}

    void Load() {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        uchar* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    uint GetTexture() {
        return texture;
    }

  private:
    uint texture;
    std::string path;
};

class Rect {
  public:
    Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {}

    std::vector<float> to_vertices() {
        // TODO: convert pixel coords to OpenGL coords
        return {
            0.5f,  0.5f,  0.0f, // top right
            0.5f,  -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f,  0.0f  // top left
        };
    }

    void SetShader(const std::string& vPath, const std::string& fPath) {
        shader.reset(new Shader(vPath, fPath));
    }

    void SetTexture(const std::string texPath) {
        texture.reset(new Texture{texPath});
    }

    void Init() {
        // TODO: Move to init
        auto vertices = to_vertices();

        // Vertex array object
        glGenBuffers(1, &VAO);
        glBindVertexArray(VAO);

        // Vertex buffer object
        uint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

        // Element buffer object
        uint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Interpret vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Texture Stuff
        if (texture) {
            texture->Load();

            uint TVBO;
            glGenBuffers(1, &TVBO);
            glBindBuffer(GL_ARRAY_BUFFER, TVBO);
            glBufferData(GL_ARRAY_BUFFER, textCoords.size() * sizeof(float), &textCoords.front(), GL_STATIC_DRAW);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(2);
        }
    }

    void Render() {
        if (shader) {
            shader->use();
            shader->set_int("texture", texture->GetTexture());
        }

        // Render Loop
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

  private:
    uint indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    std::vector<float> textCoords = {
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f  // top left
    };

    uint VAO;
    Vec2 pos, size;
    std::unique_ptr<Texture> texture;
    std::unique_ptr<Shader> shader;
};

} // namespace kafei

#endif // KAFEI_RENDERER_H