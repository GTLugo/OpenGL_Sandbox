//
// Created by galex on 7/18/2020.
//
#include <GL/glew.h>

#include <iostream>

#include "Renderer.h"
#include "Mesh.h"
#include "Vector.h"

Renderer::Renderer(glm::mat4 &projectionMatrix) {
    m_projectionMatrix = &projectionMatrix;
    // std::cout << m_projectionMatrix << std::endl;
}

Renderer::~Renderer() {

}

void Renderer::Draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shader) const {
    shader.Bind();
    vertexArray.Bind();
    indexBuffer.Bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawMesh(const Mesh &mesh, glm::vec4 rgba) const {
    auto material = mesh.GetMaterial();
    if (material) {
        material->GetShader()->Bind();
    }
    mesh.GetVertexArray()->Bind();
    mesh.GetIndexBuffer()->Bind();
    if (material) {
        material->SetUniformMat4f("u_MVP", *m_projectionMatrix);
        switch (material->GetRenderMode()) {
            case RenderMode::TEXTURED:
                material->GetTexture2D()->Bind(material->GetTextureSlot());
                material->SetUniform1i("u_Texture", material->GetTextureSlot());
                break;
            case RenderMode::COLORED:
                material->SetUniform4f("u_Color", rgba.r, rgba.g, rgba.b, rgba.a);
                break;
        }
    }
    glDrawElements(GL_TRIANGLES, mesh.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

//void Renderer::DrawColoredMesh(const Mesh &mesh, const std::string &name, float v0, float v1, float v2, float v3) const {
//    mesh.GetShader()->Bind();
//    mesh.GetVertexArray()->Bind();
//    mesh.GetIndexBuffer()->Bind();
//    mesh.SetUniform4f(name, v0, v1, v2, v3);
//    glDrawElements(GL_TRIANGLES, mesh.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
//}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetBufferBit(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}
