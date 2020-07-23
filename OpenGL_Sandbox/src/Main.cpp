#include <GL/glew.h>
#include <GLFW/glfw3.h>
#ifdef WIN32
    #include <Windows.h>
#endif
#include <iostream>

#include "AppWindow.h"

int main(void) {
    // if in release mode, free console
#if defined(WIN32) && !defined(CMAKE_DEBUG)
    FreeConsole();
#endif

    // Create window instance and ensure it was successfully initialized
    auto window = std::make_unique<AppWindow>("Window Test", 1024, 576, false, false);
    if (!window->successfulInit) return -1;
    // Enter window's render loop
    window->GameLoop();

    std::cout << "Have a good day! <3" << std::endl;
    return 0;
}

