//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFraBase"
#pragma resource "*.dfm"
TFraImage *FraImage;
//---------------------------------------------------------------------------
__fastcall TFraImage::TFraImage(TComponent* Owner)
    : TFraBase(Owner)
{
    this->DoubleBuffered = true;
}
//---------------------------------------------------------------------------

__fastcall TFraImage::~TFraImage()
{
}


void __fastcall TFraImage::LoadJpeg()
{
}


void __fastcall TFraImage::FastShowImage(int Q)
{
}

void __fastcall TFraImage::ShowImage(int Q)
{
}

void __fastcall TFraImage::LoadImage(AnsiString inFileName)
{
}

