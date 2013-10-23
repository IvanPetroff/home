//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "TPers.h"
#include "TGrid.h"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

TPers myPers(100,1,20);
TGrid* myGrid=0;
bool flg_go = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    dop.resize(10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    if (myGrid==0) return;
    if (PageControl1->ActivePage->Name != "TS_Test") return;

    TPoint p = Mouse->CursorPos;
//    p.x++;
//    Mouse->CursorPos = p;

    HDC hdc;
    Cardinal Color;
    hdc = GetWindowDC(0);
    for (int x = p.x-8; x<p.x+8; x++) {
        for (int y = p.y-8; y<p.y+8; y++) {
            Color = GetPixel(hdc, x, y);
            PB_Test->Canvas->Pixels[x - (p.x-8)][y - (p.y-8)] = Color;
        }
    }
    ReleaseDC(0, hdc);

    int C = 0;
    for (int T = 0; T < 16; T++) {
        for (int J = 0; J < 16; J++) {
            double Col = PB_Test->Canvas->Pixels[T][J];
            double maxCol = RGB(255,255,255);
            if (Col > maxCol) Col = maxCol;
            Col = Col / maxCol;
            myGrid->in[C++] = Col;
        }
    }
    myGrid->Transfer();
    myGrid->DrawLayer(PB_Test->Canvas,0,200,20);
    myGrid->DrawLayer(PB_Test->Canvas,1,200+300,20);
    myGrid->DrawLayer(PB_Test->Canvas,2,200+300+300,20);
    PB_Test->Canvas->Brush->Color = clWhite;
    PB_Test->Canvas->TextOut(20,20,FloatToStr(myGrid->out[0]));
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
//    for (;;)
//    for (int I = 0; I < 10; I++)
    flg_go = true;
    while (flg_go&&(PageControl1->ActivePage->Name == "TS_Learn"))
    {
        int I = random(20);
        if (I<10) {
            PaintBox1->Canvas->Brush->Color = clBlack;
            PaintBox1->Canvas->FillRect(TRect(0,I*20,16,I*20+16));
            ImageList1->Draw(PaintBox1->Canvas,0,I*20,I,true);
  //        Form1->Canvas->TextOut(0,I*20,IntToStr(I)+"   ");
            Application->ProcessMessages();
            int C = 0;
            for (int T = 0; T < 16; T++) {
                for (int J = 0; J < 16; J++) {
                    double Col = 0;
                    Col = PaintBox1->Canvas->Pixels[T][J+I*20];
                    double maxCol = RGB(255,255,255);
                    if (Col > maxCol) Col = maxCol;
                    Col = Col / maxCol;
                    myGrid->in[C++] = Col;
                }
            }
        }
        else {
            if (dop[I-10].size()==0) continue;
            int dop_index = random(dop[I-10].size());
            I = I - 10;
            int C=0;
            for (int T = 0; T < 16; T++) {
                for (int J = 0; J < 16; J++) {
                    myGrid->in[C] = dop[I][dop_index][C];
                    double maxCol = RGB(255,255,255);
                    PaintBox1->Canvas->Pixels[T][J+I*20] = myGrid->in[C]*maxCol;
                    C++;
                }
            }
        }
        myGrid->Transfer();
        myGrid->DrawLayer(PaintBox1->Canvas,0,200,I*20);
        myGrid->DrawLayer(PaintBox1->Canvas,1,200+300,I*20);
        myGrid->DrawLayer(PaintBox1->Canvas,2,200+300+300,I*20);
        PaintBox1->Canvas->Brush->Color = clWhite;
        PaintBox1->Canvas->TextOut(20,I*20,FloatToStr(myGrid->out[0]));
        myGrid->Learn(I/10.0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    myGrid->SaveToFile("s:\\grid.sav");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    flg_go = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    if (myGrid!=0) {
        delete myGrid;
        myGrid = 0;
    }
    myGrid = new TGrid("s:\\grid.sav");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
    if (myGrid!=0) {
        delete myGrid;
        myGrid = 0;
    }
    myGrid = new TGrid(2,256,5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    int index = String(Key).ToInt();
    int C = 0;

    vector<double> pix;
    pix.resize(256);
    for (int T = 0; T < 16; T++) {
        for (int J = 0; J < 16; J++) {
            double Col = PB_Test->Canvas->Pixels[T][J];
            double maxCol = RGB(255,255,255);
            if (Col > maxCol) Col = maxCol;
            Col = Col / maxCol;
            pix[C++] = Col;
        }
    }
    dop[index].push_back(pix);

}
//---------------------------------------------------------------------------

