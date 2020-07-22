//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_MESH_H
#define OPENGL_SANDBOX_MESH_H

#include "Vector.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

// Used for marking mesh as 2-Dimensional or 3-Dimensional
enum class RenderDimensions {
    TWO = 2,
    THREE = 3
};

class Mesh {
public:
    Mesh();
//    Mesh(RenderDimensions dimensions, RenderMode mode, std::vector<float> vertices, std::vector<unsigned int> indices);
    Mesh(const std::vector<Vector2D> &vertices, const std::vector<unsigned int> &indices,
            const std::vector<Vector2D> &uvs, std::shared_ptr<Material> &material);
    Mesh(const std::vector<Vector3D> &vertices, const std::vector<unsigned int> &indices,
            const std::vector<Vector2D> &uvs, std::shared_ptr<Material> &material);

    ~Mesh();

    void SetMesh(const std::vector<Vector2D> &vertices, const std::vector<unsigned int> &indices, const std::vector<Vector2D> &uvs);
    void SetMesh(const std::vector<Vector3D> &vertices, const std::vector<unsigned int> &indices, const std::vector<Vector2D> &uvs);
    void SetVertices(const float *vertices, unsigned int floatsPerVertex, unsigned int vertCount);

    void SetIndices(const unsigned int *indices, unsigned int count);
    void SetRenderDimension(RenderDimensions dimensions) { m_renderDimensions = dimensions; }

    inline VertexArray* GetVertexArray() const { return m_vertexArray; }
    inline IndexBuffer* GetIndexBuffer() const { return m_indexBuffer; }
    inline std::shared_ptr<Material> GetMaterial() const { return m_material; }
private:
    RenderDimensions          m_renderDimensions;
    VertexArray              *m_vertexArray;
    VertexBuffer             *m_vertexBuffer;
    VertexBufferLayout       *m_vertexBufferLayout;
    IndexBuffer              *m_indexBuffer;
    std::shared_ptr<Material> m_material;
};


#endif //OPENGL_SANDBOX_MESH_H
