#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

HWND hEdit1, hEdit2;
HBRUSH hBrush;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            CreateWindow(TEXT("STATIC"), TEXT(" Please input two numbers"), WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 20, 200, 25, hwnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 50, 50, 140, 25, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 50, 80, 140, 25, hwnd, NULL, NULL, NULL);
            
            CreateWindow(TEXT("BUTTON"), TEXT("+"), WS_VISIBLE | WS_CHILD, 65, 120, 25, 25, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("-"), WS_VISIBLE | WS_CHILD, 95, 120, 25, 25, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("*"), WS_VISIBLE | WS_CHILD, 125, 120, 25, 25, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("/"), WS_VISIBLE | WS_CHILD, 155, 120, 25, 25, hwnd, (HMENU)4, NULL, NULL);
            
            hBrush = CreateSolidBrush(RGB(120, 255, 255));
            break;
        }

        case WM_COMMAND: {
            if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
                TCHAR buf1[20], buf2[20], resStr[50];
                GetWindowText(hEdit1, buf1, 20);
                GetWindowText(hEdit2, buf2, 20);
                
                double num1 = _tstof(buf1); 
                double num2 = _tstof(buf2);
                double result = 0;

                switch (LOWORD(wParam)) {
                    case 1: result = num1 + num2; break;
                    case 2: result = num1 - num2; break;
                    case 3: result = num1 * num2; break;
                    case 4: 
                        if(num2 != 0) result = num1 / num2;
                        else { MessageBox(hwnd, TEXT("Cannot divide by zero!"), TEXT("Error"), MB_OK | MB_ICONERROR); return 0; }
                        break;
                }
                
                _stprintf(resStr, TEXT("%g"), result);
                MessageBox(hwnd, resStr, TEXT("Result"), MB_OK);
            }
            break;
        }

        case WM_CTLCOLORDLG:
            return (LRESULT)hBrush;
        case WM_CTLCOLORSTATIC:
            SetBkMode((HDC)wParam, TRANSPARENT);
            SetTextColor((HDC)wParam, RGB(255, 255, 255));
            return (LRESULT)hBrush;

        case WM_DESTROY: {
            DeleteObject(hBrush);
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(120, 255, 255));
    wc.lpszClassName = TEXT("MyCalculatorClass");

    if(!RegisterClass(&wc)) return 0;

    HWND hwnd = CreateWindow(TEXT("MyCalculatorClass"), TEXT("My Calculator"),
        WS_VISIBLE | WS_SYSMENU | WS_CAPTION, 
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, 
        NULL, NULL, hInstance, NULL);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
