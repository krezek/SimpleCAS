#include "platform.h"

#include <main_wnd.h>
#include <winutil.h>

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    RedirectIOToConsole();
#endif

    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        ShowError(_T("WinMain:CoInitialize"));
        return -1;
    }

    if (!MainWindow_RegisterClass())
    {
        ShowError(_T("Call to RegisterClass failed!"));

        return -1;
    }

    MainWindow* mainWindow = MainWindow_init();

    if (!MainWindow_Create(mainWindow))
    {
        ShowError(_T("Call to CreateWindow failed!"));

        return -1;
    }

    ShowWindow(mainWindow->_hWnd, nCmdShow);
    UpdateWindow(mainWindow->_hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    MainWindow_free(mainWindow);

    CoUninitialize();

    return (int)msg.wParam;
}

