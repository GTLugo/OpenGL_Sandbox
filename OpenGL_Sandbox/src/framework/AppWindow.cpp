//
// Created by galex on 7/21/2020.
//
#include "AppWindow.h"

#include <iostream>

#include "Vector.h"

void GLAPIENTRY MessageCallback (GLenum source,
                                 GLenum type,
                                 GLuint id,
                                 GLenum severity,
                                 GLsizei length,
                                 const GLchar* message,
                                 const void* userParam) {
    // only output if there is an error or such
    if (type != GL_DEBUG_TYPE_OTHER)
        fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                 ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                 type, severity, message );
}

AppWindow::AppWindow(const std::string &windowName, bool vsync, bool fullscreen) {
    successfulInit = WindowInit(windowName, vsync, fullscreen) == 0;
    if (successfulInit) {
        m_lastTime = glfwGetTime();
        m_nbFrames = 0;
    }
}

AppWindow::~AppWindow() {
    glfwTerminate();
}

int AppWindow::WindowInit(const std::string &windowName, bool vsync, bool fullscreen) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
//    m_glfwWindow = std::unique_ptr<GLFWwindow, DestroyglfwWin>(
//            glfwCreateWindow(1920, 1080, "Sandbox", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr)
//            );
    m_glfwWindow = glfwCreateWindow(640, 480, windowName.c_str(), nullptr, nullptr);
    if (!m_glfwWindow) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSetWindowUserPointer(m_glfwWindow, this);
    glfwSetWindowSizeCallback(m_glfwWindow, AppWindow::CallbackResize);

    m_monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(m_glfwWindow, &m_windowSize.x(), &m_windowSize.y());
    glfwGetWindowPos(m_glfwWindow, &m_windowPosition.x(), &m_windowPosition.y());
    m_updateViewport = true;
    SetFullScreen(fullscreen);

    // enable/disable vsync
    glfwSwapInterval(vsync);

    // Now that the GL context is made current, initialize glew
    if (glewInit() != GLEW_OK)
        std::cerr << "ERROR | Glew failed to initialize!" << std::endl;
    std::cout << "Using GLEW " << glGetString(GL_VERSION) << " *poggers*" << std::endl;

    // During init, enable debug output
#ifdef CMAKE_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);
#endif

    return 0;
}

void AppWindow::GameLoop() {
    // Initialize more generic application specific stuff
    OnAwake();
    // TODO: Event callbacks to allow subscribing to OnStart from other classes.
    // Initialize application specific stuff
    OnStart();
    /* Loop until the user closes the window */
    while (!ShouldClose()) {
        // Measure speed
        m_currentTime = glfwGetTime();
        m_nbFrames++;
        if (m_currentTime - m_lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame (%d FPS)\n", 1000.0/double(m_nbFrames), m_nbFrames);
            m_nbFrames = 0;
            m_lastTime += 1.0;
        }
        if (m_updateViewport) {
            glfwGetFramebufferSize(m_glfwWindow, &m_viewportSize.x(), &m_viewportSize.y());
            glViewport( 0, 0, m_viewportSize.x(), m_viewportSize.y());
            m_updateViewport = false;
        }

        /* Render here */
        m_renderer->Clear();

        // TODO: Event callbacks to allow subscribing to OnUpdate from other classes.
        OnUpdate();

        /* Swap front and back buffers */
        SwapBuffers();
        /* Poll for and process events */
        PollEvents();
    }
    // TODO: Event callbacks to allow subscribing to OnEnd from other classes.
    OnEnd();
}

void AppWindow::OnAwake() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    m_renderer->SetBufferBit(0.3f, 0.7f, 1.0f, 1.0f);
}

void AppWindow::OnStart() {
    simpleTexturedUnlitShader = std::make_shared<Shader>("res/shaders/SimpleTexturedUnlit.shader");
    simpleUnlitShader = std::make_shared<Shader>("res/shaders/SimpleUnlit.shader");
    simpleMaterial = std::make_shared<Material>(RenderMode::TEXTURED, simpleTexturedUnlitShader, "res/sprites/test_sprite_2.png");

    quadMesh = new Mesh(quadPositions, quadIndices, quadUVs, simpleMaterial);
}

void AppWindow::OnUpdate() {
    m_renderer->DrawMesh(*quadMesh, rgba);

    switch (incrementIndex) {
        case 0:
            if (rgba.r() > 0.0f) {
                rgba.r() -= increment;
                rgba.g() -= increment;
            }
            else {
                rgba.r() = 1.0f;
                rgba.g() = 1.0f;
                incrementIndex = 1;
            }
            break;
        case 1:
            if (rgba.g() > 0.0f) {
                rgba.g() -= increment;
                rgba.b() -= increment;
            }
            else {
                rgba.g() = 1.0f;
                rgba.b() = 1.0f;
                incrementIndex = 2;
            }
            break;
        case 2:
            if (rgba.b() > 0.0f) {
                rgba.b() -= increment;
                rgba.r() -= increment;
            }
            else {
                rgba.b() = 1.0f;
                rgba.r() = 1.0f;
                incrementIndex = 0;
            }
            break;
        default:
            break;
    }
}

void AppWindow::OnEnd() {
    delete quadMesh;
}

void AppWindow::CallbackResize(GLFWwindow *window, int cx, int cy) {
    void *ptr = glfwGetWindowUserPointer(window);
    if (auto *appWindow = static_cast<AppWindow*>(ptr) )
        appWindow->Resize(cx, cy);
}

void AppWindow::SetFullScreen(bool fullscreen) {
    if (IsFullscreen() == fullscreen)
        return;

    if (fullscreen) {
        // backup window position and window size
        glfwGetWindowPos(m_glfwWindow, &m_windowPosition.x(), &m_windowPosition.y());
        glfwGetWindowSize(m_glfwWindow, &m_windowSize.x(), &m_windowSize.y());

        // get resolution of monitor
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // switch to full screen
        glfwSetWindowMonitor(m_glfwWindow, m_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else {
        // restore last window size and position
        glfwSetWindowMonitor(m_glfwWindow, nullptr, m_windowPosition.x(), m_windowPosition.y(),
                m_windowSize.x(), m_windowSize.y(), 0);
    }

    m_updateViewport = true;
}

void AppWindow::Resize(int cx, int cy) {
    std::cout << "Resizing window..." << std::endl;
    m_updateViewport = true;
}