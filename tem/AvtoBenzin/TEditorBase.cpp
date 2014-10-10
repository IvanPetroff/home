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
}
//---------------------------------------------------------------------------


void __fastcall TEditorBase::SetRect(TRect inRect)
{
    Left = inRect.Left+2;
    Top = inRect.Top+1;
    Width = inRect.Width()-5;
    Height = inRect.Height()-2;
}


void __fastcall TEditorBase::FrameResize(TObject *Sender)
{
    StaticText1->Width = Width;
    StaticText1->Height = Height;
    Edit1->Width = Width;
    Edit1->Height = Height;
}

void __fastcall TEditorBase::SetVal(AnsiString S)
{
    StaticText1->Caption = S;
    Edit1->Text = S;
}


void __fastcall TEditorBase::SetAlignment(TAlignment al)
{
    StaticText1->Alignment = al;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::StaticText1Click(TObject *Sender)
{
    StaticText1->Visible = false;
    Edit1->Visible = true;
    Edit1->BringToFront();
    Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TEditorBase::Edit1Exit(TObject *Sender)
{
    Edit1->Visible = false;
    StaticText1->Visible = true;
    StaticText1->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TEditorBase::myKeyPress(char &Key)
{
    StaticText1->Visible = false;
    Edit1->Visible = true;
    Edit1->BringToFront();
    Edit1->SetFocus();
    SendMessage(Edit1->Handle, WM_CHAR, Key, 0);
}


void __fastcall TEditorBase::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    TDBGridEh* DBG = (TDBGridEh*)this->Parent;
    if (Key==VK_ESCAPE) {
        Edit1->Visible = false;
        StaticText1->Visible = true;
        StaticText1->BringToFront();
        this->Parent->SetFocus();
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->DataSource->DataSet->Cancel();
        }
    }

    if (Key==VK_RETURN) {
        Edit1->Visible = false;
        StaticText1->Visible = true;
        StaticText1->BringToFront();
        this->Parent->SetFocus();
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->SelectedField->AsString = Edit1->Text;
        }
    }

    if (Key==VK_UP || Key==VK_DOWN) {
        Edit1->Visible = false;
        StaticText1->Visible = true;
        StaticText1->BringToFront();
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

}