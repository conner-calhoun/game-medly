#include <renderer.h>

using namespace jinx;

/// Shader stuff
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

Triangle::Triangle(Point left, Point right, Point top) {
    this->left = left;
    this->right = right;
    this->top = top;
}

std::vector<float> Triangle::ToVertices() {
    // TODO: Do some math to convert the pixel coords to the OpenGL Vertices
    return {left.x, left.y, 0.0f, right.x, right.y, 0.0f, top.x, top.y, 0.0f};
}

Rect::Rect(float x, float y, float w, float h)
    : l{{x, y}, {x + w, y}, {x, y + h}}, r{{x + w, y}, {x + w, y + h}, {x, y + h}} {}

void Rect::Render() {
    Renderer::GetInstance()->SetupVAO();
    Renderer::GetInstance()->RenderTriangle(l);
    Renderer::GetInstance()->RenderTriangle(r);
}

std::unique_ptr<Renderer> Renderer::_instance = nullptr;

std::unique_ptr<Renderer>& Renderer::GetInstance() {
    if (_instance == nullptr) {
        _instance.reset(new Renderer{});
    }

    return _instance;
}

void Renderer::RenderTriangle(Triangle& t) {
    // get vertices from triangle
    std::vector<float> vertices = t.ToVertices();

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::pair<int, int> Renderer::GetWindowSize() {
    GLFWwindow* window = glfwGetCurrentContext();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return std::make_pair(width, height);
}

void Renderer::SetupVAO() {
    unsigned int VAO;
    glGenBuffers(1, &VAO);
    glBindVertexArray(VAO);
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