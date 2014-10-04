//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TmyThreadFile.h"
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

__fastcall TmyThreadFile::TmyThreadFile(AnsiString inFileName, int inSizeX, int inSizeY)
    : TThread(false)
{
    FileName = inFileName;
    cFileName = FileName.c_str(); // иначе AnsiString неадекватно себя ведёт даже в пределах одного класса
    SizeX = inSizeX;
    SizeY = inSizeY;
    isComplete = false;
    Bitmap.reset(new Graphics::TBitmap);
    Bitmap->Width = SizeX;
    Bitmap->Height = SizeY;
    this->Priority = tpLower;
}
//---------------------------------------------------------------------------
void __fastcall TmyThreadFile::Execute()
{
    //---- Place thread code here ----
    std::auto_ptr<TJPEGImage> jpg(new TJPEGImage);
    this->jpg = jpg.get();
    this->Synchronize( _LoadFile);
    this->Synchronize( _GetBitmap);
    isComplete = true;
}
//---------------------------------------------------------------------------

void __fastcall TmyThreadFile::_LoadFile()
{
    jpg->Performance = jpBestSpeed;
    jpg->Scale = 2;
    jpg->LoadFromFile(cFileName);
    jpg->DIBNeeded();

}


void __fastcall TmyThreadFile::ShowImage(TImage* toImg)
{
    while (!isComplete) {
        Application->ProcessMessages();
        Sleep(100);
    }
    toImg->Picture->Bitmap->Assign(Bitmap.get());
//    toImg->Picture->Bitmap->Canvas->Draw(0,0, Bitmap.get());
}



void __fastcall TmyThreadFile::_GetBitmap()
{
//    if (Quality != l_jpg->Scale) l_jpg->Scale = Quality;
    std::auto_ptr<Graphics::TBitmap> tmpBitmap(new Graphics::TBitmap);
    tmpBitmap->Assign(jpg);

    int myWidth = Bitmap->Width;
    int myHeight = Bitmap->Height;

    if (tmpBitmap->Width > tmpBitmap->Height) {
        double k = (double)tmpBitmap->Height / (double)tmpBitmap->Width;
        myHeight = Bitmap->Width * k;
        if (myHeight > Bitmap->Height) {
            myHeight = Bitmap->Height;
            myWidth = Bitmap->Height / k;
        }
    }
    else {
        double k = (double)tmpBitmap->Width / (double)tmpBitmap->Height;
        myWidth = Bitmap->Height * k;
        if ( myWidth > Bitmap->Width) {
            myWidth = Bitmap->Width;
            myHeight = Bitmap->Width / k;
        }
    }

    Bitmap->Canvas->Brush->Color = clBlack;
    Bitmap->Canvas->FillRect(TRect( 0, 0, Bitmap->Width, Bitmap->Height));

    SetStretchBltMode( Bitmap->Canvas->Handle, HALFTONE);

    StretchBlt(
        Bitmap->Canvas->Handle, // приемник
        (Bitmap->Width - myWidth)/2, (Bitmap->Height - myHeight) / 2, // координаты верхнего угла приемника
        myWidth, myHeight,
        tmpBitmap->Canvas->Handle, // исходник
        0, 0, // координаты верхнего угла исходника
        tmpBitmap->Width, tmpBitmap->Height,
        SRCCOPY
    );
}