#ifndef _MAIN_WND_H_
#define _MAIN_WND_H_

typedef struct _MainWindow MainWindow;

typedef LRESULT(*HandleMessageFunc) (MainWindow* _this, UINT uMsg, WPARAM wParam, LPARAM lParam);

typedef struct _MainWindow
{
	HWND _hWnd;

	HandleMessageFunc _HandleMessageFunc;
} MainWindow;

ATOM MainWindow_RegisterClass();

MainWindow* MainWindow_init();
void MainWindow_free(MainWindow* mw);

BOOL MainWindow_Create(MainWindow* _this);

#endif /* _MAIN_WND_H_ */

