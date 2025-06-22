#pragma once

#include "Volante.h"
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

namespace Volante {

class Shader {
public:
    unsigned int id;

    Shader(const char* vertexSource, const char* fragmentSource) {
        const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        const unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        checkCompileErrors(id, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~Shader() {
        glDeleteProgram(id);
    }

    void use() const {
        glUseProgram(id);
    }

    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
    }

    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void setVec3(const std::string& name, const Vec3& value) const {
        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string& name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
    }

    void setMat4(const std::string& name, const Mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

private:
    static void checkCompileErrors(unsigned int shader, const std::string& type) {
        int success;
        char info[1024];
        if (type == "PROGRAM") {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, info);
                std::cerr << "ERROR::SHADER::" << type << "::LINKING_FAILED: " << info << std::endl;
            }
        } else {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, info);
                std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED: " << info << std::endl;
            }
        }
    }
};

}