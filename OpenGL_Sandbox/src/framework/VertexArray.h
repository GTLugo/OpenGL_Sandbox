//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_VERTEXARRAY_H
#define OPENGL_SANDBOX_VERTEXARRAY_H


#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
private:
    unsigned int m_rendererID;
};


#endif //OPENGL_SANDBOX_VERTEXARRAY_H
