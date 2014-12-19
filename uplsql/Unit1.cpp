//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <memory>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "OdacVcl"
#pragma link "TFraLightRichEdit"
#pragma link "TFraListObjects"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    try {
        std::auto_ptr<TStringList> SL(new TStringList);
        SL->LoadFromFile("c:\\db_asu.txt");
        for (int I = 0; I < SL->Count; I++) {
            if (SL->Strings[I].SubString(1,1)=="#") continue;
            if (SL->Strings[I].UpperCase().Pos("TEM/")==0) continue;
            db->ConnectString = SL->Strings[I];
            break;
        }
        db->LoginPrompt = false;
        db->Options->Direct = true;
        Caption = Caption + " [" + db->Server.Trim() + "]";
    }
    catch (...) {
    }
    db->Connected = true;
    std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
    Q->SQL->Text = "ALTER SESSION SET NLS_NUMERIC_CHARACTERS='.,'";
    Q->ExecSQL();
    this->FraListObjects1->Init("TYPE");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoadText(AnsiString objName)
{
    std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
    Q->SQL->Text = "select * from all_source where name=:name and type='TYPE BODY' order by line";
    Q->ParamByName("name")->AsString = objName.UpperCase();
    this->FraLightRichEdit1->RichEdit1->Lines->Clear();
    AnsiString S = "";
    for (Q->Open(); !Q->Eof; Q->Next()) {
        S = S+Q->FieldByName("text")->AsString;
    }
    this->FraLightRichEdit1->RichEdit1->Text = S;
    this->FraLightRichEdit1->HighLight(0);

}


void __fastcall TForm1::FraListObjects1ListBox1Click(TObject *Sender)
{
    LoadText(this->FraListObjects1->ListBox1->Items->Strings[this->FraListObjects1->ListBox1->ItemIndex]);
}
//---------------------------------------------------------------------------

