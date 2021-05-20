#include <renderer.h>

using namespace jinx;

/**
 * Some basic shaders at the moment
 */

const char* VERT_SRC = "#version 400\n"
                       "layout (location = 0) in vec3 aPos;\n"
                       "void main() {"
                       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                       "}";

const char* FRAG_SRC = "#version 400\n"
                       "out vec4 frag_colour;\n"
                       "void main() {"
                       "   frag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n"
                       "}";

std::unique_ptr<Renderer> Renderer::_instance = nullptr;

std::unique_ptr<Renderer>& Renderer::GetInstance() {
    if (_instance == nullptr) {
        _instance.reset(new Renderer{});
    }

    return _instance;
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