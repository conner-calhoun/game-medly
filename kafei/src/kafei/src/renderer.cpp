#include <Renderer.h>

namespace kafei {

/// Basic Shaders
const char* VERT_SRC =
    "#version 400\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";

const char* FRAG_SRC =
    "#version 400\n"
    "out vec4 frag_colour;\n"
    "void main() {"
    "   frag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n"
    "}";

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
    unsigned int VAO;
    glGenBuffers(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

    // Element buffer object
    unsigned int EBO;
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

bool Renderer::SetupShaders() {
    bool success = true;

    // compile vert shader
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &VERT_SRC, NULL);
    glCompileShader(vertex_shader);

    // check shader compilation
    success &= CheckShaderCompilation(vertex_shader);

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &FRAG_SRC, NULL);
    glCompileShader(fragment_shader);

    success &= CheckShaderCompilation(fragment_shader);

    unsigned int shader_program;
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    success &= CheckShaderLinking(shader_program);
    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return success;
}

bool Renderer::CheckShaderCompilation(unsigned int shader) {
    int success;
    char info_log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    return success;
}

bool Renderer::CheckShaderLinking(unsigned int shaderProgram) {
    int success;
    char info_log[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
    }

    return success;
}

}  // namespace kafei