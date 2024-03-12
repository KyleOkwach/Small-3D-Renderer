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

RebelGL::RebelGL(HWND window)
{
    this->window = window;
    
    hdc = GetDC(window); // Device context
    GetClientRect(window, &rect);

    this->screen_width = rect.right - rect.left;
    this->screen_height = rect.bottom - rect.top;

    winMemory = VirtualAlloc(
        0,
        screen_width * screen_height * sizeof(unsigned int),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE 
    );

    if (!winMemory) {
        DWORD error = GetLastError();
        throw std::runtime_error("Failed to allocate window memory. Error code: " + std::to_string(error));
    }

    pixel = (u32 *)winMemory;


    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = screen_width;
    bitmap_info.bmiHeader.biHeight = screen_height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;
}

RebelGL::~RebelGL()
{
    // Destructor
    if(winMemory) {
        VirtualFree(winMemory, 0, MEM_RELEASE);
        winMemory = nullptr;
    }
}

void RebelGL::update() 
{
    StretchDIBits(
        hdc,  // Handle device context
        0,
        0,
        screen_width,
        screen_height,
        0,
        0,
        screen_width,
        screen_height,
        winMemory,  // Memory
        &bitmap_info,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

void RebelGL::fill_screen(u32 color) {
    std::fill(pixel, pixel + screen_width * screen_height, color);
}

void RebelGL::drawPixel(int x, int y, u32 color) 
{
    if (x >= 0 && x < screen_width && y >= 0 && y < screen_height) {
        int inverted_y = screen_height - (y + 1);  // To make y axis point down
        int p = inverted_y * screen_width + x;
        pixel[p] = color;
    }
}

void RebelGL::fillRect(int x, int y, int width, int height, u32 color) 
{
    for(int pixel_num = 0; pixel_num < screen_width * screen_height; pixel_num++) {
        int inverted_y = screen_height - (y + 1);  // To make y axis point down
        // int p = inverted_y * screen_width + x;  // y * s_screen_width + x

        int top = inverted_y;
        int bottom = top - height;
        int left = x;
        int right = x + width;
        if(
            pixel_num / screen_width < top &&
            pixel_num / screen_width > bottom &&
            pixel_num % screen_width > left &&
            pixel_num % screen_width < right
        ) {
            *pixel = color;
        }
        *pixel++;  // Go to next pixel address
    }
}