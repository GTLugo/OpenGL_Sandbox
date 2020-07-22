//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_INDEXBUFFER_H
#define OPENGL_SANDBOX_INDEXBUFFER_H


class IndexBuffer {
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_count; }
private:
    unsigned int m_rendererID;
    unsigned int m_count;
};


#endif //OPENGL_SANDBOX_INDEXBUFFER_H
