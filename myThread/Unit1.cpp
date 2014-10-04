//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "TmyThread.h"
#include "TmyUnpackThread.h"
#include <jpeg.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TJPEGImage* jpg;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    myThreadShow = new TmyThreadShow(Image1);
    myThreadShow->LoadFile("S:\\IMG_5733.JPG");
    myThreadShow->LoadFile("S:\\IMG_5435.JPG");
    myThreadShow->ShowFile("S:\\IMG_5733.JPG");
return;

    Init();
    LoadFile("S:\\IMG_5733.JPG");
    LoadFile("S:\\IMG_5435.JPG");
//    ShowFile("S:\\IMG_5733.JPG");

return;

    CurrentImage = new TImage(Application);
    NextImage = new TImage(Application);
    SetImageSize(Image1->Width, Image1->Height);
    this->LoadCurrentImage("S:\\IMG_5733.JPG");
    this->LoadNextImage("S:\\IMG_5435.JPG");
    this->ShowCurrentImage(Image1);
return;
                                 
    TmyThread* myThread = new TmyThread(true, "S:\\IMG_5733.JPG", Image1);
//    myThread->OnTerminate = myTerminate;
    myThread->Resume();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SetImageSize(int Width, int Height)
{
    CurrentImage->Width = Width;
    CurrentImage->Height = Height;
    NextImage->Width = Width;
    NextImage->Height = Height;
}


void __fastcall TForm1::LoadCurrentImage(AnsiString FileName)
{
    if (CurrentFileName==FileName) return;
    if (NextFileName==FileName) {
        CurrentImage->Picture->Bitmap->Assign( NextImage->Picture->Bitmap);
        CurrentFileName = FileName;
        return;
    }
    CurrentFileName = FileName;
    TmyThread* myThread = new TmyThread(true, FileName, CurrentImage);
    myThread->OnTerminate = OnCurrentImageLoaded;
    isCurrentImageLoaded = false;
    myThread->Resume();
}


void __fastcall TForm1::LoadNextImage(AnsiString FileName)
{
    if (NextFileName==FileName) return;
    if (CurrentFileName==FileName) {
        NextImage->Picture->Bitmap->Assign( CurrentImage->Picture->Bitmap);
        NextFileName = FileName;
        return;
    }
    NextFileName = CurrentFileName;

    TmyThread* myThread = new TmyThread(true, FileName, NextImage);
    myThread->OnTerminate = OnNextImageLoaded;
    isNextImageLoaded = false;
    myThread->Resume();
}


void __fastcall TForm1::OnCurrentImageLoaded(TObject *Sender)
{
    isCurrentImageLoaded = true;
}

void __fastcall TForm1::OnNextImageLoaded(TObject *Sender)
{
    isNextImageLoaded = true;
}


void __fastcall TForm1::ShowCurrentImage(TImage* img)
{
    while (!CurrentFileName.IsEmpty() && !isCurrentImageLoaded) {
        Application->ProcessMessages();
        Sleep(100);
    }
    img->Picture->Bitmap->Assign(CurrentImage->Picture->Bitmap);
}


void __fastcall TForm1::ShowNextImage(TImage* img)
{
    while (!NextFileName.IsEmpty() && !isNextImageLoaded) {
        Application->ProcessMessages();
        Sleep(100);
    }
    img->Picture->Bitmap->Assign(NextImage->Picture->Bitmap);
}


void __fastcall TForm1::myTerminate(TObject *Sender)
{
    TmyUnpackThread* myThread = new TmyUnpackThread(true, Image1, jpg);
    myThread->Resume();
}


void __fastcall TForm1::_GetBitmap(TImage* img)
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



//---------------------------------------------------------------------------


void __fastcall TForm1::Init()
{
    for (int I = 0; I < MAX_CACHED_SIZE; I++) {
        CachedFiles.push_back(0);
    }
}


void __fastcall TForm1::LoadFile(AnsiString FileName)
{
    for (int I = 0; I < MAX_CACHED_SIZE; I++) {
        if ( CachedFiles[I] == 0) continue;
        if (CachedFiles[I]->FileName==FileName) {
            if (I != 0) {
                swap( CachedFiles[0], CachedFiles[I]);
            }
            return;
        }
    }

    if (CachedFiles[MAX_CACHED_SIZE-1] != 0) {
        delete CachedFiles[MAX_CACHED_SIZE-1];
        CachedFiles[MAX_CACHED_SIZE-1] = 0;
    }

    for (int I = MAX_CACHED_SIZE-1; I>0; I--) {
        CachedFiles[I] = CachedFiles[I-1];
    }
    CachedFiles[0] = 0;
    CachedFiles[0] = new TmyThreadFile(FileName, 800, 600);
}


void __fastcall TForm1::ShowFile(AnsiString FileName)
{
    for (int I = 0; I < MAX_CACHED_SIZE; I++) {
        if ( CachedFiles[I] == 0) continue;
        if (CachedFiles[I]->FileName!=FileName) continue;
        CachedFiles[I]->ShowImage(Image1);
        return;
    }
}


void __fastcall TForm1::Image1Click(TObject *Sender)
{
    if (random(2)==0) {
        myThreadShow->ShowFile("S:\\IMG_6344.JPG");
    }
    else {
        myThreadShow->ShowFile("S:\\IMG_5435.JPG");
    }
return;

    ShowFile("S:\\IMG_5733.JPG");
return;
    this->ShowNextImage(Image1);
}


void __fastcall TForm1::Image1DblClick(TObject *Sender)
{
    myThreadShow->ShowFile("S:\\IMG_5733.JPG");
return;
    ShowFile("S:\\IMG_5435.JPG");

}
//---------------------------------------------------------------------------

