//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
map<int,bool>m210;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    AnsiString S = "1,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,121,127,131,137,139,143,149,151,157,163,167,169,173,179,181,187,191,193,197,199,209,";
    while (S.Pos(",")>0) {
        AnsiString SS = S.SubString(1,S.Pos(",")-1);
        S = S.SubString(S.Pos(",")+1, S.Length());
        m210[SS.ToInt()]=true;
    }
}
//---------------------------------------------------------------------------



bool isSimple(unsigned int X)
{
    int m=X%210;
    if (m210[m]==false) return false;
    for (unsigned int I = 2; I < X; I++) {
        if ((X % I)==0) return false;
    }
    return true;
}

void __fastcall TForm1::FormDblClick(TObject *Sender)
{
    unsigned int X = 0;
    for (unsigned int X = 0; X < 1000000; X++) {
        p.push_back(isSimple(X));
        if (p[X-1]) Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    int sWhite = 0;
    for (int I = 0; I<X; I++) {
        if (Canvas->Pixels[I][Y]>0) sWhite++;
    }
    Caption = String(sWhite);
    return;
    unsigned int XX = Y*this->ClientWidth + X;
    Caption = String(XX) + " "+ String(s[X])+" " +((Canvas->Pixels[X][Y]==0)?" black ":" white ") + (isSimple(XX)?String(" - SIMPLE "):String(" "));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
    Caption = String(this->ClientWidth);

        Canvas->Brush->Color = clBlack;
        Canvas->FillRect(TRect(0,0,this->ClientWidth,this->ClientHeight));
        unsigned int X = 0;
        int ss = p.size()/this->ClientWidth-this->ClientHeight;
        if (ss<0) ss = 0;
        X = ss*this->ClientWidth;

        Canvas->Pen->Color = clLime;
        for (int I = 0; I < this->ClientHeight; I++) {
            int sWhite = 0;
            for (int T = 0; T < this->ClientWidth; T++) {
                if (I==0) s[T]=0;
                if (X>=p.size()) continue;
                if (p[X++]) {
                    Canvas->Pixels[T][I]=clWhite;
                    s[T] = s[T]+1;
                    sWhite++;
                }
                else Canvas->Pixels[T][I]=0;
            }
            Canvas->LineTo(sWhite,I);
        }

        Canvas->Pen->Color = clYellow;
        int c = 0;
        Edit1->Text = "";
        for (int T = 0; T < this->ClientWidth; T++) {
            int y = s[T];
            if (y>0) {
                Canvas->LineTo(T,y);
                c++;
                Edit1->Text = Edit1->Text + String(T) + ",";
            }
        }
        Caption = String(c);

//
//    Caption = String(this->ClientWidth);
//    for (int J = 0; J < 50; J++) {
//        unsigned int X = 0;
//        for (int I = 0; I < 20; I++) {
//            for (int T = 0; T < this->ClientWidth-J; T++) {
//                if (X>=p.size()) return;
//                if (p[X++]) Canvas->Pixels[T][I+J*20]=clWhite;
//                else Canvas->Pixels[T][I+J*20]=0;
//            }
//        }
//    }
}
//---------------------------------------------------------------------------
