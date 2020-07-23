//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_RENDERER_H
#define OPENGL_SANDBOX_RENDERER_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vector.h"
#include "glm/glm.hpp"

class Renderer {
public:
    glm::mat4 *m_projectionMatrix;

    explicit Renderer(glm::mat4 &projectionMatrix);
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shader) const;
    void DrawMesh(const Mesh &mesh, glm::vec4 rgba = {0.0f,0.0f,0.0f,1.0f}) const;

    void SetBufferBit(float r, float g, float b, float a) const;
};

#endif //OPENGL_SANDBOX_RENDERER_H
