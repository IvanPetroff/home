//---------------------------------------------------------------------------

#ifndef TLayerH
#define TLayerH
#include <vector.h>
#include "TNeyron.h"
//---------------------------------------------------------------------------
class TLayer {
private:
    vector<TNeyron*> n;
    double __fastcall getOut(int index);
    void __fastcall setOut(int index, double val);
    double __fastcall getErr(int index);
    void __fastcall setErr(int index, double val);
    int __fastcall getCount();

public:
    __fastcall TLayer(int cnt_neyrons, int cnt_sinaps, TLayer* PredLayer);
    __fastcall ~TLayer();
    void __fastcall Transfer();
    __property double out[int] = {read=getOut,write=setOut};
    __property double err[int] = {read=getErr,write=setErr};
    __property int count = {read=getCount};

    void __fastcall Learn();

};
#endif
