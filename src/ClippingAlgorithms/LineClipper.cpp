#include "src/ClippingAlgorithms/LineClipper.h"


Line* LineClipper::Clip(Line* line , ScreenBoarder screenBoarder)
{
    OutCode outCodeStart = ComputeOutCode(line->Start(), screenBoarder);
    OutCode outCodeEnd = ComputeOutCode(line->End(), screenBoarder);

    while (true) {
        if (!(outCodeStart.All | outCodeEnd.All)) {
            // if all of the outcode is null he are at our destination.
            return line;
        }
        else if (outCodeStart.All & outCodeEnd.All) {
            // if there are two similar tags then the line is outside of the screen.
            return nullptr;
        }
        else {
            if (outCodeStart.All) {
                if (outCodeStart.Left == 1) {
                    line->SetStart(line->VerticalIntersect(screenBoarder.XLeft));
                }
                else if (outCodeStart.Right == 1) {
                    line->SetStart(line->VerticalIntersect(screenBoarder.XRight));
                }
                else if (outCodeStart.Top == 1) {
                    line->SetStart(line->HorizontalIntersect(screenBoarder.YTop));
                }
                else if (outCodeStart.Bottom == 1) {
                    line->SetStart(line->HorizontalIntersect(screenBoarder.YBottom));
                }
            }
            else {
                if (outCodeEnd.Left == 1) {
                    line->SetEnd(line->VerticalIntersect(screenBoarder.XLeft));
                }
                else if (outCodeEnd.Right == 1) {
                    line->SetEnd(line->VerticalIntersect(screenBoarder.XRight));
                }
                else if (outCodeEnd.Top == 1) {
                    line->SetEnd(line->HorizontalIntersect(screenBoarder.YTop));
                }
                else if (outCodeEnd.Bottom == 1) {
                    line->SetEnd(line->HorizontalIntersect(screenBoarder.YBottom));
                }
            }
        }
        if (line->Start() == nullptr || line->End() == nullptr) {
            return nullptr;
        }
        outCodeStart = ComputeOutCode(line->Start(), screenBoarder);
        outCodeEnd = ComputeOutCode(line->End(), screenBoarder);
    }
    return line;
}

OutCode LineClipper::ComputeOutCode(Vector2D *point, ScreenBoarder screenBoarder)
{
    OutCode outCode;
    outCode.All = 0;

    if (screenBoarder.XLeft > point->X())
    {
        outCode.Left = 1;
    }
    if (screenBoarder.XRight < point->X())
    {
        outCode.Right = 1;
    }
    if (screenBoarder.YTop < point->Y())
    {
        outCode.Top = 1;
    }
    if (screenBoarder.YBottom > point->Y())
    {
        outCode.Bottom = 1;
    }
    return outCode;
}