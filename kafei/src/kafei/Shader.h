#ifndef SHADER_H
#define SHADER_H

#include <Typedefs.h>
#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace kafei {

class Shader {
   public:
    uint ID;
    Shader(const std::string& vertPath, const std::string& fragPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertPath.c_str());
            fShaderFile.open(fragPath.c_str());
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure e) {
            // TODO: Replace with logger
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        CompileShaders(vertexCode.c_str(), fragmentCode.c_str());
    }

    void Use() {}

    void SetBool(const std::string& name, bool val) const {}

    void SetInt(const std::string& name, int val) const {}

    void SetFloat(const std::string& name, float val) const {}

   private:
    bool CompileShaders(const char* vertCode, const char* fragCode) {
        bool success = true;

        // compile vert shader
        uint vertex_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertCode, NULL);
        glCompileShader(vertex_shader);

        // check shader compilation
        success &= CheckShaderCompilation(vertex_shader);

        uint fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragCode, NULL);
        glCompileShader(fragment_shader);

        success &= CheckShaderCompilation(fragment_shader);

        uint shader_program;
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

    bool CheckShaderCompilation(unsigned int shader) {
        int success;
        char infoLog[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return success;
    }

    bool CheckShaderLinking(unsigned int shaderProgram) {
        int success;
        char infoLog[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        }

        return success;
    }
};

}  // namespace kafei

#endif  // SHADER_H