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
    EditorGrid1->Parent = DBG;
    EditorGrid1->BringToFront();
    EditorGrid1->listFieldName["NAIM"] = true;
    EditorGrid1->LoadHistoryFromDataset(MT, "NAIM");

    EditorCat->Parent = DBG;
    EditorCat->BringToFront();
    EditorCat->listFieldName["CAT"] = true;
    EditorCat->LoadHistoryFromDataset(MT, "CAT");
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MT2AfterPost(TDataSet *DataSet)
{
    EditorGrid1->LoadHistoryFromDataset(MT, "NAIM");
    EditorCat->LoadHistoryFromDataset(MT, "CAT");
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
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
    MT->LoadFromFile("test");

}
//---------------------------------------------------------------------------

