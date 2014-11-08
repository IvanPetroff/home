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
}
//---------------------------------------------------------------------------
