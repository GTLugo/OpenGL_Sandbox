//
// Created by galex on 7/18/2020.
//

#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &m_rendererID);
    // set to current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    // set layout of currently bound vbo
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::Bind() const {
    // set to current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const {
    // set to current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
