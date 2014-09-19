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



void __fastcall TFormImage::LoadImage(AnsiString inFileName)
{
    this->FraImage1->LoadImage(inFileName);
    AnsiString FileName = ExtractFileName(inFileName).UpperCase();
    FileListBox1->Directory = ExtractFileDir(inFileName);
    for (int I = 0; I < FileListBox1->Items->Count; I++) {
        if (FileListBox1->Items->Strings[I].UpperCase()==FileName) {
            FileListBox1->ItemIndex = I;
            break;
        }
    }
//    Timer1->Enabled = true;
}


void __fastcall TFormImage::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;
    this->FraImage1->ShowImage(1);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::NextFile()
{
    FileListBox1->ItemIndex++;
    this->FraImage1->LoadImage( FileListBox1->FileName);
    this->FraImage1->OnResize(0);
}

void __fastcall TFormImage::PrevFile()
{
    if ( FileListBox1->ItemIndex==0) return;
    FileListBox1->ItemIndex--;
    this->FraImage1->LoadImage( FileListBox1->FileName);
    this->FraImage1->OnResize(0);
}


void __fastcall TFormImage::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_ESCAPE) {
        Application->Terminate();
    }
    if (Key==VK_SPACE || Key==VK_RIGHT) {
        NextFile();
    }
    if (Key==VK_BACK || Key==VK_LEFT) {
        PrevFile();
    }
}
//---------------------------------------------------------------------------

