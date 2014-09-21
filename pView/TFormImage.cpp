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
    imgThread.reset( new TImgThread(true));
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::LoadListBox(AnsiString inFileName)
{
    AnsiString FileName = ExtractFileName(inFileName).UpperCase();
    FileListBox1->Directory = ExtractFileDir(inFileName);
    for (int I = 0; I < FileListBox1->Items->Count; I++) {
        if (FileListBox1->Items->Strings[I].UpperCase()==FileName) {
            FileListBox1->ItemIndex = I;
            break;
        }
    }
}


void __fastcall TFormImage::LoadImage(AnsiString inFileName)
{
    Timer1->Enabled = false;
    if (inFileName != FileName) {
        imgThread->Terminate();
        delete imgThread.get();
        imgThread.reset( new TImgThread(true));
    }
    FileName = inFileName;

    this->FraImage1->pFileName->Caption = inFileName;
    imgThread->LoadJpeg(FileName, 3);
    imgThread->GetBitmap(this->FraImage1->img, 3);
    Timer1->Enabled = true;
    LoadListBox(inFileName);
}


void __fastcall TFormImage::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;
    imgThread->GetBitmap(this->FraImage1->img,1);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::NextFile()
{
    FileListBox1->ItemIndex++;
    LoadImage( FileListBox1->FileName);
}

void __fastcall TFormImage::PrevFile()
{
    if ( FileListBox1->ItemIndex==0) return;
    FileListBox1->ItemIndex--;
    LoadImage( FileListBox1->FileName);
}


void __fastcall TFormImage::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_ESCAPE) {
        imgThread->Terminate();
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



void __fastcall TFormImage::FormResize(TObject *Sender)
{
    imgThread->GetBitmap(this->FraImage1->img,3);
    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    imgThread->Terminate();
}
//---------------------------------------------------------------------------

