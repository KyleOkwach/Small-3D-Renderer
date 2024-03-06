#include <Windows.h>
#include <stdint.h>

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

class WinGL
{
private:
    /* data */
public:
    WinGL(HWND window);
    ~WinGL();

    RECT rect;
    u32 *pixel;
    HDC hdc;
    BITMAPINFO bitmap_info;

    void *memory;
    int screen_width;
    int screen_height;

    void update();
    void fill_screen(u32 color);
    void drawPixel(int x, int y, u32 color);
    void fillRect(int x, int y, int width, int height, u32 color);
};

WinGL::WinGL(HWND window)
{
    hdc = GetDC(window); // Device context
    GetClientRect(window, &rect);

    screen_width = rect.left - rect.right;
    screen_height = rect.bottom - rect.top;

    memory = VirtualAlloc(
        0,
        screen_width * screen_height * sizeof(unsigned int),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE 
    );

    u32 *pixel = (u32 *)memory;  // Address to start(1st 32 bits) of memory

    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = screen_width;
    bitmap_info.bmiHeader.biHeight = screen_height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;
}

WinGL::~WinGL()
{  // Destructor
}

void WinGL::update() 
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
        memory,  // Memory
        &bitmap_info,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

void WinGL::fill_screen(u32 color) {
    for(int pixel_num = 0; pixel_num < screen_width * screen_height; pixel_num++) {
        // Fill entire screen
        *pixel++ = color;  // Go to next pixel address then change color value
    }
}

void WinGL::drawPixel(int x, int y, u32 color) 
{
    for(int pixel_num = 0; pixel_num < screen_width * screen_height; pixel_num++) {
        int inverted_y = screen_height - (y + 1);  // To make y axis point down
        int p = inverted_y * screen_width + x;  // y * s_screen_width + x
        if(pixel_num== p) {
            *pixel = color;
        }
        *pixel++;  // Go to next pixel address
    }
}

void WinGL::fillRect(int x, int y, int width, int height, u32 color) 
{
    for(int pixel_num = 0; pixel_num < screen_width * screen_height; pixel_num++) {
        int inverted_y = screen_height - (y + 1);  // To make y axis point down
        int p = inverted_y * screen_width + x;  // y * s_screen_width + x

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