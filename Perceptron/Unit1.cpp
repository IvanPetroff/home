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
TGrid myGrid(2,256,256);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        for (int T = 0; T < myPers.cnt_lay; T++) {
            myPers.DrawLinks(Form1->Canvas, TRect(200+T*200,200,300+T*200,300),T);
            myPers.DrawLayer(Form1->Canvas, TRect(300+T*200,200,400+T*200,300),T+1);
        }
return;

    TPoint p = Mouse->CursorPos;
    p.x++;
    Mouse->CursorPos = p;

    HDC hdc;
    Cardinal Color;
    hdc = GetWindowDC(0);
    for (int x = p.x-20; x<p.x+20; x++) {
        for (int y = p.y-20; y<p.y+20; y++) {
            Color = GetPixel(hdc, x, y);
            Form1->Canvas->Pixels[x][y] = Color;
        }
    }
    ReleaseDC(0, hdc);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
    for (;;)
//    for (int I = 0; I < 10; I++)
    {
        int I = random(10);
//        Form1->Canvas->TextOut(0,I*20,IntToStr(I)+"   ");
        Form1->Canvas->Brush->Color = clBlack;
        Form1->Canvas->FillRect(TRect(0,I*20,16,I*20+16));
        ImageList1->Draw(Form1->Canvas,0,I*20,I,true);
        Application->ProcessMessages();
        int C = 0;
        for (int T = 0; T < 16; T++) {
            for (int J = 0; J < 16; J++) {
                double Col = Form1->Canvas->Pixels[T][J+I*20];
                double maxCol = RGB(255,255,255);
                if (Col > maxCol) Col = maxCol;
                Col = Col / maxCol;
                myGrid.in[C++] = Col;
            }
        }
        myGrid.Transfer();
        myGrid.DrawLayer(Form1->Canvas,0,200,I*20);
        myGrid.DrawLayer(Form1->Canvas,1,200+300,I*20);
        myGrid.DrawLayer(Form1->Canvas,2,200+300+300,I*20);
        Form1->Canvas->Brush->Color = clWhite;
        Form1->Canvas->TextOut(20,I*20,FloatToStr(myGrid.out[0]));
        myGrid.Learn(I/10.0);
    }
}
//---------------------------------------------------------------------------
