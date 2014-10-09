//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TmyInplaceEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TInplaceEditorBase"
#pragma resource "*.dfm"
TmyInplaceEditor *myInplaceEditor;
//---------------------------------------------------------------------------
__fastcall TmyInplaceEditor::TmyInplaceEditor(TComponent* Owner)
    : TInplaceEditorBase(Owner)
{
}
//---------------------------------------------------------------------------
#define __class__ TmyInplaceEditor
void __fastcall __class__::Show(TRect Rect)
{
    myWindow->Left = Rect.Left;
    myWindow->Top = Rect.Top;
    myWindow->Width = Rect.Width();
    myWindow->Height = Rect.Height();
    this->Panel1->Height = Rect.Height();
    this->E_Cell->Width = Rect.Width();



    myWindow->Show();
}

void __fastcall TmyInplaceEditor::SaveVal()
{
}


void __fastcall TmyInplaceEditor::LoadVal()
{
}

