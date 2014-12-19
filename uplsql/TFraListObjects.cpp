//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>
#include "TFraListObjects.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma resource "*.dfm"
TFraListObjects *FraListObjects;
//---------------------------------------------------------------------------
__fastcall TFraListObjects::TFraListObjects(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFraListObjects::Init(AnsiString objType)
{
    std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
    Q->SQL->Text = "select distinct object_name from all_objects where owner=user and object_type like :objtype order by 1";
    Q->ParamByName("objtype")->AsString = objType;
    for (Q->Open(); !Q->Eof; Q->Next()) {
        ListBox1->Items->Add(Q->FieldByName("object_name")->AsString);
    }
}