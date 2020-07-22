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

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shader) const;
    void DrawMesh(const Mesh &mesh, Vector4D rgba = {0.0f,0.0f,0.0f,1.0f}) const;

    void SetBufferBit(float r, float g, float b, float a) const;
};

#endif //OPENGL_SANDBOX_RENDERER_H
