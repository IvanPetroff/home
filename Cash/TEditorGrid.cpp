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
    if (isEditMode && !IsHistoryGridEmpty()) {
        SetVisibleHistoryGrid(true);
    }
}


void __fastcall TEditorGrid::SetVisibleHistoryGrid(bool flg)
{
    if (flg) {
        this->Width   = FrameCell.Width()-2;
        if (this->Width < Grid->Width) {
            this->Width = Grid->Width+2;
        }
        this->Height  = Grid->Top + Grid->Height+4;
        EditText->Width    = this->Width-3;
    }
    else {
        this->Height  = Grid->Top;
    }
}

bool __fastcall TEditorGrid::IsHistoryGridEmpty()
{
    if (Grid->Cells[0][Grid->FixedRows].Trim().IsEmpty()) {
        return true;
    }
    return false;

}

void __fastcall TEditorGrid::FilterHistory()
{
    int row = Grid->FixedRows;
    Grid->Cells[0][Grid->FixedRows] = "";
    for (map<AnsiString,int>::iterator it = History.begin(); it!=History.end(); it++) {
        if (it->second==0) continue;
        if (EditText->Text.Trim().IsEmpty() || it->first.UpperCase().Pos(EditText->Text.Trim().UpperCase()) > 0) {
            Grid->Cells[0][row] = it->first;
            row++;
        }
    }
    Grid->RowCount = row+Grid->FixedRows;
    SetVisibleHistoryGrid( !IsHistoryGridEmpty());
}


void __fastcall TEditorGrid::EditTextChange(TObject *Sender)
{
    FilterHistory();
}
//---------------------------------------------------------------------------

void __fastcall TEditorGrid::EditTextKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_DOWN && !IsHistoryGridEmpty()) {
        Grid->SetFocus();
        return;
    }
    if (Key==VK_RETURN && Shift.Contains(ssCtrl) && GetHistoryGridCount()==1) {
        Grid->SetFocus();
        EditText->Text = GetHistoryGridItem(0);
    }
    TEditorBase::EditTextKeyDown(Sender, Key, Shift);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TEditorGrid::GetHistoryGridItem(int index)
{
    int row = Grid->FixedRows;
    return Grid->Cells[0][Grid->FixedRows];
}


int __fastcall TEditorGrid::GetHistoryGridCount()
{
    if (IsHistoryGridEmpty()) return 0;
    return Grid->RowCount - Grid->FixedRows;
}


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
    if (Key==VK_UP && Grid->Row==Grid->FixedRows) {
        EditText->SetFocus();
        return;
    }
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


void __fastcall TEditorGrid::LoadHistoryFromDataset(TDataSet* DS, AnsiString FieldName)
{
#define foreach(X) for (X->First();!X->Eof;X->Next())
    History.clear();
    int recno = DS->RecNo;
    foreach(DS) {
        AnsiString S = DS->FieldByName(FieldName)->AsString.Trim();
        if (S.IsEmpty()) continue;
        History[ S] = 1+History[ S];
    }
    DS->RecNo = recno;
}


void __fastcall TEditorGrid::SetEditMode()
{
    __INHERIT__::SetEditMode();
    this->FilterHistory();
}




