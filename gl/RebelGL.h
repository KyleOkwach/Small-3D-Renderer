#ifndef RebelGL_H
#define RebelGL_H

#include <Windows.h>
#include <stdint.h>
#include <iostream>

#define UNICODE
#define _UNICODE

// COLORS
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000

// TYPES & STRUCTS
typedef uint32_t u32;

using namespace std;
class RebelGL
{
private:
    /* data */
public:
    RebelGL(HWND window);
    ~RebelGL();

    void *winMemory;  // Memory that stores window pixel data
    HWND window;
    RECT rect;
    u32 *pixel;
    HDC hdc;
    BITMAPINFO bitmap_info;

    int screen_width;
    int screen_height;

    void update();
    void fill_screen(u32 color);
    void drawPixel(int x, int y, u32 color);
    void fillRect(int x, int y, int width, int height, u32 color);
};

#endif