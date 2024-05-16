#include "FloodFiller.h"
#include <queue>

void FloodFiller::fillShape(HDC hdc, Vector2D* start, COLORREF borderColor, COLORREF targetColor, int size) {
    std::queue<Vector2D*> queue;
    queue.push(start);
    while (!queue.empty()) {
        Vector2D* current = queue.front();
        queue.pop();
        COLORREF color = GetPixel(hdc, current->X(), current->Y());
        if (color != borderColor && color != targetColor) {
            SetPixel(hdc, current->X(), current->Y(), targetColor);
            queue.push(new Vector2D(current->X() + 1, current->Y()));
            queue.push(new Vector2D(current->X() - 1, current->Y()));
            queue.push(new Vector2D(current->X(), current->Y() + 1));
            queue.push(new Vector2D(current->X(), current->Y() - 1));
        }
    }
}