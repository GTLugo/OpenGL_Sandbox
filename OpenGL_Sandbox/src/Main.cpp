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

    auto window = std::make_unique<AppWindow>("Sandbox Window :)", false, false);
    if (!window->successfulInit) return -1;

    window->GameLoop();

    std::cout << "Have a good day! <3" << std::endl;
    //getchar();
    return 0;
}

