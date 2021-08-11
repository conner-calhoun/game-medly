// TODO: Determine if triangles are needed
class Tri {
  public:
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

        uint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

        // position attrib
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

  private:
    Vec2 left;
    Vec2 right;
    Vec2 top;

    std::vector<float> textCoords = {
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f  // top left
    };
};