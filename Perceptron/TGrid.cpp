//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TGrid.h"

//---------------------------------------------------------------------------
__fastcall TGrid::TGrid(int cnt_layers, int cnt_neyrons, int cnt_sinaps)
{
    TLayer* myLayer = new TLayer(cnt_neyrons, 0, 0);
    l.push_back(myLayer);
    for (int I = 0; I < cnt_layers; I++) {
        myLayer = new TLayer(cnt_neyrons, 5, myLayer);
        l.push_back(myLayer);
    }
    myLayer = new TLayer(1, cnt_neyrons, myLayer);
    l.push_back(myLayer);
}

__fastcall TGrid::~TGrid()
{
    for (int I = 0; I < l.size(); I++) {
        delete l[I];
    }
}

double __fastcall TGrid::getIn(int index)
{
    return l[0]->out[index];
}

void __fastcall TGrid::setIn(int index, double val)
{
    TLayer* first = l[0];
    first->out[index] = val;
}


double __fastcall TGrid::getOut(int index)
{
    return l[l.size()-1]->out[index];
}

void __fastcall TGrid::setOut(int index, double val)
{
    l[l.size()-1]->out[index] = val;
}

void __fastcall TGrid::Transfer()
{
    for (int I = 1; I < l.size(); I++) {
        l[I]->Transfer();
    }
}

void __fastcall TGrid::Learn(double val)
{
    TLayer* last = l[l.size()-1];
    last->err[0] = (val - last->out[0]) * last->out[0] * (1-last->out[0]);
    for (int I = l.size()-1; I>=0; I--) {
        l[I]->Learn();
    }
}


void __fastcall TGrid::DrawLayer(TCanvas* Canvas, int layer_number, int X, int Y)
{
    for (int I = 0; I < l[layer_number]->count; I++) {
        Canvas->Pen->Color = RGB(255,255,255) * l[layer_number]->out[I];
        Canvas->MoveTo(X+I, Y);
        Canvas->LineTo(X+I, Y+10);
    }
}




#pragma package(smart_init)
