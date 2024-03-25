#ifndef TOOL_H
#define TOOL_H

#include <windows.h>
#include "Vector2D.h"

class Tool {
protected:
    Vector2D* startPoint = NULL;
    Vector2D* endPoint = NULL;
    bool canDraw = false;
public:
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) = 0;
};

#endif