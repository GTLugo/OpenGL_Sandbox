//
// Created by galex on 7/20/2020.
//

#include <iostream>
#include "glm/glm.hpp"
#include "Material.h"

Material::Material() {
    m_renderMode = RenderMode::COLORED;
    m_shader = nullptr;
    m_texture = nullptr;
    m_textureSlot = 0;
}

Material::Material(RenderMode mode, std::shared_ptr<Shader> &shader, const std::string &textureFilePath, unsigned int textureSlot) {
    m_renderMode = mode;
    SetShader(shader);
    if (!textureFilePath.empty()) {
        SetTexture2D(textureFilePath);
    }
    else {
        std::cerr << "WARNING | No texture path specified!" << std::endl;
        m_texture = nullptr;
    }
    m_textureSlot = textureSlot;
}

Material::~Material() {

}

void Material::SetShader(std::shared_ptr<Shader> &shader) {
    m_shader = shader;
}

void Material::SetUniform1i(const std::string &name, unsigned int v0) const {
    if (!m_shader) return;
    m_shader->Bind();
    m_shader->SetUniform1i(name, v0);
}

void Material::SetUniform1f(const std::string &name, float v0) const {
    if (!m_shader) return;
    m_shader->Bind();
    m_shader->SetUniform1f(name, v0);
}

void Material::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const {
    if (!m_shader) return;
    m_shader->Bind();
    m_shader->SetUniform4f(name, v0, v1, v2, v3);
}

void Material::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) const {
    if (!m_shader) return;
    m_shader->Bind();
    m_shader->SetUniformMat4f(name, matrix);
}

void Material::SetTexture2D(const std::string &filePath) {
    m_texture = std::make_shared<Texture>(filePath);
}
