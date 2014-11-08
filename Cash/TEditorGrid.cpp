//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditorGrid.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TEditorBase"
#pragma link "MemTableEh"
#pragma link "DBGridEh"
#pragma link "GridsEh"
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

    Grid->Left = EditText->Left;
    Grid->Top = EditText->Height+2;
    Grid->Width = EditText->Width;
    if (isEditMode) {
        this->Width   = inRect.Width()-2;
        if (this->Width < Grid->Width) this->Width = Grid->Width+2;
        this->Height  = EditText->Height + Grid->Height+4;
        EditText->Width    = this->Width-3;
    }
}

void __fastcall TEditorGrid::EditTextChange(TObject *Sender)
{
    int row = Grid->FixedRows;
    Grid->Cells[0][Grid->FixedRows] = "";
    for (int I = 0; I < listAvto.size(); I++) {
        if (EditText->Text.Trim().IsEmpty() || listAvto[I].UpperCase().Pos(EditText->Text.Trim().UpperCase()) > 0) {
            Grid->Cells[0][row] = listAvto[I];
            row++;
        }
    }
    Grid->RowCount = row+Grid->FixedRows;
}
//---------------------------------------------------------------------------

void __fastcall TEditorGrid::EditTextKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_DOWN) {
        Grid->SetFocus();
        return;
    }
    TEditorBase::EditTextKeyDown(Sender, Key, Shift);
}
//---------------------------------------------------------------------------

void __fastcall TEditorGrid::GridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    if (Grid->Focused() && State.Contains(Grids::gdSelected)) {
        Grid->Canvas->Brush->Color = clHighlight;
        Grid->Canvas->Font->Color = clHighlightText;
    }
    else {
        Grid->Canvas->Brush->Color = clWindow;
        Grid->Canvas->Font->Color = clBlack;
    }
    Grid->Canvas->TextRect(Rect, Rect.Left + 1, Rect.Top + 1, Grid->Cells[ACol][ARow]);
}
//---------------------------------------------------------------------------

void __fastcall TEditorGrid::GridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_DOWN || Key==VK_UP) {
        return;
    }
    if (Key==VK_RETURN) {
        EditText->Text = Grid->Cells[0][Grid->Row];
    }
    TEditorBase::EditTextKeyDown(Sender, Key, Shift);
}
//---------------------------------------------------------------------------

void __fastcall TEditorGrid::GridDblClick(TObject *Sender)
{
    GridKeyDown(Sender, VK_RETURN, TShiftState());
}
//---------------------------------------------------------------------------

void __fastcall TEditorGrid::Show()
{
    int row = Grid->FixedRows;
    TMemTableEh* MT = MemTableEh1;
    MT->Open();

//    MT->ExternalMemData = (TMemTableEh*)(((TDBGridEh*)this->Parent)->DataSource->DataSet);
    Grid->Cells[0][Grid->FixedRows] = "";
    for (MT->First(); !MT->Eof; MT->Next()) {
        Grid->Cells[0][row] = MT->FieldByName("naim")->AsString;
        row++;
    }
    Grid->RowCount = row+Grid->FixedRows;

    __INHERIT__::Show();
}
