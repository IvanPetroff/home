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
    __INHERIT__::SetRect(inRect);

    if (this->isEditMode()) {
        Width   = inRect.Width()-2;
        if (Width < Grid->Width) Width = Grid->Width+2;
        Height  = Edit1->Height + Grid->Height+2;
    }

    TDBGridEh* DBG = (TDBGridEh*)this->Parent;
    if (this->isViewMode()) {
        StaticText1->Left   = 1;
        StaticText1->Top    = DBG->Flat?0:1;
        StaticText1->Width  = Width-3;
        StaticText1->Height = Height-0;
    }
    else {
        Edit1->Left     = StaticText1->Left;
        Edit1->Top      = StaticText1->Top;
        Edit1->Width    = StaticText1->Width;
        Edit1->Height   = StaticText1->Height;

        Grid->Left = Edit1->Left;
        Grid->Top = Edit1->Height;
    }

}

