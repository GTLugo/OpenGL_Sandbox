//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_VERTEXBUFFERLAYOUT_H
#define OPENGL_SANDBOX_VERTEXBUFFERLAYOUT_H

#include <GL/glew.h>

#include <vector>
#include <iostream>

struct VertexBufferLayoutElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:         return 4;
            case GL_UNSIGNED_INT:  return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        std::cerr << "ERROR | Type not supported for VertexBufferLayoutElement (GetSizeOfType)!" << std::endl;
        return 0;
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout();

    template<typename T>
    void Push(unsigned int count) {
        std::cerr << "ERROR | Failed to push to vertex buffer. Type not supported!" << std::endl;
        //static_assert(false);
    }

    template<>
    void Push<float>(unsigned int count) {
        m_elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count) {
        m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count) {
        m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferLayoutElement> GetElements() const& { return m_elements; }
    inline unsigned int GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferLayoutElement> m_elements;
    unsigned int m_stride;
};


#endif //OPENGL_SANDBOX_VERTEXBUFFERLAYOUT_H
