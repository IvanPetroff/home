//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TLayer.h"

//---------------------------------------------------------------------------
__fastcall TLayer::~TLayer()
{
    for (int I = 0; I < n.size(); I++) {
        delete n[I];
    }
}


__fastcall TLayer::TLayer(int cnt_neyrons, int cnt_sinaps, TLayer* PredLayer)
{
    for (int I = 0; I < cnt_neyrons; I++) {
        TNeyron* myNeyron = new TNeyron(cnt_sinaps, (PredLayer==0)?this->n:PredLayer->n);
        n.push_back(myNeyron);
    }
}

void __fastcall TLayer::Transfer()
{
    for (int I = 0; I < n.size(); I++) {
        n[I]->Transfer();
    }
}

double __fastcall TLayer::getOut(int index)
{
    return n[index]->out;
}

void __fastcall TLayer::setOut(int index, double val)
{
    n[index]->out = val;
}


void __fastcall TLayer::Learn()
{
    for (int I = 0; I < n.size(); I++) {
        n[I]->CalcErr();
        n[I]->Learn();
    }
}

void __fastcall TLayer::setErr(int index, double val)
{
    n[index]->Err = val;
}

double __fastcall TLayer::getErr(int index)
{
    return n[index]->Err;
}


int __fastcall TLayer::getCount()
{
    return n.size();
}


#pragma package(smart_init)
