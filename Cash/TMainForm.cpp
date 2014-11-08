//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "MemTableEh"
#pragma link "TEditorBase"
#pragma link "TEditorGrid"
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


void __fastcall TMainForm::MTAfterPost(TDataSet *DataSet)
{
    EditorGrid1->LoadHistoryFromDataset(MT, "NAIM");
    EditorCat->LoadHistoryFromDataset(MT, "CAT");
}
//---------------------------------------------------------------------------

