#ifndef RECTDRAWER_H
#define RECTDRAWER_H

#include "Tool.h"
#include "LineDrawer.h"

class RectDrawer : public Tool {
public:
    static void drawRect(HDC, Vector2D*, Vector2D*, COLORREF);
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) override;
};

#endif