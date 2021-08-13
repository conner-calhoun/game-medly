#ifndef KAFGL_H
#define KAFGL_H

#include <common.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

namespace kafei {

struct KglVertex {
    glm::vec2 tex;
    glm::vec3 color;
    glm::vec3 pos;
};

struct Kgl {
    Kgl() : vertices(), VAO() {}

    void init() {
        glGenBuffers(1, &VAO);
        glBindVertexArray(VAO);
    }

    void update() {
        uint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(KglVertex), &(vertices[0].pos.x), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(KglVertex), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    std::vector<KglVertex> vertices;
    // std::vector<glm::vec3> vertices;
    uint VAO;

    uint indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
};

} // namespace kafei

#endif // KAFGL_H