//
// Created by galex on 7/20/2020.
//

#ifndef OPENGL_SANDBOX_MATERIAL_H
#define OPENGL_SANDBOX_MATERIAL_H


#include "Shader.h"
#include "Texture.h"

// Used for marking mesh as Textured or Colored
enum class RenderMode {
    COLORED = 0,
    TEXTURED = 1
};

class Material {
public:
    Material();
    Material(RenderMode mode, std::shared_ptr<Shader> &shader, const std::string &textureFilePath = "", unsigned int textureSlot = 0);
    ~Material();

    void SetShader(std::shared_ptr<Shader> &shader);
    void SetUniform1i(const std::string &name, unsigned int v0) const;
    void SetUniform1f(const std::string &name, float v0) const;
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const;
    void SetTexture2D(const std::string &filePath);

    void SetRenderMode(RenderMode mode) { m_renderMode = mode; }

    inline std::shared_ptr<Shader>  GetShader()      const { return m_shader; }
    inline std::shared_ptr<Texture> GetTexture2D()   const { return m_texture; }
    inline unsigned int             GetTextureSlot() const { return m_textureSlot; }
    inline RenderMode               GetRenderMode()  const { return m_renderMode; }

private:
    RenderMode               m_renderMode;
    std::shared_ptr<Shader>  m_shader;
    std::shared_ptr<Texture> m_texture;
    unsigned int             m_textureSlot;
};


#endif //OPENGL_SANDBOX_MATERIAL_H
