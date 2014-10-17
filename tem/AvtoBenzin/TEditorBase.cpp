//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditorBase.h"

//#define TEM_TRACE
//#define TEM_TRACE_TAB_COUNT 4
#include "TtemTraceLog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TEditorBase *EditorBase;
//---------------------------------------------------------------------------
__fastcall TEditorBase::TEditorBase(TComponent* Owner)
    : TFrame(Owner)
{BEGIN
    oldOnKeyPress = 0;
    oldOnDrawColumnCell = 0;
    StaticText1->BringToFront();
    Color = StaticText1->Color;

}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetRect(TRect inRect)
{BEGIN
    FrameCell = inRect;
    int Left = this->Left;
    int Top = this->Top;
    int Width = this->Width;
    int Height = this->Height;

    Left    = inRect.Left+1;
    Top     = inRect.Top+1;
    if (this->isViewMode()) {
        Width   = inRect.Width()-2;
        Height  = inRect.Height()-2;
    }
    else {
        Width   = inRect.Width()-2;
        if (Width < Grid->Width) Width = Grid->Width;
        Height  = Edit1->Height + Grid->Height;
    }

    this->Left = Left;
    this->Top = Top;
    this->Width = Width;
    this->Height = Height;
    VAR(Width)
    VAR(Height)
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetVal(AnsiString S)
{BEGIN
    StaticText1->Caption    = S;
    StaticText1->Hint       = S;
    Edit1->Text             = S;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetAlignment(TAlignment al)
{BEGIN
    StaticText1->Alignment = al;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetViewMode()
{BEGIN
    Edit1->Hide();
    StaticText1->Show();
    StaticText1->BringToFront();
    Color = StaticText1->Color;

    Grid->Visible = Edit1->Visible;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetEditMode()
{BEGIN
    StaticText1->Hide();
    Edit1->Show();
    Edit1->BringToFront();
    Edit1->SetFocus();
    Color = Edit1->Color;

    Grid->Visible = Edit1->Visible;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::StaticText1Click(TObject *Sender)
{BEGIN
    SetEditMode();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::myKeyPress(char &Key)
{BEGIN
    SetEditMode();
    SendMessage(Edit1->Handle, WM_CHAR, Key, 0);
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{BEGIN
    TDBGridEh* DBG = (TDBGridEh*)this->Parent;
    if (Key==VK_ESCAPE) {
        SetViewMode();
        this->Parent->SetFocus();
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->DataSource->DataSet->Cancel();
        }
    }

    if (Key==VK_RETURN) {
        SetViewMode();
        this->Parent->SetFocus();
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->SelectedField->AsString = Edit1->Text;
        }
    }

    if (Key==VK_UP || Key==VK_DOWN) {
        SetViewMode();
        this->Parent->SetFocus();
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->SelectedField->AsString = Edit1->Text;
        }
        SendMessage(Parent->Handle, WM_KEYDOWN, Key, 0);
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::Edit1KeyPress(TObject *Sender, char &Key)
{BEGIN
    if (Edit1->Focused() && ((TDBGridEh*)this->Parent)->DataSource->DataSet->State==dsBrowse) {
        ((TDBGridEh*)this->Parent)->DataSource->DataSet->Edit();
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetParent(TWinControl* AParent)
{BEGIN
    TDBGridEh* DBG = dynamic_cast<TDBGridEh*>(Parent);
    if (DBG != 0) {
        _RemoveEvents(DBG);
    }
    TFrame::SetParent(AParent);
    DBG = dynamic_cast<TDBGridEh*>(Parent);
    if (DBG != 0) {
        _SetupEvents(DBG);
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::_RemoveEvents(TDBGridEh* DBG)
{BEGIN
    DBG->OnKeyPress         = 0;
    DBG->OnDrawColumnCell   = 0;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::_SetupEvents(TDBGridEh* DBG)
{BEGIN
    oldOnKeyPress           = DBG->OnKeyPress;
    oldOnDrawColumnCell     = DBG->OnDrawColumnCell;
    DBG->OnKeyPress         = EditorBaseKeyPress;
    DBG->OnDrawColumnCell   = EditorBaseDrawColumnCell;
}



//---------------------------------------------------------------------------
bool __fastcall TEditorBase::isPointInRect(int X, int Y, TRect &Rect)
{BEGIN
    if (X>Rect.Left && X<Rect.Right && Y>Rect.Top && Y<Rect.Bottom) return true;
    return false;
}


//---------------------------------------------------------------------------
bool __fastcall TEditorBase::isFrameInRect(TRect &Rect)
{BEGIN
    if (isPointInRect(FrameCell.Left,FrameCell.Top,Rect)) return true;
    if (isPointInRect(FrameCell.Left,FrameCell.Top+FrameCell.Height(),Rect)) return true;
    if (isPointInRect(FrameCell.Left+FrameCell.Width(),FrameCell.Top,Rect)) return true;
    if (isPointInRect(FrameCell.Left+FrameCell.Width(),FrameCell.Top+FrameCell.Height(),Rect)) return true;
    return false;
}


//---------------------------------------------------------------------------
bool __fastcall TEditorBase::isViewMode()
{BEGIN
    if (StaticText1->Visible) {
        return true;
    }
    return false;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::Show()
{BEGIN
    if (Visible) return;
    TFrame::Show();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::Hide()
{BEGIN
    TFrame::Hide();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::EditorBaseKeyPress(TObject *Sender, char &Key)
{BEGIN
 // перехватчик соответствующего события грида
    if (oldOnKeyPress != 0) oldOnKeyPress(Sender,Key);
    if (Key != VK_TAB && Key!=VK_ESCAPE) {
        myKeyPress(Key);
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::EditorBaseDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{BEGIN
 // перехватчик соответствующего события грида
    if (oldOnDrawColumnCell != 0) oldOnDrawColumnCell(Sender,Rect,DataCol,Column,State);

    TDBGridEh* DBG = (TDBGridEh*)Sender;
    if (DBG->LeftCol > (DBG->SelectedIndex+1)) {
        Hide();
        return;
    }
    if ((DBG->VisibleColCount+DBG->LeftCol) < (DBG->SelectedIndex)) {
        Hide();
        return;
    }
    if (State.Contains(Gridseh::gdSelected)) {
        if (isViewMode()) {
            Hide();
        }
        this->SetRect(Rect); VAR(Rect.Width()) VAR(Rect.Height())
        if (isViewMode()) this->SetVal(Column->Field->AsString);
        this->SetAlignment(Column->Alignment);
        Show();
    }
    else {
        if (isFrameInRect(Rect) && this->Visible) {
            Hide();
        }
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::FrameExit(TObject *Sender)
{BEGIN
 // обработчик соответствующего события фрейма
    SetViewMode();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::FrameResize(TObject *Sender)
{BEGIN // обработчик соответствующего события фрейма
    if (this->isViewMode()) {
        TDBGridEh* DBG = (TDBGridEh*)this->Parent;
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




