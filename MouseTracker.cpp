#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

char g_szClassName[] = "MouseTracker";
HINSTANCE g_hInst = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    g_hInst = hInstance;

    WNDCLASSEXA wc;
    wc.cbSize        = sizeof(WNDCLASSEXA);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIconA(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIconA(NULL, IDI_APPLICATION);

    if(!RegisterClassExA(&wc))
    {
        return 0;
    }

    HWND hwnd = CreateWindowExA(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        g_szClassName,
        "Mouse Tracker",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        120, 50,
        NULL, NULL,
        hInstance,
        NULL
    );

    if(hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while(GetMessageA(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
        {
            SetTimer(hwnd, 1, 50, NULL);
            return 0;
        }
        
        case WM_TIMER:
        {
            POINT pt;
            GetCursorPos(&pt);
            
            DEVMODE devMode;
            devMode.dmSize = sizeof(devMode);
            if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode))
            {
                int screenWidth = devMode.dmPelsWidth;
                int screenHeight = devMode.dmPelsHeight;

                char text[50];
                sprintf_s(text, sizeof(text), "X: %ld, Y: %ld", 
                    pt.x * screenWidth / (GetSystemMetrics(SM_CXSCREEN) - 1), 
                    pt.y * screenHeight / (GetSystemMetrics(SM_CYSCREEN) - 1));
                
                PAINTSTRUCT ps;
                HDC hdc = GetDC(hwnd);
                RECT rect;
                GetClientRect(hwnd, &rect);
                
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
                
                DrawTextA(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                
                ReleaseDC(hwnd, hdc);
            }
            return 0;
        }
        
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}