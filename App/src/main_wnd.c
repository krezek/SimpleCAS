#include "platform.h"

#include <main_wnd.h>
#include <winutil.h>
#include <ribbon.h>
#include <panel.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Simple Computer Algebra System");

LRESULT CALLBACK DefaultWindow_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static LRESULT HandleMessage(MainWindow* _this, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT OnCreate(MainWindow* mw);
LRESULT OnDestroy(MainWindow* mw);

ATOM MainWindow_RegisterClass()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_DBLCLKS;
    wcex.lpfnWndProc = DefaultWindow_Proc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);
}

LRESULT CALLBACK DefaultWindow_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MainWindow* pThis;

    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (MainWindow*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->_hWnd = hWnd;
    }
    else
    {
        pThis = (MainWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (pThis)
    {
        return pThis->_HandleMessageFunc(pThis, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

BOOL MainWindow_Create(MainWindow* _this)
{
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        _this
    );

    _this->_hWnd = hWnd;

    return _this->_hWnd ? TRUE : FALSE;
}

MainWindow* MainWindow_init()
{
    MainWindow* mw = (MainWindow*)malloc(sizeof(MainWindow));
    assert(mw != NULL);

    mw->_HandleMessageFunc = HandleMessage;

    mw->_panelList = PanelList_init();

    return mw;
}

void MainWindow_free(MainWindow* mw)
{
    PanelList_free(mw->_panelList);
    free(mw);
}

static LRESULT HandleMessage(MainWindow* _this, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        return OnCreate(_this);

    case WM_DESTROY:
        return OnDestroy(_this);

    default:
        return DefWindowProc(_this->_hWnd, uMsg, wParam, lParam);
    }
}

LRESULT OnCreate(MainWindow* mw)
{
    if (CreateRibbon(mw->_hWnd))
    {
        ShowError(L"MainWindow::OnCreate::unable to create ribbon!");
        return -1;
    }

    return 0;
}

LRESULT OnDestroy(MainWindow* mw)
{
    DestroyRibbon();
    PostQuitMessage(0);

    return 0;
}
