//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <fstream>
#include <streambuf>
#include <istream>
#include <memory>
#include <vector>
#include <string>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DataDriverEh"
#pragma link "TEditorBase"
#pragma resource "*.dfm"
TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    try {
        std::auto_ptr<TStringList> SL(new TStringList);
        SL->LoadFromFile("c:\\db_asu.txt");
        for (int I = 0; I < SL->Count; I++) {
            if (SL->Strings[I].SubString(1,1)=="#") continue;
            db->ConnectString = SL->Strings[I];
            break;
        }
        db->LoginPrompt = false;
        db->Options->Direct = true;
        Caption = Caption + " [" + db->Server.Trim() + "]";
    }
    catch (...) {
    }
    db->Connected = true;
    TmyQuery Q(db,"ALTER SESSION SET NLS_NUMERIC_CHARACTERS='.,'");
    Q->ExecSQL();

    Q_Sod->Open();

    Q_KodOper->Close();
    for (Q_KodOper->Open(); !Q_KodOper->Eof; Q_KodOper->Next()) {
        CB_KodOper->Items->Add( Q_KodOper->FieldByName("txt")->AsString);
    }

    Q_Benzin->Close();
    Q_Benzin->ParamByName("skl")->AsString = E_SklFrom->Text;
    for (Q_Benzin->Open(); !Q_Benzin->Eof; Q_Benzin->Next()) {
        CB_Benzin->Items->Add( Q_Benzin->FieldByName("txt")->AsString);
    }
    CB_Benzin->ItemIndex = 0;

    EditorBase1->Parent = DBG_Sod;
    EditorBase1->BringToFront();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::DBG_SloAvtoSortMarkingChanged(TObject *Sender)
{
    AnsiString S = "";
    for (int I=0; I < DBG_SloAvto->SortMarkedColumns->Count; I++) {
        S = S + ", " + DBG_SloAvto->SortMarkedColumns->Items[I]->FieldName;
        if (DBG_SloAvto->SortMarkedColumns->Items[I]->Title->SortMarker == smDownEh) {
            S = S + " ";
        }
        if (DBG_SloAvto->SortMarkedColumns->Items[I]->Title->SortMarker == smUpEh) {
            S = S + " desc";
        }
    }
    S = S.Delete(1,1);
    Q_SloAvto->SetOrderBy(S);
    Q_SloAvto->Open();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::DBG_SloAvtoApplyFilter(TObject *Sender)
{
    AnsiString S = "";
    for (int I = 0; I < DBG_SloAvto->Columns->Count; I++) {
        if (DBG_SloAvto->Columns->Items[I]->STFilter->ExpressionStr.Trim().IsEmpty()) continue;
        S = S + " and upper(" + DBG_SloAvto->Columns->Items[I]->FieldName + ") like '%"+DBG_SloAvto->Columns->Items[I]->STFilter->ExpressionStr.Trim().UpperCase()+"%'";
    }
    S = S.Delete(1,5);
    Q_SloAvto->DeleteWhere();
    Q_SloAvto->AddWhere(S);
    Q_SloAvto->Open();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
    Q_Sod->Append();
    Q_Sod->FieldByName("izd")->AsString = Q_SloAvto->FieldByName("n_gai")->AsString;
    AnsiString S = CB_Benzin->Text;
    S = S.SubString(S.LastDelimiter("[")+1,S.Length());
    S = S.SubString(1, S.Pos("]")-1);
    Q_Sod->FieldByName("kod_mat")->AsString = S;

    Q_Sod->Post();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::DBG_SloAvtoDblClick(TObject *Sender)
{
    SpeedButton1Click(0);
}


//---------------------------------------------------------------------------
void __fastcall TForm1::DBG_SloAvtoDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
    if (State.Contains(Gridseh::gdFixed)) return;
    if (DataCol>0) return;
    Panel3->Height = Rect.Height()-2;
    Panel3->Width = Rect.Height()+2;
    if (State.Contains(Gridseh::gdSelected)) {
        Panel3->Color = clLime;
        Panel3->Font->Color = clBlack;
    }
    else {
        Panel3->Color = DBG_SloAvto->Color;
        Panel3->Font->Color = clSilver;
    }

    if (State.Contains(Gridseh::gdSelected)) {
        DBG_SloAvto->Canvas->Lock();
        Panel3->PaintTo( DBG_SloAvto->Canvas->Handle,(Rect.Left+Rect.Right-Panel3->Width)/2,(Rect.Top+Rect.Bottom-Panel3->Height)/2);
        DBG_SloAvto->Canvas->Unlock();
    }
}


//---------------------------------------------------------------------------
int __fastcall GetRecNoOnARow(TDBGridEh* DBG, int ARow)
{
    if (ARow<(DBG->STFilter->Visible?2:1)) {
        return -1;
    }

    int DeltaY = ARow - DBG->Row;
    int RecNo = DBG->DataRowToRecNo(DBG->Row-(DBG->STFilter->Visible?2:1)) + DeltaY;
    return RecNo;
}


//---------------------------------------------------------------------------
void __fastcall TForm1::DBG_SloAvtoMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    Gridseh::TGridCoord Coord = DBG_SloAvto->MouseCoord(X,Y);
    int MouseRecNo = GetRecNoOnARow(DBG_SloAvto,Coord.Y);
    if (MouseRecNo>0) {
        while (Q_SloAvto->RecNo < MouseRecNo) Q_SloAvto->Next();
        while (Q_SloAvto->RecNo > MouseRecNo && Q_SloAvto->RecNo>1) Q_SloAvto->Prior();
        if (Y > (DBG_SloAvto->Height - DBG_SloAvto->RowHeight/2)) Q_SloAvto->Next();
    }
    else {
        if (Y > (DBG_SloAvto->Height - DBG_SloAvto->RowHeight)) Q_SloAvto->Next();
    }

}


//---------------------------------------------------------------------------
void __fastcall TForm1::BeginEdit()
{
    if (DBG_Sod->EditorMode) {
      if (Q_Sod->State==dsBrowse) Q_Sod->Edit();
        DBG_Sod->EditorMode = false;
        std::auto_ptr<TmyInplaceEditor> my(new TmyInplaceEditor(this));

        TRect Rect = DBG_Sod->CellRect(DBG_Sod->Col,DBG_Sod->Row);
    TPoint LeftTop = DBG_Sod->ClientToScreen( TPoint(Rect.Left, Rect.Top));
    TPoint RightBottom = DBG_Sod->ClientToScreen( TPoint(Rect.Right, Rect.Bottom));
    Rect.Left = LeftTop.x;
    Rect.Top = LeftTop.y;
    Rect.Right = RightBottom.x;
    Rect.Bottom = RightBottom.y;
        my->E_Cell->Text = DBG_Sod->InplaceEditor->Text;
        int MR = my->ShowModal( Rect, false);
        if (MR==mrOk) {
            DBG_Sod->SelectedField->AsString = my->E_Cell->Text;
        }
    }
}














