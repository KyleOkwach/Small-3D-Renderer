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
    void *memory;
    int screen_width;
    int screen_height;
    
    wchar_t CLASS_NAME[];
    int Create(const wchar_t* title);
    static LRESULT Wndproc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
};

Window::Window(HINSTANCE hInstance, int width, int height)
: hInstance(hInstance), window(nullptr)
{    
    this->hInstance = hInstance;
    this->screen_width = width;
    this->screen_height = height;
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
    cout<<"Closing Application...";
    VirtualFree(memory, 0, MEM_RELEASE);
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
        screen_width,  // screen_width
        screen_height,  // screen_height
        0,
        0,
        hInstance,
        0
    );

    memory = VirtualAlloc(
        0,
        this->screen_width * this->screen_height * sizeof(unsigned int),
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE 
    );

    if (window == nullptr)
    {
        // Window creation failed
        return GetLastError();
    }

    // Window creation successful
    return 0;
}

LRESULT CALLBACK Window::Wndproc(
    HWND window,
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam
)
{
    // Window message handling
    LRESULT result;
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        result = DefWindowProc(window, message, wParam, lParam);
    }
    return result;
}