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
    Window(HINSTANCE hInstance);
    ~Window();

    HWND window;
    wchar_t CLASS_NAME[];

    int Create(const wchar_t* title);
    static LRESULT Wndproc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
};

Window::Window(HINSTANCE hInstance)
: hInstance(hInstance), window(nullptr)
{
    this->hInstance = hInstance;
    wcscat(CLASS_NAME, L"GameWindowClass");

    window_class = { 0 };
    window_class.lpfnWndProc = Wndproc;  // Handles messages sent to window
    window_class.hInstance = hInstance;
    window_class.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&window_class))
    {
        // Registration failed
        cout << "Window class registration failed\n";
    }
}

Window::~Window()
{
    // Destructor
    cout<<"Closing window";
}

int Window::Create(const wchar_t* title)
{
    HWND window =  CreateWindowEx(
        0,
        CLASS_NAME,
        title,
        // L"Game",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        CW_USEDEFAULT,  // X position of window
        CW_USEDEFAULT,  // Y position of window
        CW_USEDEFAULT,  // screen_width
        CW_USEDEFAULT,  // screen_height
        0,
        0,
        hInstance,
        0
    );

    if (window == nullptr)
    {
        // Window creation failed
        return GetLastError();
    }

    // Window creation successful
    return 0;
}

LRESULT CALLBACK Window::Wndproc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Window message handling
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    // case WM_CLOSE:
    //     break;
    default:
        return DefWindowProc(window, message, wParam, lParam);
    }
    return 0;
}