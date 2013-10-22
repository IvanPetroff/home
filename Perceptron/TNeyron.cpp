//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TNeyron.h"

//---------------------------------------------------------------------------
void __fastcall TNeyron::InitWeights()
{
    for (int I = 0; I < w.size(); I++) {
        w[I] = (random(1000)-1000.0)/1000.0;
    }
}

void __fastcall TNeyron::InitSinaps(vector<TNeyron*> &Layer)
{
    for (int I = 0; I < s.size(); I++) {
        s[I] = (Layer.size()==s.size())?Layer[I]:Layer[random(Layer.size())];
        s[I]->bs.push_back(this);
    }
}


__fastcall TNeyron::TNeyron(int cnt_inputs, vector<TNeyron*> &Layer)
{
    w.resize(cnt_inputs);
    InitWeights();
    s.resize(cnt_inputs);
    InitSinaps(Layer);
}

void __fastcall TNeyron::Transfer()
{
    out = 0;
    for (int I = 0; I < s.size(); I++) {
        out = out + s[I]->out * w[I];
    }
    out = Activator(out);
}

double __fastcall TNeyron::Activator(double in)
{
    double out;
    out = 1/(1+exp(-0.01*in));
    return out;
}


void __fastcall TNeyron::CalcErr()
{
    if (bs.size()==0) return;
    double Sum = 0;

    for (int I = 0; I < bs.size(); I++) {
        TNeyron* posl = bs[I];
        for (int T = 0; T<posl->s.size(); T++) {
            if (posl->s[T] != this) continue;
            Sum = Sum + posl->Err * posl->w[T];
        }
    }
    Err = out * (1-out) * Sum;
}


void __fastcall TNeyron::Learn()
{
    for (int I = 0; I < bs.size(); I++) {
        TNeyron* posl = bs[I];
        for (int T = 0; T<posl->s.size(); T++) {
            if (posl->s[T] != this) continue;
            posl->w[T] = posl->w[T] + 1 * posl->Err * out;
        }
    }
}


#pragma package(smart_init)
