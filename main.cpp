#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <vector>

#include "includes/Utils.h"
#include "includes/Window.h"

#include "includes/math/RVector.h"

#include "includes/gl/RebelGL.h"

#include "includes/gl/3D/Tri.h"
#include "includes/gl/3D/Mesh.h"

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
        std::cout<<"Failed to open window\nError: "<< GetLastErrorAsString();
        return -1;
    }

    RebelGL rgl(mainWindow.window, true);

    // ________Initializations________
    std::vector<RVector> points = {
        RVector(50, 50),
        RVector(50, 150),
        RVector(150, 150),
        RVector(150, 50)
    };

    Mesh cube;
    cube.tris = {
        // Front face
        {RVector(0, 0), RVector(1, 0), RVector(1, 1)},
        {RVector(0, 0), RVector(1, 1), RVector(0, 1)},
        // Back face
        {RVector(0, 1), RVector(1, 1), RVector(1, 10)},
        {RVector(0, 1), RVector(1, 10), RVector(0, 10)},
        // Left face
        {RVector(0, 0), RVector(0, 1), RVector(0, 10)},
        {RVector(0, 0), RVector(0, 10), RVector(0, 1)},
        // Right face
        {RVector(1, 0), RVector(1, 1), RVector(1, 10)},
        {RVector(1, 0), RVector(1, 10), RVector(1, 1)},
        // Top face
        {RVector(0, 0), RVector(1, 0), RVector(1, 10)},
        {RVector(0, 0), RVector(1, 10), RVector(0, 10)},
        // Bottom face
        {RVector(0, 1), RVector(1, 1), RVector(1, 10)},
        {RVector(0, 1), RVector(1, 10), RVector(0, 10)}
    };

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

        // ________MAIN________
        // Your code goes here
        rgl.fill_screen(0x1F1F1F);

        for(RVector i : points) {
            rgl.drawPixel(static_cast<int>(i.x), static_cast<int>(i.y), GREEN, 10);
        }
        rgl.drawLine(100, 350, 400, 100, GREEN, 5);
        rgl.drawLine(100, 350, 2000, 2000, GREEN, 5);

        // for(auto tri : cube.tris) {
        //     rgl.drawPixel(static_cast<int>(tri[0].x), static_cast<int>(i.y), GREEN, 10);
        //     rgl.drawPixel(static_cast<int>(i.x), static_cast<int>(i.y), GREEN, 10);
        //     rgl.drawPixel(static_cast<int>(i.x), static_cast<int>(i.y), GREEN, 10);
        // }

        rgl.update();
    }
    
    return 0;
}