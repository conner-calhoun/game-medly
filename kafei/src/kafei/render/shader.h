#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <common.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace kafei {

class Shader {
  public:
    uint id;

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
            std::stringstream vert_stream, frag_stream;
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

    void use() {
        glUseProgram(id);
    }

    void set_bool(const std::string& name, bool val) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)val);
    }

    void set_int(const std::string& name, int val) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), val);
    }

    void set_float(const std::string& name, float val) const {
        glUniform1f(glGetUniformLocation(id, name.c_str()), val);
    }

  private:
    bool compile_shaders(const char* vert_code, const char* frag_code) {
        bool success = true;

        // compile vert shader
        uint vert_shader;
        vert_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert_shader, 1, &vert_code, NULL);
        glCompileShader(vert_shader);

        // check shader compilation
        success &= check_compilation(vert_shader);

        uint frag_shader;
        frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_code, NULL);
        glCompileShader(frag_shader);

        success &= check_compilation(frag_shader);

        id = glCreateProgram();

        glAttachShader(id, vert_shader);
        glAttachShader(id, frag_shader);
        glLinkProgram(id);

        success &= check_linking();

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

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

    bool check_linking() {
        int success;
        char info_log[512];

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::LINKING FAILED\n" << info_log << std::endl;
        }

        return success;
    }
};

} // namespace kafei

#endif // SHADER_H