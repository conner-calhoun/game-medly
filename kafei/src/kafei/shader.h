#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <typedefs.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace kafei {

class Shader {
   public:
    uint ID;
    Shader(const std::string& vert_path, const std::string& frag_path) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vert_code;
        std::string frag_code;
        std::ifstream vert_file;
        std::ifstream frag_file;
        // ensure ifstream objects can throw exceptions:
        vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vert_file.open(vert_path.c_str());
            frag_file.open(frag_path.c_str());
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vert_stream << vert_file.rdbuf();
            frag_stream << frag_file.rdbuf();
            // close file handlers
            vert_file.close();
            frag_file.close();
            // convert stream into string
            vert_code = vert_stream.str();
            frag_code = frag_stream.str();
        } catch (std::ifstream::failure e) {
            // TODO: Replace with logger
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        compile_shaders(vert_code.c_str(), frag_code.c_str());
    }

    void use() {}

    void set_bool(const std::string& name, bool val) const {}

    void set_int(const std::string& name, int val) const {}

    void set_float(const std::string& name, float val) const {}

   private:
    bool compile_shaders(const char* vert_code, const char* frag_code) {
        bool success = true;

        // compile vert shader
        uint vertex_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vert_code, NULL);
        glCompileShader(vertex_shader);

        // check shader compilation
        success &= check_compilation(vertex_shader);

        uint fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &frag_code, NULL);
        glCompileShader(fragment_shader);

        success &= check_compilation(fragment_shader);

        uint shader_program;
        shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        success &= check_linking(shader_program);
        glUseProgram(shader_program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return success;
    }

    bool check_compilation(uint shader) {
        int success;
        char info_log[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
        }

        return success;
    }

    bool check_linking(uint shader_program) {
        int success;
        char info_log[512];

        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        }

        return success;
    }
};

}  // namespace kafei

#endif  // SHADER_H