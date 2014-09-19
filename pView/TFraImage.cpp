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
    l_jpg = new TJPEGImage();
    this->DoubleBuffered = true;
}
//---------------------------------------------------------------------------

__fastcall TFraImage::~TFraImage()
{
    delete l_jpg;
}


void __fastcall TFraImage::LoadJpeg()
{
    l_jpg->Scale = 1;
    l_jpg->LoadFromFile(FileName);
    l_jpg->DIBNeeded();
}


void __fastcall TFraImage::FastShowImage(int Q)
{
//ShowMessage(__FUNC__);
    if (FileName.IsEmpty()) return;
    if ( Q >= 0 ) {
        l_jpg->Scale = Q;
    }
    img->Stretch = true;
    img->Picture->Bitmap->Assign(l_jpg);
    Repaint();
}

void __fastcall TFraImage::ShowImage(int Q)
{
    if (FileName.IsEmpty()) return;
    if ( Q >= 0 ) {
        l_jpg->Scale = Q;
    }
    if (img->Stretch) img->Stretch = false;

    std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap);
    Bitmap->Assign(l_jpg);

    int myWidth = img->Width;
    int myHeight = img->Height;
    img->Picture->Bitmap->Width = img->Width;
    img->Picture->Bitmap->Height = img->Height;

    if (Bitmap->Width > Bitmap->Height) {
        double k = (double)Bitmap->Height / (double)Bitmap->Width;
        myHeight = img->Width * k;
        if (myHeight > img->Height) {
            myHeight = img->Height;
            myWidth = img->Height / k;
        }
    }
    else {
        double k = (double)Bitmap->Width / (double)Bitmap->Height;
        myWidth = img->Height * k;
        if ( myWidth > img->Width) {
            myWidth = img->Width;
            myHeight = img->Width / k;
        }
    }

    img->Picture->Bitmap->Canvas->Brush->Color = clBlack;
    img->Picture->Bitmap->Canvas->FillRect(TRect(0,0,img->Width,img->Height));

    SetStretchBltMode(img->Picture->Bitmap->Canvas->Handle, HALFTONE);

    StretchBlt(
        img->Picture->Bitmap->Canvas->Handle, // приемник
        (img->Width - myWidth)/2, (img->Height - myHeight) / 2, // координаты верхнего угла приемника
        myWidth, myHeight,
        Bitmap->Canvas->Handle, // исходник
        0, 0, // координаты верхнего угла исходника
        Bitmap->Width, Bitmap->Height,
        SRCCOPY
    );
}

void __fastcall TFraImage::LoadImage(AnsiString inFileName)
{
    FileName = inFileName;
    pFileName->Caption = inFileName;
    LoadJpeg();
}
void __fastcall TFraImage::FrameResize(TObject *Sender)
{
    ShowImage(-1);
}
//---------------------------------------------------------------------------
