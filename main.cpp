#include <Windows.h>
#include <iostream>

const int Threshold = 20;

COLORREF GetPixelColorAt(int x, int y) {
    HDC hdcScreen = GetDC(NULL);
    COLORREF color = GetPixel(hdcScreen, x, y);
    ReleaseDC(NULL, hdcScreen);
    return color;
}

void MouseClick() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main() {
    while (true) {
        if (GetAsyncKeyState('X') & 0x8000) { 
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            COLORREF color1 = GetPixelColorAt(cursorPos.x + 2, cursorPos.y + 2);
            int color1R = GetRValue(color1);
            int color1G = GetGValue(color1);
            int color1B = GetBValue(color1);

            while (GetAsyncKeyState('X') & 0x8000) {
                Sleep(1);
                GetCursorPos(&cursorPos);
                COLORREF color2 = GetPixelColorAt(cursorPos.x + 2, cursorPos.y + 2);
                int color2R = GetRValue(color2);
                int color2G = GetGValue(color2);
                int color2B = GetBValue(color2);

                if (abs(color1R - color2R) > Threshold || abs(color1G - color2G) > Threshold || abs(color1B - color2B) > Threshold) {
                    MouseClick();
                    Sleep(450);
                }
            }
        }
        if (GetAsyncKeyState(VK_END) & 0x8000) { 
            break;
        }
    }
    return 0;
}
