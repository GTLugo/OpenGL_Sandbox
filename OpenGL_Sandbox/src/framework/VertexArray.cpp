//
// Created by galex on 7/18/2020.
//

#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout) {
    Bind();
    vertexBuffer.Bind();
    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i) {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        // bind currently bound vbo to index i of currently bound vao
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
        offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
}
