//---------------------------------------------------------------------------

#include <vcl.h>
#include "AllHeaders.hpp"
#pragma hdrstop

#include "THorizont.h"

//---------------------------------------------------------------------------
void __fastcall THorizont::AddRect(TRect Rect)
{
    Rects.push_back(Rect);
}


HRGN __fastcall THorizont::GetHRGN(int Left, int Top)
{
    vector <tagPOINT> POINTs;
    tagPOINT POINT;
//    sort(Rects.begin(),Rects.end(), *this);

    for (unsigned int I = 0; I < Rects.size(); I++) {
        if (I>0) {
          POINT.x = Rects[I].Left; POINT.y = Rects[I-1].Top; POINTs.push_back(POINT);
        }
        POINT.x = Rects[I].Left; POINT.y = Rects[I].Top; POINTs.push_back(POINT);
        POINT.x = Rects[I].Right; POINT.y = Rects[I].Top; POINTs.push_back(POINT);
        POINT.x = Rects[I].Right; POINT.y = Rects[I].Bottom; POINTs.push_back(POINT);
        POINT.x = Rects[I].Left; POINT.y = Rects[I].Bottom; POINTs.push_back(POINT);
        POINT.x = Rects[I].Left; POINT.y = Rects[I].Top; POINTs.push_back(POINT);
    }
//    POINT.x = Rects[0].Left; POINT.y = Rects[0].Top; POINTs.push_back(POINT);

    for (unsigned int I = 0; I < POINTs.size(); I++) {
        POINTs[I].x -= Left;
        POINTs[I].y -= Top;
    }



    HRGN hRegion;
    hRegion=CreatePolygonRgn(POINTs.begin(), POINTs.size(), 1);

    return hRegion;
}


bool THorizont::operator() (TRect Rect1, TRect Rect2)
{
//    if ((Rect1.Left==Rect2.Left)&&(Rect1.Top>Rect2.Top)) return true;
//    if ((Rect1.Top==Rect2.Top)&&(Rect1.Left>Rect2.Left)) return true;
//    if ((Rect1.Top>Rect2.Top)&&(Rect1.Left>Rect2.Left)) return true;


    if (Rect1.Top>Rect2.Top) return true;
    if ((Rect1.Top==Rect2.Top)&&(Rect1.Left<Rect2.Left)) return true;

    return false;
}
#pragma package(smart_init)
