//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditorBase.h"

//#define TEM_TRACE
//#define TEM_TRACE_TAB_COUNT 4
//#include "TtemTraceLog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TEditorBase *EditorBase;
//
//---------------------------------------------------------------------------
__fastcall TEditorBase::TEditorBase(TComponent* Owner)
    : TFrame(Owner)
{
    oldOnKeyPress = 0;
    oldOnDrawColumnCell = 0;
    ViewText->BringToFront();
    Color = ViewText->Color;
    isEditMode = false;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetRect(TRect inRect)
{
    FrameCell = inRect;

    this->Left    = inRect.Left+1;
    this->Top     = inRect.Top+1;
    this->Width   = inRect.Width()-2;
    this->Height  = inRect.Height()-2;

    TDBGridEh* DBG = (TDBGridEh*)this->Parent;
    ViewText->Left   = 1;
    ViewText->Top    = DBG->Flat?0:1;
    ViewText->Width  = this->Width-3;
    ViewText->Height = this->Height-0;
    EditText->Left   = ViewText->Left;
    EditText->Top    = ViewText->Top;
    EditText->Width  = ViewText->Width;
    EditText->Height = ViewText->Height;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetVal(AnsiString S)
{
    ViewText->Caption    = S;
    ViewText->Hint       = S;
    EditText->Text       = S;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetAlignment(TAlignment al)
{
    ViewText->Alignment = al;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetViewMode()
{
    isEditMode = false;

    EditText->Hide();
    ViewText->Show();
    ViewText->BringToFront();
    Color = ViewText->Color;
    SetRect(FrameCell);
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetEditMode()
{
    isEditMode = true;

    ViewText->Hide();
    EditText->Show();
    EditText->BringToFront();
    Color = EditText->Color;

    SetRect(FrameCell);
    EditText->SetFocus();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::ViewTextClick(TObject *Sender)
{
    SetEditMode();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::myKeyPress(unsigned char &Key)
{
    SetEditMode();
    SendMessage(EditText->Handle, WM_CHAR, Key, 0);
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::EditTextKeyDown(TObject *Sender, WORD &Key,
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
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->SelectedField->AsString = EditText->Text;
        }
        SetViewMode();
        this->Parent->SetFocus();
    }

    if (Key==VK_UP || Key==VK_DOWN) {
        SetViewMode();
        this->Parent->SetFocus();
        if (DBG->DataSource->State == dsEdit || DBG->DataSource->State == dsInsert) {
            DBG->SelectedField->AsString = EditText->Text;
        }
        SendMessage(Parent->Handle, WM_KEYDOWN, Key, 0);
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::EditTextKeyPress(TObject *Sender, char &Key)
{
    if (EditText->Focused() && ((TDBGridEh*)this->Parent)->DataSource->DataSet->State==dsBrowse) {
        ((TDBGridEh*)this->Parent)->DataSource->DataSet->Edit();
    }
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::SetParent(TWinControl* AParent)
{
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
{
    DBG->OnKeyPress         = 0;
    DBG->OnDrawColumnCell   = 0;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::_SetupEvents(TDBGridEh* DBG)
{
    oldOnKeyPress           = DBG->OnKeyPress;
    oldOnDrawColumnCell     = DBG->OnDrawColumnCell;
    DBG->OnKeyPress         = EditorBaseKeyPress;
    DBG->OnDrawColumnCell   = EditorBaseDrawColumnCell;
}



//---------------------------------------------------------------------------
bool __fastcall TEditorBase::isPointInRect(int X, int Y, TRect &Rect)
{
    if (X>Rect.Left && X<Rect.Right && Y>Rect.Top && Y<Rect.Bottom) return true;
    return false;
}


//---------------------------------------------------------------------------
bool __fastcall TEditorBase::isFrameInRect(TRect &Rect)
{
    if (isPointInRect(FrameCell.Left,FrameCell.Top,Rect)) return true;
    if (isPointInRect(FrameCell.Left,FrameCell.Top+FrameCell.Height(),Rect)) return true;
    if (isPointInRect(FrameCell.Left+FrameCell.Width(),FrameCell.Top,Rect)) return true;
    if (isPointInRect(FrameCell.Left+FrameCell.Width(),FrameCell.Top+FrameCell.Height(),Rect)) return true;
    return false;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::Show()
{
    if (Visible) return;
    TFrame::Show();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::Hide()
{
    TFrame::Hide();
}


bool __fastcall TEditorBase::isEditableField(AnsiString inFieldName)
{
    inFieldName = inFieldName.Trim().UpperCase();
    map<AnsiString,bool>::iterator it = listFieldName.find(inFieldName);
    if (it==listFieldName.end()) return false;
    return it->second;
}

//---------------------------------------------------------------------------
void __fastcall TEditorBase::EditorBaseKeyPress(TObject *Sender, char &Key)
{
 // перехватчик соответствующего события грида
    if (oldOnKeyPress != 0) oldOnKeyPress(Sender,Key);
    TDBGridEh* DBG = (TDBGridEh*)this->Parent;

    if (Key != VK_TAB && Key!=VK_ESCAPE && isEditableField(DBG->SelectedField->FieldName)) {
        myKeyPress(Key);
        DBG->EditorMode = false;
        Key = 0;
    }
}


//---------------------------------------------------------------------------
bool __fastcall TEditorBase::isSelectedColumnOutOfRange(TDBGridEh* DBG)
{
    if (DBG->LeftCol > (DBG->SelectedIndex+1)) {
        return true;
    }
    if ((DBG->VisibleColCount+DBG->LeftCol) < (DBG->SelectedIndex)) {
        return true;
    }
    return false;
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::EditorBaseDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
 // перехватчик соответствующего события грида
    if (oldOnDrawColumnCell != 0) {
        oldOnDrawColumnCell(Sender,Rect,DataCol,Column,State);
    }

    TDBGridEh* DBG = (TDBGridEh*)Sender;

    if (isSelectedColumnOutOfRange(DBG)) {
        Hide();
        return;
    }

    if (State.Contains(Gridseh::gdSelected)) {
        if (!isEditMode) {
            Hide();
            this->SetVal(Column->Field->AsString);
            this->SetAlignment(Column->Alignment);
        }
        if (isEditableField(Column->FieldName)) {
            this->SetRect(Rect);// VAR(Rect.Width()) VAR(Rect.Height())
            Show();
        }
    }
    else {
        if (isFrameInRect(Rect) && this->Visible) {
            Hide();
        }
    }
}



//---------------------------------------------------------------------------
void __fastcall TEditorBase::FrameExit(TObject *Sender)
{
 // обработчик соответствующего события фрейма
    SetViewMode();
}


//---------------------------------------------------------------------------
void __fastcall TEditorBase::FrameMouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    Handled = true;
}
//---------------------------------------------------------------------------


