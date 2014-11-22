//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraTankGasolineList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFraBase"
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma resource "*.dfm"
TFraTankGasolineList *FraTankGasolineList;
//---------------------------------------------------------------------------
__fastcall TFraTankGasolineList::TFraTankGasolineList(TComponent* Owner)
        : TFraBase(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFraTankGasolineList::Init(TOraSession* in_db)
{
    db = in_db;
    Query->Session = db;
}



void __fastcall TFraTankGasolineList::Load(AnsiString SKL)
{
    vTanks.clear();
    Query->ParamByName("skl")->AsString = SKL;
    for (Query->Open(); !Query->Eof; Query->Next()) {
        CB->Items->Add( Query->FieldByName("txt")->AsString);
        map<AnsiString,AnsiString> m;
        m["MESTOH"] = Query->FieldByName("mestoh")->AsString;
        m["KOD"] = Query->FieldByName("m_kod")->AsString;
        m["TXT"] = Query->FieldByName("txt")->AsString;
        vTanks.push_back( m);
    }
    Query->Close();
    CB->ItemIndex = 0;
}


void __fastcall TFraTankGasolineList::FrameMouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    Handled = true;
}


//---------------------------------------------------------------------------
