//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditorGrid.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TEditorBase"
#pragma resource "*.dfm"
TEditorGrid *EditorGrid;
//---------------------------------------------------------------------------
__fastcall TEditorGrid::TEditorGrid(TComponent* Owner)
        : TEditorBase(Owner)
{
}
//---------------------------------------------------------------------------
#define __INHERIT__ TEditorBase

void __fastcall TEditorGrid::SetRect(TRect inRect)
{
    TEditorBase::SetRect(inRect);

    TDBGridEh* DBG = (TDBGridEh*)this->Parent;
    ViewText->Left   = 1;
    ViewText->Top    = DBG->Flat?0:1;
    ViewText->Width  = this->Width-3;
    ViewText->Height = this->Height-0;
    EditText->Left         = ViewText->Left;
    EditText->Top          = ViewText->Top;
    EditText->Width        = ViewText->Width;
    EditText->Height       = ViewText->Height;

    Grid->Left = EditText->Left;
    Grid->Top = EditText->Height;
    if (isEditMode) {
        this->Width   = inRect.Width()-2;
        if (this->Width < Grid->Width) this->Width = Grid->Width+2;
        this->Height  = EditText->Height + Grid->Height+2;
        EditText->Width    = this->Width-3;
    }
}

