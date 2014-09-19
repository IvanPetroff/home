//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFormImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFraBase"
#pragma link "TFraImage"
#pragma resource "*.dfm"
TFormImage *FormImage;
//---------------------------------------------------------------------------
__fastcall TFormImage::TFormImage(TComponent* Owner)
    : TForm(Owner)
{
//    this->DoubleBuffered = true;
}
//---------------------------------------------------------------------------



void __fastcall TFormImage::LoadImage(AnsiString FileName)
{
    this->FraImage1->LoadImage(FileName);
//    Timer1->Enabled = true;
}


void __fastcall TFormImage::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;
    this->FraImage1->ShowImage(1);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::FormKeyPress(TObject *Sender, char &Key)
{
    if (Key==VK_ESCAPE) {
        Application->Terminate();
    }
}
//---------------------------------------------------------------------------

