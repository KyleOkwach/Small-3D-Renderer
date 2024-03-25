#include "RebelGL.h"

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

void RebelGL::drawPixel(int x, int y, u32 color) 
{
    if (x >= 0 && x < screen_width && y >= 0 && y < screen_height) {
        int inverted_y = screen_height - (y + 1);  // To make y axis point down
        int p = inverted_y * screen_width + x;
        pixel[p] = color;
    }
}

void RebelGL::fill_screen(u32 color) {
    std::fill(pixel, pixel + screen_width * screen_height, color);
}

void RebelGL::fillRect(int x, int y, int width, int height, u32 color) 
{
    // Ensure x, y, width, and height are within bounds
    if (x < 0) { width += x; x = 0; }
    if (y < 0) { height += y; y = 0; }

    if (x + width > screen_width) {
        width = screen_width - x;
    }
    if (y + height > screen_height) {
        height = screen_height - y;
    }

    // Adjust y-coordinate for inverted y-axis
    int inverted_y = screen_height - y - 1;

    // Calculate starting position in memory
    u32* start_pixel = pixel + (inverted_y * screen_width + x);

    // Fill the rectangle
    for (int row = 0; row < height; ++row) {
        std::fill(start_pixel, start_pixel + width, color);
        start_pixel += screen_width;
    }
}