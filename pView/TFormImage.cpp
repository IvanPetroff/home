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
    myThreadShow.reset(new TmyThreadShow(0));
    myThreadShow->SetImage(FraImage1->img);
//    myThreadShow->ShowFile(sCmd);
return;
    imgThread.reset( new TImgThread);
    imgThreadPrev.reset( new TImgThread);
    imgThreadNext.reset( new TImgThread);
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::LoadFileListBox(AnsiString inFileName)
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
//---------------------------------------------------------------------------


void __fastcall TFormImage::LoadImage(AnsiString inFileName)
{
    myThreadShow->ShowFile(inFileName);

return;
    Timer1->Enabled = false;
//    if (inFileName != FileName) {
//        imgThread->Terminate();
//        delete imgThread.get();
//        imgThread.reset( new TImgThread);
//    }
    FileName = inFileName;

    imgThread->LoadJpegFile(FileName, 3);
//    LoadListBox(inFileName);
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::ShowImage(TImgThread* imgThread)
{
    imgThread->GetBitmap(this->FraImage1->img, 3);
    this->FraImage1->pFileName->Caption = imgThread->FileName;
//    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::Timer1Timer(TObject *Sender)
{
return;
    Timer1->Enabled = false;
    imgThread->GetBitmap(this->FraImage1->img,1);
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::NextFile()
{
    FileListBox1->ItemIndex++;

    TImgThread* tmpImg = imgThread.release();
    imgThread.reset(imgThreadNext.release());
    imgThreadNext.reset(tmpImg);

//    LoadImage( FileListBox1->FileName, imgThreadNext.get());
//    ShowImage( imgThread);
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::PrevFile()
{
    if ( FileListBox1->ItemIndex==0) return;
    FileListBox1->ItemIndex--;
//    LoadImage( FileListBox1->FileName);
//    ShowImage( imgThread);
}
//---------------------------------------------------------------------------


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
    myThreadShow->SetImage(FraImage1->img);
//    imgThread->GetBitmap(this->FraImage1->img,3);
//    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    myThreadShow->Terminate();
//    imgThread->Terminate();
}
//---------------------------------------------------------------------------

