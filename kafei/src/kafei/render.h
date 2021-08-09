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
    Texture(const std::string& texPath) {
        auto fullPath = Res::GetInstance()->Get(texPath);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    uint texture;
};

struct Tri {
    Vec2 left;
    Vec2 right;
    Vec2 top;

    Tri() {}

    Tri(Vec2 left, Vec2 right, Vec2 top) : left(left), right(right), top(top) {}

    std::vector<float> to_vertices() {
        // TODO: convert pixel coords to OpenGL coords
        return {
            left.x,  left.y,  0.0f, // Left Point
            right.x, right.y, 0.0f, // Right Point
            top.x,   top.y,   0.0f  // Top Point
        };
    }

    std::vector<float> GetTexCoords() {
        return {
            // texture coords
            1.0f, 1.0f, // top right
            1.0f, 0.0f, // bottom right
            0.0f, 0.0f, // bottom left
            0.0f, 1.0f  // top left
        };
    }

    void render() {
        std::vector<float> vertices = to_vertices();
        std::vector<float> texCoords = GetTexCoords();

        uint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

        // position attrib
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        // draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

struct Rect {
    Vec2 pos, size;
    unsigned int indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

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

    std::vector<float> GetTexCoords() {
        return {
            // texture coords
            1.0f, 1.0f, // top right
            1.0f, 0.0f, // bottom right
            0.0f, 0.0f, // bottom left
            0.0f, 1.0f  // top left
        };
    }

    void SetShader(const std::string& vPath, const std::string& fPath) {
        shader.reset(new Shader(vPath, fPath));
    }

    void SetTexture(const std::string texPath) {
        texture.reset(new Texture{texPath});
    }

    void render() {
        shader->use();
        shader->set_int("texture", texture->texture);

        // TODO: Move to init
        auto vertices = to_vertices();
        auto texVerts = GetTexCoords();

        // Vertex array object
        uint VAO;
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
        uint TVBO;
        glGenBuffers(1, &TVBO);
        glBindBuffer(GL_ARRAY_BUFFER, TVBO);
        glBufferData(GL_ARRAY_BUFFER, texVerts.size() * sizeof(float), &texVerts.front(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
        // End texture stuff

        // End init section

        // Render Loop
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    std::unique_ptr<Texture> texture;
    std::unique_ptr<Shader> shader;
};

} // namespace kafei

#endif // KAFEI_RENDERER_H