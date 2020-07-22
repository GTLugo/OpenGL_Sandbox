//
// Created by galex on 7/19/2020.
//

#ifndef OPENGL_SANDBOX_TEXTURE_H
#define OPENGL_SANDBOX_TEXTURE_H


#include <string>

class Texture {
public:
    explicit Texture(const std::string &filePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline std::string GetFilePath() const { return m_filePath; }
    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }
    inline int GetBytesPerPixel() const { return m_bytesPerPixel; }
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_bytesPerPixel;
};


#endif //OPENGL_SANDBOX_TEXTURE_H
