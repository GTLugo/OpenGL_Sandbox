//
// Created by galex on 7/18/2020.
//

#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include "glm/glm.hpp"

Shader::Shader(std::string filePath)
    : m_rendererID(0), m_filePath(std::move(filePath)){
    ShaderProgram shaderProgram = ParseShaderFile();
    m_rendererID = CreateShader(shaderProgram.VertexProgram, shaderProgram.FragmentProgram);
}

Shader::~Shader() {
    glDeleteProgram(m_rendererID);
}

ShaderProgram Shader::ParseShaderFile() {
    std::ifstream stream(m_filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::stringstream shaderStream[2];
    std::string currentLine;
    ShaderType type = ShaderType::NONE;
    while (getline(stream, currentLine)) {
        if (currentLine.find("#shader") != std::string::npos) {
            if (currentLine.find("vertex") != std::string::npos) {
                // set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (currentLine.find("fragment") != std::string::npos) {
                // set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            shaderStream[(int)type] << currentLine << "\n";
        }
    }

    return { shaderStream[0].str(), shaderStream[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &shader) {
    unsigned int id = glCreateShader(type);
    const char* src = shader.c_str();
    // giving nullptr as length means that string is null-terminated
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "ERROR | Failed to compile "
                  << (type == GL_VERTEX_SHADER
                      ? "vertex"
                      : "fragment")
                  << " shader!" << std::endl;
        std::cerr << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShaderID);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return program;
}

void Shader::Bind() const {
    glUseProgram(m_rendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string &name, unsigned int v0) {
    glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform1f(const std::string &name, float v0) {
    glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_uniformLocationCache.contains(name)) {
        return m_uniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1)
        std::cerr << "WARNING | Uniform " << name << " does not exist!" << std::endl;
    m_uniformLocationCache[name] = location;
    return location;
}
