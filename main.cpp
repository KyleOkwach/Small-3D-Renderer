#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <stdint.h>
#include <iostream>

#include "Window.cpp"
#include "WinGL.cpp"
#include "Utils.cpp"

typedef uint32_t u32;
int globalRunning = 1;
int screen_width = 0;
int screen_height = 0;

LRESULT Wndproc(
  HWND window,
  UINT message,
  WPARAM wParam,
  LPARAM lParam
) {
    LRESULT result;
    switch(message) {
        case WM_CLOSE:
            globalRunning = 0;
            break;
        default:
            result = DefWindowProc(window, message, wParam, lParam);
    }

    return result;
}

int WinMain(
    HINSTANCE hInstance,  // Handle instance of the program
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,  // Argument passed when running program in the command line
    int nShowCmd  // How to show the program
) {
    Window mainWindow(hInstance);
    // gameWindow.Wndproc = Wndproc;

    if (mainWindow.Create(L"Game") != 0)
    {
        // Window creation failed
        std::cout<<"Failed to open window\n"<< Utils::GetLastErrorAsString();
        return -1;
    }

    while(globalRunning) {
        // fill_screen(pixel, BLACK);
        // fill_rect(100, 100, 50, 50, rect, pixel, 0x1F1F1F);

        MSG msg;
        while(PeekMessage(&msg, mainWindow.window, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);  // Translates key code when key is pressed to actual character
            DispatchMessage(&msg);

            // Check if user quit the window
            if (msg.message == WM_QUIT) {
                globalRunning = 0;  // End the main loop
            }
        }

        // gl.update()
    }
    
    return 0;
}