//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditorBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TEditorBase *EditorBase;
//---------------------------------------------------------------------------
__fastcall TEditorBase::TEditorBase(TComponent* Owner)
    : TFrame(Owner)
{
    StaticText1->BringToFront();
    Color = StaticText1->Color;
}
//---------------------------------------------------------------------------


void __fastcall TEditorBase::SetRect(TRect inRect)
{
    Left = inRect.Left+1;
    Top = inRect.Top+1;
    Width = inRect.Width()-2;
    Height = inRect.Height()-2;
}


void __fastcall TEditorBase::FrameResize(TObject *Sender)
{
    TDBGridEh* DBG = (TDBGridEh*)this->Parent;
    StaticText1->Left = 1;
    StaticText1->Top = DBG->Flat?0:1;
    StaticText1->Width = Width-3;
    StaticText1->Height = Height-0;

    Edit1->Left = StaticText1->Left;
    Edit1->Top = StaticText1->Top;
    Edit1->Width = StaticText1->Width;
    Edit1->Height = StaticText1->Height;
}

void __fastcall TEditorBase::SetVal(AnsiString S)
{
    StaticText1->Caption = S;
    StaticText1->Hint = S;

    Edit1->Text = S;
}


void __fastcall TEditorBase::SetAlignment(TAlignment al)
{
    StaticText1->Alignment = al;
}


void __fastcall TEditorBase::SetViewMode()
{
    Edit1->Visible = false;
    StaticText1->Visible = true;
    StaticText1->BringToFront();
    Color = StaticText1->Color;
}


void __fastcall TEditorBase::SetEditMode()
{
    StaticText1->Visible = false;
    Edit1->Visible = true;
    Edit1->BringToFront();
    Edit1->SetFocus();
    Color = Edit1->Color;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::StaticText1Click(TObject *Sender)
{
    SetEditMode();
}
//---------------------------------------------------------------------------
void __fastcall TEditorBase::Edit1Exit(TObject *Sender)
{
    SetViewMode();
}
//---------------------------------------------------------------------------

void __fastcall TEditorBase::myKeyPress(char &Key)
{
    SetEditMode();
    SendMessage(Edit1->Handle, WM_CHAR, Key, 0);
}


void __fastcall TEditorBase::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
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
{
    if (Edit1->Focused()) {
        ((TDBGridEh*)this->Parent)->DataSource->Edit();
    }
}
//---------------------------------------------------------------------------


void __fastcall TEditorBase::SetParent(TWinControl* AParent)
{
    TDBGridEh* DBG = dynamic_cast<TDBGridEh*>(Parent);
    if (DBG != 0) {
        RemoveEvents(DBG);
    }
    TFrame::SetParent(AParent);
    DBG = dynamic_cast<TDBGridEh*>(Parent);
    if (DBG != 0) {
        SetupEvents(DBG);
    }
}

void __fastcall TEditorBase::RemoveEvents(TDBGridEh* DBG)
{
    DBG->OnKeyPress = 0;
    DBG->OnDrawColumnCell = 0;
}

void __fastcall TEditorBase::SetupEvents(TDBGridEh* DBG)
{
    DBG->OnKeyPress = EditorBaseKeyPress;
    DBG->OnDrawColumnCell = EditorBaseDrawColumnCell;
}



void __fastcall TEditorBase::EditorBaseKeyPress(TObject *Sender, char &Key)
{
    if (Key != VK_TAB && Key!=VK_ESCAPE) {
        myKeyPress(Key);
    }
}

bool __fastcall TEditorBase::isPointInRect(int X, int Y, TRect &Rect)
{
    if (X>Rect.Left && X<Rect.Right && Y>Rect.Top && Y<Rect.Bottom) return true;
    return false;
}

bool __fastcall TEditorBase::isFrameInRect(TRect &Rect)
{
    if (isPointInRect(Left,Top,Rect)) return true;
    if (isPointInRect(Left,Top+Height,Rect)) return true;
    if (isPointInRect(Left+Width,Top,Rect)) return true;
    if (isPointInRect(Left+Width,Top+Height,Rect)) return true;
    return false;
}


void __fastcall TEditorBase::EditorBaseDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
    TDBGridEh* DBG = (TDBGridEh*)Sender;
    if (DBG->LeftCol > (DBG->SelectedIndex+1)) {
        this->Visible = false;
        return;
    }
    if ((DBG->VisibleColCount+DBG->LeftCol) < (DBG->SelectedIndex)) {
        this->Visible = false;
        return;
    }
    if (State.Contains(gdFocused)) {
        this->Visible = false;
        this->SetRect(Rect);
        this->SetVal(Column->Field->AsString);
        this->SetAlignment(Column->Alignment);
        this->Visible = true;
    }
    else {
        if (isFrameInRect(Rect)) {
            this->Visible = false;
        }
    }
}
