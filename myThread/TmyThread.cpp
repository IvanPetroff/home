//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TmyThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit2::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TmyThread::TmyThread(bool CreateSuspended, AnsiString FileName, TImage* img)
    : TThread(CreateSuspended)
{
    this->FileName = FileName;
    this->FreeOnTerminate = true;
    this->img = img;
}
//---------------------------------------------------------------------------



void __fastcall TmyThread::Execute()
{
    //---- Place thread code here ----
    std::auto_ptr<TJPEGImage> jpg(new TJPEGImage);
    jpg->Performance = jpBestSpeed;
    jpg->Scale = 2;
    jpg->LoadFromFile(FileName);
    this->jpg = jpg.get();
    this->Synchronize( _GetBitmap);
}
//---------------------------------------------------------------------------


void __fastcall TmyThread::_GetBitmap()
{
//    if (Quality != l_jpg->Scale) l_jpg->Scale = Quality;
    std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap);
    Bitmap->Assign(jpg);

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
