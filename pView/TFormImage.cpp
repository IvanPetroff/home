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
    FraImage1->OnResize = TFormImage::FormResize;

    myThreadShow.reset(new TmyThreadShow(0));
    myThreadShow->SetImage(FraImage1->img);
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

void __fastcall TFormImage::LoadNextFile()
{
    for (int I = 0; I < CNT_PRELOAD_FILES; I++) {
        if (FileListBox1->ItemIndex < (FileListBox1->Items->Count-1-I)) {
            AnsiString FileName = FileListBox1->Directory;
            if (FileListBox1->Directory.SubString(FileListBox1->Directory.Length(),1) != "\\") {
                FileName = FileName + "\\";
            }
            FileName = FileName + FileListBox1->Items->Strings[FileListBox1->ItemIndex+1+I];
            myThreadShow->LoadFile( FileName, (I==0)?tpLowest:tpIdle);
        }
    }
}


void __fastcall TFormImage::LoadPrevFile()
{
    for (int I = 0; I < CNT_PRELOAD_FILES; I++) {
        if (FileListBox1->ItemIndex >(0+I)) {
            AnsiString FileName = FileListBox1->Directory;
            if (FileListBox1->Directory.SubString(FileListBox1->Directory.Length(),1) != "\\") {
                FileName = FileName + "\\";
            }
            FileName = FileName + FileListBox1->Items->Strings[FileListBox1->ItemIndex-1-I];
            myThreadShow->LoadFile( FileName, (I==0)?tpLowest:tpIdle);
        }
    }
}


void __fastcall TFormImage::LoadImage(AnsiString inFileName)
{
    LoadFileListBox(inFileName);
//ShowMessage(String(__FUNC__) + " " + FileListBox1->FileName);
    myThreadShow->ShowFile( FileListBox1->FileName);
    LoadNextFile();
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::ShowImage(AnsiString FileName)
{
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::NextFile()
{
    FileListBox1->ItemIndex++;
//ShowMessage(String(__FUNC__) + " " + FileListBox1->FileName);
    myThreadShow->ShowFile( FileListBox1->FileName);
    LoadNextFile();
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::PrevFile()
{
    if ( FileListBox1->ItemIndex==0) return;
    FileListBox1->ItemIndex--;
//ShowMessage(String(__FUNC__) + " " + FileListBox1->FileName);
    myThreadShow->ShowFile( FileListBox1->FileName);
    LoadPrevFile();
}
//---------------------------------------------------------------------------


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


void __fastcall TFormImage::FormResize(TObject *Sender)
{
    myThreadShow->SetImage(FraImage1->img);
    LoadNextFile();
    LoadPrevFile();
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    myThreadShow->Terminate();
}
//---------------------------------------------------------------------------


