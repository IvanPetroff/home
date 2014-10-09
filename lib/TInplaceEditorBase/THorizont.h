//---------------------------------------------------------------------------

#ifndef THorizontH
#define THorizontH
#include <map.h>
#include <vector.h>
//---------------------------------------------------------------------------
class THorizont {
private:
    vector <TRect> Rects;
public:
    bool        operator()              (TRect Rect1, TRect Rect2);
    void        __fastcall AddRect      (TRect Rect);
    HRGN        __fastcall GetHRGN      (int Left, int Top);
};

#endif
