//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_VERTEXBUFFER_H
#define OPENGL_SANDBOX_VERTEXBUFFER_H


class VertexBuffer {
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_rendererID;
};


#endif //OPENGL_SANDBOX_VERTEXBUFFER_H
