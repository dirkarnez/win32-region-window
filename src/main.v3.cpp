// Include Windows Headers
#include <windows.h>
#include <dwmapi.h>

// Create Window Procedure and Window Class
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSEX wcex;

// Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Initialize Window Class
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"MyWindowClass";
    wcex.hIconSm = NULL; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    // Register Window Class
    if (!RegisterClassEx(&wcex))
        return 1;

    // Create Window
    HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, L"MyWindowClass", L"My Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);

    // Create Round Rectangular Window Shape
    HRGN hRgn = CreateRoundRectRgn(0, 0, 500, 500, 10, 10);
    SetWindowRgn(hWnd, hRgn, TRUE);


    // MARGINS margins = {-1};
    // DwmExtendFrameIntoClientArea(hWnd, &margins);

    // Enable Blur Behind Window
    DWM_BLURBEHIND bb = {0};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = hRgn;
    DwmEnableBlurBehindWindow(hWnd, &bb);

    // Show Window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main Message Loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}