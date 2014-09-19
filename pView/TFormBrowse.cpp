//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>
#include <jpeg.hpp>
#include <Graphics32.hpp>
#include "TFormBrowse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFraBase"
#pragma link "TFraImage"
#pragma resource "*.dfm"
TFormBrowse *FormBrowse;
//---------------------------------------------------------------------------
__fastcall TFormBrowse::TFormBrowse(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------






void TFormBrowse::foo()
{
//    TSearchRec sr;
//    int iAttributes = 0;
//    StringGrid1->RowCount = 1;
////    iAttributes |= faReadOnly * CheckBox1->Checked;
////    iAttributes |= faHidden * CheckBox2->Checked;
////    iAttributes |= faSysFile * CheckBox3->Checked;
////    iAttributes |= faVolumeID * CheckBox4->Checked;
////    iAttributes |= faDirectory * CheckBox5->Checked;
////    iAttributes |= faArchive * CheckBox6->Checked;
////    iAttributes |= faAnyFile * CheckBox7->Checked;
//    iAttributes = faAnyFile;
//    StringGrid1->RowCount = 0;
//    if (FindFirst(Edit1->Text, iAttributes, sr) == 0) {
//        do {
//            if ((sr.Attr & iAttributes) == sr.Attr) {
//                StringGrid1->RowCount = StringGrid1->RowCount + 1;
//                StringGrid1->Cells[1][StringGrid1->RowCount-1] = sr.Name;
//                StringGrid1->Cells[2][StringGrid1->RowCount-1] = IntToStr(sr.Size);
//            }
//        } while (FindNext(sr) == 0);
//        FindClose(sr);
//    }
}

void __fastcall TFormBrowse::FileListBox1Change(TObject *Sender)
{
    for (int I = 0; I < mas_preview.size(); I++) {
        delete mas_preview[I];
    }
    mas_preview.clear();

Caption = Caption + ".";
    std::auto_ptr<TJPEGImage> l_jpg(new TJPEGImage());
    l_jpg->Scale = jsEighth;
    std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap);
    int x = 0;
    int y = 0;
    int maxX = ScrollBox1->Width / (128+10);

    for (int I = 0; I < FileListBox1->Items->Count; I++) {
        TFraPreview* FraPreview = new TFraPreview(Application);
        TFraPreview::SelectedPreview = FraImage1;
        ScrollBox1->InsertControl( FraPreview);
        FraPreview->Left = 8+x*(FraPreview->Width+10) - ScrollBox1->HorzScrollBar->Position;
        FraPreview->Top = 8+y*(FraPreview->Height+10) - ScrollBox1->VertScrollBar->Position;
        FraPreview->pFileName->Caption = FileListBox1->Items->Strings[I];
        x++;
        if (x>=maxX) {
            x = 0;
            y++;
        }
        mas_preview.push_back(FraPreview);
    }


    for (int I = 0; I < FileListBox1->Items->Count; I++) {
        l_jpg->LoadFromFile(FileListBox1->Items->Strings[I]);
        l_jpg->DIBNeeded();
        Bitmap->Assign(l_jpg.get());

        TImage* img = mas_preview[I]->img;

        if (Bitmap->Width > Bitmap->Height) {
            double k = (double)Bitmap->Height / (double)Bitmap->Width;
            img->Picture->Bitmap->Width = img->Width;
            img->Picture->Bitmap->Height = img->Width * k;
        }
        else {
            double k = (double)Bitmap->Width / (double)Bitmap->Height;
            img->Picture->Bitmap->Height = img->Height;
            img->Picture->Bitmap->Width = img->Height * k;
        }

//        img->Picture->Bitmap->Width = img->Width;
//        img->Picture->Bitmap->Height = img->Height;
        SetStretchBltMode(img->Picture->Bitmap->Canvas->Handle, HALFTONE);

        StretchBlt(img->Picture->Bitmap->Canvas->Handle, // приемник
        0, 0, // координаты верхнего угла приемника
        img->Picture->Bitmap->Width, img->Picture->Bitmap->Height,
        Bitmap->Canvas->Handle, // исходник
        0, 0, // координаты верхнего угла исходника
        Bitmap->Width, Bitmap->Height,
        SRCCOPY);

        Sleep(10);
        Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormBrowse::ScrollBox1MouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
ShowMessage(__FUNC__);
}
//---------------------------------------------------------------------------

void __fastcall TFormBrowse::ScrollBox1MouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
ShowMessage(__FUNC__);
}
//---------------------------------------------------------------------------

void __fastcall TFormBrowse::ScrollBox1MouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
ShowMessage(__FUNC__);
    
}
//---------------------------------------------------------------------------

