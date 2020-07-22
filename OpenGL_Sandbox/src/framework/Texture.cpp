//
// Created by galex on 7/19/2020.
//

#include "Texture.h"

#include <GL/glew.h>

#include "stb_image/stb_image.h"

Texture::Texture(const std::string &filePath)
    : m_rendererID(0), m_filePath(filePath), m_localBuffer(nullptr), m_width(0), m_height(0), m_bytesPerPixel(0) {

    // png starts at top-left, not bottom-left
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bytesPerPixel, 4);

    glGenTextures(1, &m_rendererID);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Stretch wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Tiling wrap

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0); // unbind
}

Texture::~Texture() {
    if (m_localBuffer) {
        stbi_image_free(m_localBuffer);
    }

    glDeleteTextures(1, &m_rendererID);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
