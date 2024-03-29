#include "Window.h"

Window::Window(HINSTANCE hInstance, int width, int height)
: hInstance(hInstance), window(nullptr)
{    
    this->hInstance = hInstance;

    window_rect.left = 0;
    window_rect.top = 0;
    window_rect.right = width;
    window_rect.bottom = height;

    AdjustWindowRectEx(
        &window_rect,
        WS_OVERLAPPEDWINDOW,
        0,
        0
    );

    this->window_width = window_rect.right - window_rect.left;
    this->window_height = window_rect.bottom - window_rect.top;

    wcscat(CLASS_NAME, L"GameWindowClass");

    window_class = { 0 };
    window_class.lpfnWndProc = Wndproc;  // Handles messages sent to window
    window_class.hInstance = hInstance;
    window_class.lpszClassName = CLASS_NAME;
    window_class.hCursor = LoadCursor(0, IDC_CROSS);  // Change cursos

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
    if (window != nullptr)
    {
        DestroyWindow(window);
    }
}

int Window::Create(const wchar_t* title)
{
    window =  CreateWindowEx(
        0,
        CLASS_NAME,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,  // X position of window
        CW_USEDEFAULT,  // Y position of window
        window_width,  // window_width
        window_height,  // window_height
        0,
        0,
        hInstance,
        0
    );

    if (window == nullptr)
    {
        // Window creation failed
        return GetLastError();
    } else {
        // Window creation successful
        return 0;
    }
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