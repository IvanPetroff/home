//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "MemTableEh"
#pragma link "TEditorBase"
#pragma link "TEditorGrid"
#pragma link "MemDS"
#pragma link "VirtualTable"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
    isLoadMode = false;
    EditorGrid1->Parent = DBG;
    EditorGrid1->BringToFront();
    EditorGrid1->listFieldName["NAIM"] = true;
    EditorGrid1->LoadHistoryFromDataset(MT, "NAIM");

    EditorCat->Parent = DBG;
    EditorCat->BringToFront();
    EditorCat->listFieldName["CAT"] = true;
    EditorCat->LoadHistoryFromDataset(MT, "CAT");

    EditorCurr->Parent = DBG;
    EditorCurr->BringToFront();
    EditorCurr->listFieldName["CURR"] = true;
    EditorCurr->LoadHistoryFromDataset(MT, "CURR");

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MT2AfterPost(TDataSet *DataSet)
{
    if (isLoadMode) return;
    EditorGrid1->LoadHistoryFromDataset(MT, "NAIM");
    EditorCat->LoadHistoryFromDataset(MT, "CAT");
    EditorCurr->LoadHistoryFromDataset(MT, "CURR");
}
//---------------------------------------------------------------------------
struct x {
  char c;
};

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    MT->SaveToFile("test");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MTAfterPost(TDataSet *DataSet)
{
    EditorGrid1->LoadHistoryFromDataset(MT, "NAIM");
    EditorCat->LoadHistoryFromDataset(MT, "CAT");
    EditorCurr->LoadHistoryFromDataset(MT, "CURR");
    if (!MT->FieldByName("cat")->AsString.Trim().IsEmpty() && !MT->FieldByName("naim")->AsString.Trim().IsEmpty()) {
        listCat[MT->FieldByName("naim")->AsString] = MT->FieldByName("cat")->AsString;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
    isLoadMode = true;
    try {
        MT->LoadFromFile("test");
    }
    catch(...) {
    }
    isLoadMode = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MTAfterInsert(TDataSet *DataSet)
{
    if (isLoadMode) return;
    MT->FieldByName("dat")->AsDateTime = Now();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MTBeforePost(TDataSet *DataSet)
{
    if (MT->FieldByName("cat")->AsString.Trim().IsEmpty() && !MT->FieldByName("naim")->AsString.Trim().IsEmpty()) {
        MT->FieldByName("cat")->AsString = listCat[MT->FieldByName("naim")->AsString];
    }
}
//---------------------------------------------------------------------------

