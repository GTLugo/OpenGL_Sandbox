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

#include "Vector.h"
#include "Renderer.h"

void GLAPIENTRY MessageCallback (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                 const GLchar* message, const void* userParam);

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

    explicit AppWindow(const std::string &windowName = "", bool vsync = true, bool fullscreen = false);
    ~AppWindow();

    // Lifetime methods
    int WindowInit(const std::string &windowName, bool vsync, bool fullscreen);
    void GameLoop();

    // Generic methods
    inline const bool ShouldClose() const { return glfwWindowShouldClose(m_glfwWindow); }
    inline const void SwapBuffers() const { glfwSwapBuffers(m_glfwWindow); }
    inline const void PollEvents() const { glfwPollEvents(); }
    void Resize(int cx, int cy);
    inline const bool IsFullscreen() const { return glfwGetWindowMonitor(m_glfwWindow) != nullptr; }
    void SetFullScreen(bool fullscreen);

    // Getters
    inline const GLFWwindow *GetglfwWindow() const { return m_glfwWindow; }

    // Setters

    // Callbacks
    static void CallbackResize(GLFWwindow* window, int cx, int cy);
private:
    // GLFW Window Stuff
    GLFWwindow*                                 m_glfwWindow     = nullptr;
    GLFWmonitor*                                m_monitor        = nullptr;
    Vector2DInt                                 m_windowPosition  {0, 0};
    Vector2DInt                                 m_windowSize      {0, 0};
    Vector2DInt                                 m_viewportSize    {0, 0};
    bool                                        m_updateViewport = true;
    // OpenGL Rendering Stuff
    std::unique_ptr<Renderer> m_renderer = std::make_unique<Renderer>();

    std::unique_ptr<glm::mat4> m_projectionMatrix;
    double m_lastTime    = 0.0;
    int    m_nbFrames    = 0;
    double m_currentTime = 0.0;

    // Lifetime methods
    void OnAwake();
    void OnStart();
    void OnUpdate();
    void OnEnd();
public:
    // === Application specific variables === //

    // === Shaders & Materials === //
    std::shared_ptr<Shader> simpleTexturedUnlitShader;
    std::shared_ptr<Shader> simpleUnlitShader;

    std::shared_ptr<Material> simpleMaterial;
    // === === === === === === === //

    Vector4D rgba = {1.0f,1.0f,1.0f,1.0f};
    float increment = 0.05f;
    int incrementIndex = 0;

    // set up example data
    std::vector<Vector2D> quadPositions = {
            Vector2D(-0.5f, -0.5f), // 0
            Vector2D(0.5f, -0.5f), // 1
            Vector2D(0.5f,  0.5f), // 2
            Vector2D(-0.5f,  0.5f)// 3
    };
    std::vector<Vector2D> quadUVs = {
            Vector2D(0.0, 0.0), // 0
            Vector2D(1.0, 0.0), // 1
            Vector2D(1.0, 1.0), // 2
            Vector2D(0.0, 1.0) // 3
    };
    std::vector<unsigned int> quadIndices = {
            0, 1, 2,
            2, 3, 0
    };

    Mesh *quadMesh;
};


#endif //OPENGL_SANDBOX_APPWINDOW_H
