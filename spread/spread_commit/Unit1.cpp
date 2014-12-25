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
        db->Username;
        db->Password;
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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    OraQuery1->ParamByName("1")->AsString = Edit1->Text;
    OraQuery1->Open();
    

}
//---------------------------------------------------------------------------
