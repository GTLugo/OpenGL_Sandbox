//
// Created by galex on 7/21/2020.
//

#ifndef OPENGL_SANDBOX_APPWINDOW_H
#define OPENGL_SANDBOX_APPWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"

class AppWindow {
//    struct DestroyglfwWin {
//
//        void operator()(GLFWwindow* ptr){
//            glfwDestroyWindow(ptr);
//        }
//
//    };
public:
    bool successfulInit;

    AppWindow(const std::string &windowName, unsigned int width, unsigned int height,
              bool vsync = true, bool fullscreen = false);
    ~AppWindow();

    // Lifetime methods
    int WindowInit(const std::string &windowName, unsigned int width, unsigned int height, bool vsync, bool fullscreen);
    void GameLoop();

    // Generic methods
    inline const bool ShouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }
    inline const void SwapBuffers() const { glfwSwapBuffers(m_glfwWindow); }
    inline const void PollEvents() const { glfwPollEvents(); }
    void Resize(int cx, int cy);

    // Getters
    inline const GLFWwindow *GetglfwWindow() const { return m_glfwWindow; }
    inline const bool IsFullscreen() const { return glfwGetWindowMonitor(m_glfwWindow) != nullptr; }
    inline const bool IsCursorLocked() const { return m_cursorLocked; }

    // Setters
    void SetFullScreen(bool fullscreen);
    void SetCursorLocked(bool cursorLocked);
private:
    // GLFW Window Stuff
    GLFWwindow   *m_glfwWindow          = nullptr;
    GLFWmonitor  *m_monitor             = nullptr;
    glm::i32vec2  m_initialWindowedSize {0, 0};
    glm::i32vec2  m_windowedPosition    {0, 0};
    glm::i32vec2  m_windowedSize        {0, 0};
    glm::i32vec2  m_viewportSize        {0, 0};
    glm::i32vec2  m_viewportCenter      {0, 0};
    glm::vec2     m_viewportScale       {0, 0};
    glm::dvec2    m_cursorPosition      {0, 0};
    float         m_viewportAutoScale   = 1.0f;
    bool          m_updateViewport      = true;
    bool          m_cursorLocked        = false;

    // OpenGL Rendering Stuff
    std::unique_ptr<Renderer> m_renderer;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_MVP;

    double m_lastTime    = 0.0;
    int    m_nbFrames    = 0;
    double m_currentTime = 0.0;


    // Lifetime methods
    void OnAwake();
    void OnStart();
    void OnUpdate();
    void OnEnd();

    // Callbacks
    static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                     const GLchar *message, const void *userParam);

    static void ResizeCallback(GLFWwindow *window, int cx, int cy);
    static void KeyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);
    static void CursorCallback(GLFWwindow *window, double xpos, double ypos);
public:
    // === Application specific variables === //

    // === Shaders & Materials === //
    std::shared_ptr<Shader> simpleTexturedUnlitShader;
    std::shared_ptr<Shader> simpleUnlitShader;

    std::shared_ptr<Material> simpleMaterial;
    // === === === === === === === //


    glm::vec4 rgba = {1.0f,1.0f,1.0f,1.0f};
    float increment = 0.05f;
    int incrementIndex = 0;

    // set up example data
    std::vector<glm::vec2> quadPositions;
    std::vector<glm::vec2> quadUVs = {
            glm::vec2(0.0, 0.0), // 0
            glm::vec2(1.0, 0.0), // 1
            glm::vec2(1.0, 1.0), // 2
            glm::vec2(0.0, 1.0) // 3
    };
    std::vector<unsigned int> quadIndices = {
            0, 1, 2,
            2, 3, 0
    };
};


#endif //OPENGL_SANDBOX_APPWINDOW_H
