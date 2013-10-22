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
    step = 1000000;
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
                double in_val;
                if (I==0) {
                    in_val = _in[in_index];
                }
                else {
                    in_val = _lay[I-1][in_index];
                }

                double val = _lay[I][T] + in_val * in_K;
//                if (val > 1) val=1;
//                else val = 0;
                val = 1/(1+exp(-0.1*val));
                _lay[I][T] = val;
            }
        }
    }

    out = 0;
    for (int I = 0; I < cnt_in; I++) {
        out = out + _lay[cnt_lay-1][I];
    }
    out = 1/(1+exp(-0.1*out));
}


void __fastcall TPers::Evol()
{
    int II = random(cnt_lay);
    int TT = random(cnt_in);
    int JJ = random(cnt_links);
    double w = _links[II][TT][JJ].second;
    double r = (random(step)-step)/((double)step);
    _links[II][TT][JJ].second = w+r;
return;

    for (int I = 0; I < cnt_lay; I++) {
//continue;
        for (int T = 0; T < cnt_in; T++) {
            for (int J = 0; J < cnt_links; J++) {
                _links[I][T][J].second = _links[I][T][J].second + (random(step)-step)/(double)step/1.0;
            }
        }
    }
}

void __fastcall TPers::DrawLinks(TCanvas* Canvas, TRect Rect, int lay_number)
{
    int size = sqrt(cnt_in);
    double min=0;
    double max=0;
    for (int II=0; II < 2; II++) {
        int cnt=0;
        for (int I = 0; I < size; I++) {
            for (int T = 0; T < size; T++) {
                TRect myRect( Rect.Left+Rect.Width()/size*I,
                              Rect.Top+Rect.Height()/size*T,
                              Rect.Left+Rect.Width()/size*(I+1),
                              Rect.Top+Rect.Height()/size*(T+1));

                for (int J = 0; J < cnt_links; J++) {
                    pair<int,double> myPair = _links[lay_number][cnt][J];
                    double C = myPair.second;
                    if (C<min) min=C;
                    if (C>max) max=C;
                    if (II==0) continue;
                    Canvas->Brush->Color = clWhite/(max-min)*C;

                    TRect mySubRect( myRect.Left+myRect.Width()/cnt_links*J,
                                     myRect.Top,
                                     myRect.Left+myRect.Width()/cnt_links*(J+1),
                                     myRect.Bottom);

                    Canvas->FillRect(mySubRect);
                }
                cnt++;
            }
        }
    }
}


void __fastcall TPers::DrawLayer(TCanvas* Canvas, TRect Rect, int lay_number)
{
    int size = sqrt(cnt_in);
    double min=0;
    double max=0;
    int cnt=0;
    for (int I = 0; I < size; I++) {
        for (int T = 0; T < size; T++) {
            double C = (lay_number==0)?in[cnt]:_lay[lay_number-1][cnt];
            cnt++;

            Canvas->Brush->Color = clWhite*C;
            TRect myRect( Rect.Left+Rect.Width()/size*I,
                          Rect.Top+Rect.Height()/size*T,
                          Rect.Left+Rect.Width()/size*(I+1),
                          Rect.Top+Rect.Height()/size*(T+1));
            Canvas->FillRect(myRect);
        }
    }
}

void __fastcall TPers::Fine(double targ)
{
//return;
    double old_delta = fabs(targ-out);
    vector< vector< vector<pair<int,double> > > > old_links = _links;
    Evol();
    Run();
//    if (old_delta < fabs(targ-out)) {
//        _links = old_links;
//        return;
//    }
//return;
    double new_delta = fabs(targ-out);
    while (old_delta < new_delta) {
        _links = old_links;
        Evol();
        Run();
        new_delta = fabs(targ-out);
    }
}


#pragma package(smart_init)
