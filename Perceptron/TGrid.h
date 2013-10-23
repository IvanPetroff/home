//---------------------------------------------------------------------------

#ifndef TGridH
#define TGridH
#include <vector.h>
#include "TLayer.h"
//---------------------------------------------------------------------------

class TGrid {
private:
    vector<TLayer*> l;
    double __fastcall getIn(int index);
    void __fastcall setIn(int index, double val);
    double __fastcall getOut(int index);
    void __fastcall setOut(int index, double val);
public:
    __fastcall TGrid(int cnt_layers, int cnt_neyrons, int cnt_sinaps);
    __fastcall TGrid(AnsiString FileName);
    __fastcall ~TGrid();
    void __fastcall Transfer();
    void __fastcall Learn(double val);
    void __fastcall DrawLayer(TCanvas* Canvas, int layer_number, int X, int Y);
    void __fastcall SaveToFile(AnsiString FileName);

    __property double in[int] = {read=getIn,write=setIn};
    __property double out[int] = {read=getOut,write=setOut};
};
#endif
