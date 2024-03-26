#ifndef Window_H
#define Window_h

#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <iostream>

using namespace std;

class Window
{
private:
    /* data */
    HINSTANCE hInstance;
    WNDCLASS window_class;
public:
    Window(HINSTANCE hInstance, int width, int height);
    ~Window();

    HWND window;
    RECT window_rect;
    int window_width;
    int window_height;
    
    // wchar_t CLASS_NAME[];
    static const int MAX_CLASS_NAME_LENGTH = 256;
    wchar_t CLASS_NAME[MAX_CLASS_NAME_LENGTH]; // Fixed-size array

    int Create(const wchar_t* title);
    static LRESULT Wndproc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif