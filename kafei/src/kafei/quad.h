#ifndef QUAD_H
#define QUAD_H

#include <memory>

#include <Common.h>
#include <Texture.h>
#include <shader.h>

namespace kafei {

class Quad {
  public:
    Quad(Vec2 pos, Vec2 size) : pos(pos), size(size) {}

    std::vector<float> to_vertices() {
        // TODO: convert pixel coords to OpenGL coords
        return {
            0.5f,  0.5f,  0.0f, // top right
            0.5f,  -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f,  0.0f  // top left
        };
    }

    void set_shader(const std::string& v_path, const std::string& f_path) {
        shader.reset(new Shader(v_path, f_path));
    }

    void set_texture(const std::string tex_path) {
        texture.reset(new Texture{tex_path});
    }

    void init() {
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
            glBufferData(GL_ARRAY_BUFFER, text_coords.size() * sizeof(float), &text_coords.front(), GL_STATIC_DRAW);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(2);
        }
    }

    void render() {
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

    std::vector<float> text_coords = {
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

#endif // QUAD_H