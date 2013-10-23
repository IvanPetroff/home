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
        int NeyronNumber = (Layer.size()==s.size())?I:random(Layer.size());
        sn[I] = NeyronNumber;
        s[I] = Layer[NeyronNumber];
        s[I]->bs.push_back(this);
    }
}


__fastcall TNeyron::TNeyron(int cnt_inputs, vector<TNeyron*> &Layer)
{
    w.resize(cnt_inputs);
    s.resize(cnt_inputs);
    sn.resize(cnt_inputs);
    InitWeights();
    InitSinaps(Layer);
}


__fastcall TNeyron::TNeyron(TIniFile* F, AnsiString SectionName, vector<TNeyron*> &Layer)
{
    int cnt_inputs = F->ReadInteger( SectionName, "SYNAPSES", 0);
    w.resize(cnt_inputs);
    s.resize(cnt_inputs);
    sn.resize(cnt_inputs);
    LoadWeights(F, SectionName);
    LoadSynapses(F, SectionName, Layer);
}


void __fastcall TNeyron::LoadSynapses(TIniFile* F, AnsiString SectionName, vector<TNeyron*> &Layer)
{
    for (int I = 0; I < s.size(); I++) {
        int NeyronNumber = F->ReadInteger( SectionName, "SYNAPS_"+String(I), 0);
        sn[I] = NeyronNumber;
        s[I] = Layer[NeyronNumber];
        s[I]->bs.push_back(this);
    }
}


void __fastcall TNeyron::LoadWeights(TIniFile* F, AnsiString SectionName)
{
    for (int I = 0; I < w.size(); I++) {
        w[I] = F->ReadFloat( SectionName, "WEIGHT_"+String(I), 0);
    }
}


void __fastcall TNeyron::Save(TIniFile* F, AnsiString SectionName)
{
    F->WriteInteger( SectionName, "SYNAPSES", s.size());
    for (int I = 0; I < s.size(); I++) {
        F->WriteInteger( SectionName, "SYNAPS_"+String(I), sn[I]);
        F->WriteFloat( SectionName, "WEIGHT_"+String(I), w[I]);
    }
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
            double kLearn = (random(1000)+1)/1000.0;
            posl->w[T] = posl->w[T] + kLearn * posl->Err * out;
        }
    }
}




#pragma package(smart_init)
