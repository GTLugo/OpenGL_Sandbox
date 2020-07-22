//
// Created by galex on 7/18/2020.
//

#ifndef OPENGL_SANDBOX_SHADER_H
#define OPENGL_SANDBOX_SHADER_H

#include <string>
#include <unordered_map>

struct ShaderProgram {
    std::string VertexProgram;
    std::string FragmentProgram;
};

class Shader {
public:
    explicit Shader(std::string filePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void SetUniform1i(const std::string &name, unsigned int v0);
    void SetUniform1f(const std::string &name, float v0);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    inline std::string GetFilePath() const { return m_filePath; }
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    std::unordered_map<std::string, int> m_uniformLocationCache;

    int GetUniformLocation(const std::string &name);
    ShaderProgram ParseShaderFile();
    static unsigned int CompileShader(unsigned int type, const std::string &shader);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
};


#endif //OPENGL_SANDBOX_SHADER_H
