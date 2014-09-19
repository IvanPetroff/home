//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraPreview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFraPreview *FraPreview;
//---------------------------------------------------------------------------
__fastcall TFraPreview::TFraPreview(TComponent* Owner)
    : TFrame(Owner)
{
    Width = 136;
    Height = 128;
    Name = "FraPreview_"+String((int)this);
    pFileName->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TFraPreview::imgDblClick(TObject *Sender)
{
    CheckBox1->Checked = !CheckBox1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFraPreview::imgClick(TObject *Sender)
{
    if (Selected != 0) {
        Selected->Shape1->Pen->Width = 1;
        Selected->Shape1->Pen->Color = clGray;
    }
    Selected = this;
    Selected->Shape1->Pen->Width = 3;
    Selected->Shape1->Pen->Color = clLime;
    Application->ProcessMessages();
    SelectedPreview->LoadImage(pFileName->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TFraPreview::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;
    if (Selected == 0) return;

    std::auto_ptr<TJPEGImage> l_jpg(new TJPEGImage());
    l_jpg->Scale = 0;
    l_jpg->LoadFromFile(Selected->pFileName->Caption);
    Application->ProcessMessages();
    l_jpg->DIBNeeded();
    Application->ProcessMessages();
//    SelectedPreview->Picture->Bitmap->Assign(l_jpg.get());
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------

