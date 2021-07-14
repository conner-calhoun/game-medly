#include <renderer.h>
#include <typedefs.h>

namespace kafei {

Tri::Tri(Vec2 left, Vec2 right, Vec2 top) : left(left), right(right), top(top) {}

std::vector<float> Tri::ToVertices() {
    // TODO: convert pixel coords to OpenGL coords
    return {
        left.x,  left.y,  0.0f,  // Left Point
        right.x, right.y, 0.0f,  // Right Point
        top.x,   top.y,   0.0f   // Top Point
    };
}

void Tri::Render() {
    std::vector<float> vertices = ToVertices();

    uint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Rect::Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {}

std::vector<float> Rect::ToVertices() {
    // TODO: convert pixel coords to OpenGL coords
    return {
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };
}

void Rect::Render() {
    // TODO: Move to init
    std::vector<float> vertices = ToVertices();

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
    // End init section

    // Render Loop
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::unique_ptr<Renderer> Renderer::_instance = nullptr;

std::unique_ptr<Renderer>& Renderer::GetInstance() {
    if (_instance == nullptr) {
        _instance.reset(new Renderer{});
    }

    return _instance;
}

std::pair<int, int> Renderer::GetWindowSize() {
    GLFWwindow* window = glfwGetCurrentContext();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return std::make_pair(width, height);
}

}  // namespace kafei