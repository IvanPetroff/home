//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "TPers.h"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

TPers myPers(100,2,3);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
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
    for (int I = 0; I < 10; I++) {
        ImageList1->Draw(Form1->Canvas,0,I*20,I,true);
        Application->ProcessMessages();
        int C = 0;
        for (int T = 0; T < 10; T++) {
            for (int J = 0; J < 10; J++) {
                double Col = Form1->Canvas->Pixels[T][J+I*20];
                double maxCol = RGB(255,255,255);
                if (Col > maxCol) Col = 0;
                myPers.in[C++] = Col / maxCol;
            }
        }
        myPers.Run();
        Form1->Canvas->TextOut(20,I*20,FloatToStr(myPers.out));
        myPers.Fine(I);
    }
}
//---------------------------------------------------------------------------
