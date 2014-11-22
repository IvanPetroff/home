//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <fstream>
#include <streambuf>
#include <istream>
#include <memory>
#include <vector>
#include <string>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DataDriverEh"
#pragma link "TEditorBase"
#pragma link "TEditorGrid"
#pragma link "TEditAvto"
#pragma link "TEditSimple"
#pragma link "TFraBase"
#pragma link "TFraGasPoint"
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
    TmyQuery Q(db,"ALTER SESSION SET NLS_NUMERIC_CHARACTERS='.,'");
    Q->ExecSQL();


    FraGasPoint1->Init(db);
}























