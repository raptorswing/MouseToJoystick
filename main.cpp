#include "MainWindow.h"
#include <QApplication>

#include <Windows.h>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    Q_UNUSED(nCode)
    Q_UNUSED(lParam)


    if(wParam == WM_RBUTTONDOWN)
    {
      // right button clicked
      MainWindow::rightDownDetected = true;
    }
    else if (wParam == WM_RBUTTONUP)
    {
        MainWindow::rightUpDetected = true;
    }
    else if (wParam == WM_LBUTTONDOWN)
    {
        MainWindow::leftDownDetected = true;
    }
    else if (wParam == WM_LBUTTONUP)
    {
        MainWindow::leftUpDetected = true;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
    HHOOK MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, hInstance, 0);

    int toRet = a.exec();

    UnhookWindowsHookEx(MouseHook);

    return toRet;
}

