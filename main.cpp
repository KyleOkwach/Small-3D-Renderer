#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <stdint.h>
#include <iostream>

#include "Window.cpp"
#include "RebelGL.cpp"
#include "Utils.cpp"

typedef uint32_t u32;
int globalRunning = true;
int screen_width = 0;
int screen_height = 0;

int WinMain(
    HINSTANCE hInstance,  // Handle instance of the program
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,  // Argument passed when running program in the command line
    int nShowCmd  // How to show the program
) {
    Window mainWindow(hInstance, 640, 640);

    if (mainWindow.Create(L"Rebel Engine") != 0)
    {
        // Window creation failed
        std::cout<<"Failed to open window\nError: "<<Utils::GetLastErrorAsString();
        return -1;
    }

    RebelGL rgl(mainWindow.window);

    // Application loop
    while(globalRunning) {
        MSG msg;
        // Check for messages from the window
        while(PeekMessage(&msg, mainWindow.window, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);  // Translates key code when key is pressed to actual character
            DispatchMessage(&msg);

            // Check if user quit the window
            if (msg.message == WM_QUIT) {
                globalRunning = false;  // End the main loop
            }
        }

        // Main Activities
        rgl.fill_screen(RED);

        rgl.drawPixel(10, 10, WHITE);
        rgl.drawPixel(11, 11, WHITE);
        rgl.drawPixel(12, 12, WHITE);
        rgl.drawPixel(13, 13, WHITE);

        // rgl.fillRect(30, 40, 15, 15, GREEN);

        rgl.update();
    }
    
    return 0;
}