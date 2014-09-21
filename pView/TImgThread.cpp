//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TImgThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TImgThread::TImgThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    l_jpg.reset(new TJPEGImage);
    flgRun = false;
}
//---------------------------------------------------------------------------
void __fastcall TImgThread::Execute()
{
    //---- Place thread code here ----
    while ( !this->Terminated) {
        if (cmd==CMD_LOAD) {
            this->Synchronize( _LoadJpeg);
        }
        if (cmd==CMD_BITMAP) {
            this->Synchronize( _GetBitmap);
        }
        cmd = 0;
        flgRun = false;
        Suspend();
    }
}
//---------------------------------------------------------------------------


void __fastcall TImgThread::_LoadJpeg()
{
    if (FileName.IsEmpty()) return;
    if (Quality >= 0) l_jpg->Scale = Quality;
    l_jpg->LoadFromFile(FileName);
    l_jpg->DIBNeeded();
}

void __fastcall TImgThread::_SetLoadCmd()
{
    cmd = CMD_LOAD;
}

void __fastcall TImgThread::_SetBitmapCmd()
{
    cmd = CMD_BITMAP;
}

void __fastcall TImgThread::LoadJpeg(AnsiString inFileName, int inQuality)
{
    while (!this->Suspended  || flgRun) {}
    FileName = inFileName;
    Quality = inQuality;
    this->Synchronize( _SetLoadCmd);
    flgRun = true;
    this->Resume();
}

void __fastcall TImgThread::GetBitmap(TImage* inImage, int inQuality)
{
    while (!this->Suspended || flgRun) {
        Application->ProcessMessages();
    }
    img = inImage;
    if (inQuality>=0) {
        Quality = inQuality;
    }
    this->Synchronize( _SetBitmapCmd);
    flgRun = true;
    this->Resume();
}

void __fastcall TImgThread::_GetBitmap()
{
    if (FileName.IsEmpty()) {
        return;
    }

    std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap);
    if (Quality != l_jpg->Scale) l_jpg->Scale = Quality;
    Bitmap->Assign(l_jpg.get());

    int myWidth = img->Width;
    int myHeight = img->Height;
    while (img->Width==0 || img->Height==0) {
        Application->ProcessMessages();
    }
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
