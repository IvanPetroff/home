//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TPers.h"

//---------------------------------------------------------------------------
void __fastcall TPers::Init()
{
    _in.resize(cnt_in);
    _lay.resize(cnt_lay);

    _links.resize(cnt_lay);

    for (int I = 0; I < cnt_lay; I++) {
        _lay[I].resize(cnt_in);
        _links[I].resize(cnt_in);
        for (int T = 0; T < cnt_in; T++) {
            _links[I][T].resize(cnt_links);
            for (int J = 0; J < cnt_links; J++) {
                pair <int,double> myPair(random(cnt_in),random(1000)/1000.0);
                _links[I][T][J] = myPair;
            }
        }
    }
}

__fastcall TPers::TPers(int cnt_in, int cnt_lay, int cnt_links)
{
    this->cnt_in = cnt_in;
    this->cnt_lay = cnt_lay;
    this->cnt_links = cnt_links;
    step = 1000;
    Init();
}

double __fastcall TPers::_get_in(int index)
{
    return _in[index];
}

void __fastcall TPers::_set_in(int index, double val)
{
    _in[index] = val;
}


void __fastcall TPers::Run()
{
    for (int I = 0; I < cnt_lay; I++) {
        for (int T = 0; T < cnt_in; T++) {
            _lay[I][T] = 0;
            for (int J = 0; J < cnt_links; J++) {
                pair <int,double> myPair = _links[I][T][J];
                int in_index = myPair.first;
                double in_K = myPair.second;
                double in_val = (I==0)?_in[in_index]:_lay[I-1][in_index];
                _lay[I][T] = _lay[I][T] + in_val * in_K;
            }
        }
    }

    out = 0;
    for (int I = 0; I < cnt_in; I++) {
        out = out + _lay[cnt_lay-1][I];
    }
}


void __fastcall TPers::Evol()
{
    for (int I = 0; I < cnt_lay; I++) {
        for (int T = 0; T < cnt_in; T++) {
            for (int J = 0; J < cnt_links; J++) {
                _links[I][T][J].second = _links[I][T][J].second + (random(step)-step)/(double)step/10000.0;
            }
        }
    }
}

void __fastcall TPers::Fine(double targ)
{
    double old_delta = fabs(targ-out);
    vector< vector< vector<pair<int,double> > > > old_links = _links;
    Evol();
    Run();
    if (old_delta < fabs(targ-out)) {
        _links = old_links;
        return;
    }
return;
    while (old_delta < fabs(targ-out)) {
        Evol();
        Run();
    }
}


#pragma package(smart_init)
