//
// Created by galex on 7/18/2020.
//

#include "Mesh.h"
#include "Material.h"
#include "Vector.h"

#include <array>
#include <vector>

Mesh::Mesh() {
    m_renderDimensions = RenderDimensions::TWO;
    m_vertexArray = new VertexArray();
    m_material = nullptr;
}

//Mesh::Mesh(RenderDimensions dimensions, RenderMode mode, std::vector<float> vertices, std::vector<unsigned int> indices) {
//    m_renderDimensions = dimensions;
//    m_renderMode = mode;
//    SetMesh(vertices.data(), vertices.size(), indices.data(), indices.size());
//    m_material = nullptr;
//}

Mesh::Mesh(const std::vector<glm::vec2> &vertices, const std::vector<unsigned int> &indices,
        const std::vector<glm::vec2> &uvs, std::shared_ptr<Material> &material) {
    m_renderDimensions = RenderDimensions::TWO;
    m_material = material;
    SetMesh(vertices, indices, uvs);
}

Mesh::Mesh(const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices,
        const std::vector<glm::vec2> &uvs, std::shared_ptr<Material> &material) {
    m_renderDimensions = RenderDimensions::THREE;
    m_material = material;
    SetMesh(vertices, indices, uvs);
}

Mesh::~Mesh() {
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_vertexBufferLayout;
    delete m_indexBuffer;
}

void Mesh::SetMesh(const std::vector<glm::vec2> &vertices, const std::vector<unsigned int> &indices, const std::vector<glm::vec2> &uvs) {
    bool textured = m_material->GetRenderMode() == RenderMode::TEXTURED;
    m_vertexArray = new VertexArray();
    std::vector<float> rawVerts;
    for (int i = 0; i < vertices.size(); ++i) {
        rawVerts.push_back(vertices[i].x);
        rawVerts.push_back(vertices[i].y);
        if (textured) {
            rawVerts.push_back(uvs[i].s);
            rawVerts.push_back(uvs[i].t);
        }
    }
    SetVertices(rawVerts.data(), 2, vertices.size());
    SetIndices(indices.data(), indices.size());
}

void Mesh::SetMesh(const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices, const std::vector<glm::vec2> &uvs) {
    bool textured = m_material->GetRenderMode() == RenderMode::TEXTURED;
    m_vertexArray = new VertexArray();
    std::vector<float> a;
    std::vector<float> b;
    std::vector<float> rawVerts;
    for (int i = 0; i < vertices.size(); ++i) {
        rawVerts.push_back(vertices[i].x);
        rawVerts.push_back(vertices[i].y);
        rawVerts.push_back(vertices[i].z);
        if (textured) {
            rawVerts.push_back(uvs[i].s);
            rawVerts.push_back(uvs[i].t);
        }
    }
    SetVertices(rawVerts.data(), 3, vertices.size());
    SetIndices(indices.data(), indices.size());
}

void Mesh::SetVertices(const float *vertices, unsigned int floatsPerVertex, unsigned int vertCount) {
    bool textured = m_material->GetRenderMode() == RenderMode::TEXTURED;
    //int texturedMod = (textured ? 2 : 1);
    m_vertexBuffer = new VertexBuffer(vertices, (floatsPerVertex * (vertCount/* / texturedMod*/)
                                                + ((textured ? 2 : 0) * (vertCount/* / texturedMod*/))) // add in the number of uv coordinates
                                                * sizeof(float));
    m_vertexBufferLayout = new VertexBufferLayout();
    m_vertexBufferLayout->Push<float>(floatsPerVertex);
    if (textured) m_vertexBufferLayout->Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, *m_vertexBufferLayout);
}

void Mesh::SetIndices(const unsigned int *indices, unsigned int count) {
    m_indexBuffer = new IndexBuffer(indices, count);
}
