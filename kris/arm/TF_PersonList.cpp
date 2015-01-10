//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TF_PersonList.h"
#include "TF_Person.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TF_MDI"
#pragma link "DBAccess"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "MemDS"
#pragma link "Ora"
#pragma resource "*.dfm"
TF_PersonList *F_PersonList;
//---------------------------------------------------------------------------
__fastcall TF_PersonList::TF_PersonList(TComponent* Owner)
    : TF_MDI(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_PersonList::DBGridEh1ApplyFilter(TObject *Sender)
{
    AnsiString S = "";
    OraQuery1->Close();
    for (int I = 0; I < DBGridEh1->VisibleColumns->Count; I++) {
        AnsiString sField = DBGridEh1->VisibleColumns->Items[I]->FieldName;
        AnsiString sExpr = DBGridEh1->VisibleColumns->Items[I]->STFilter->ExpressionStr.Trim();
        if (sExpr.IsEmpty()) continue;
        S = S + " and upper(to_char(" + sField + ")) like upper('%'||:"+sField+"||'%')";
    }
    for (int I = 0; I < OraQuery1->SQL->Count; I++) {
        if (OraQuery1->SQL->Strings[I].SubString(1,10)!="/*FILTER*/") continue;
        OraQuery1->SQL->Strings[I] = "/*FILTER*/"+S;
        break;
    }
    OraQuery1->Prepare();
    for (int I = 0; I < DBGridEh1->VisibleColumns->Count; I++) {
        AnsiString sField = DBGridEh1->VisibleColumns->Items[I]->FieldName;
        AnsiString sExpr = DBGridEh1->VisibleColumns->Items[I]->STFilter->ExpressionStr.Trim();
        if (sExpr.IsEmpty()) continue;
        OraQuery1->ParamByName(sField)->AsString = sExpr;
    }
    OraQuery1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TF_PersonList::DBGridEh1DblClick(TObject *Sender)
{
    TF_Person* F = new TF_Person(Application);
    F->OpenPersonID(this->OraQuery1->FieldByName("id")->AsInteger);    
}
//---------------------------------------------------------------------------
