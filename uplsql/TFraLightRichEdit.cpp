//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraLightRichEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFraLightRichEdit *FraLightRichEdit;
//---------------------------------------------------------------------------
__fastcall TFraLightRichEdit::TFraLightRichEdit(TComponent* Owner)
        : TFrame(Owner)
{

	// ������� ������ ����
	SQLWords = new TStringList;
	SQLWords->Add("constructor");
	SQLWords->Add("overriding");
	SQLWords->Add("member");
	SQLWords->Add("function");
	SQLWords->Add("procedure");
	SQLWords->Add("select");
	SQLWords->Add("and");
	SQLWords->Add("or");
	SQLWords->Add("from");
	SQLWords->Add("between");
	SQLWords->Add("where");
	SQLWords->Add("having");
	SQLWords->Add("order");
	SQLWords->Add("group");
	SQLWords->Add("by");
	SQLWords->Add("in");
	SQLWords->Add("null");
	SQLWords->Add("is");
	SQLWords->Add("not");
	SQLWords->Add("like");
	SQLWords->Add("as");
	SQLWords->Add("asc");
	SQLWords->Add("desc");
	SQLWords->Add("count");
	SQLWords->Add("min");
	SQLWords->Add("max");

	// ������� ������ ��������
	SQLSymbols = new TStringList;
	SQLSymbols->Add("*");
	SQLSymbols->Add("'");
	SQLSymbols->Add("%");
	SQLSymbols->Add(">");
	SQLSymbols->Add("<");
	SQLSymbols->Add("=");
	SQLSymbols->Add("!");
	SQLSymbols->Add(",");
	SQLSymbols->Add(";");
	SQLSymbols->Add(":");
	SQLSymbols->Add("(");
	SQLSymbols->Add(")");
	SQLSymbols->Add("^");
	SQLSymbols->Add("||");
	SQLSymbols->Add("[");
	SQLSymbols->Add("]");
	SQLSymbols->Add("+");
	SQLSymbols->Add("-");
	SQLSymbols->Add("/");
	SQLSymbols->Add("&");

	// �������������� ����
	HiLite_wds.FontColor = clBlue; // ����� �����
	HiLite_wds.FontStyle = TFontStyles() << fsBold; // ������
	// �������������� ��������
	HiLite_symb.FontColor = clRed; // ������� �����
	HiLite_symb.FontStyle = TFontStyles(); // �� ������
}
//---------------------------------------------------------------------------


void __fastcall TFraLightRichEdit::HighLight(int pos)
// http://cbuilder.ru/index.php?topic=5870.30
{
        TRichEdit *REdit = RichEdit1;
	DWORD start=GetTickCount();
	///////////////////////////

	// �������� ����� �������
	int eventMask = ::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, 0);
	// ��������� �����������
	::SendMessage(REdit->Handle, WM_SETREDRAW, false, 0);
	// ���������� ���������
	CHARRANGE chrgSave, chrgNew;
	::SendMessage(REdit->Handle, EM_EXGETSEL, 0, (LPARAM) &chrgSave);

	int startat, toend, foundat, caretpos, slth;

	// ����� ��������������
	chrgNew.cpMin = pos;
	chrgNew.cpMax = -1;
	::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
	REdit->SelAttributes->Color = REdit->Font->Color;
	REdit->SelAttributes->Style = REdit->Font->Style;
 
	foundat = -1;
//---
//---
	TSearchTypes sOpts = TSearchTypes();
	sOpts << stWholeWord; // ����� ������ - �� ������
	// ���� �� ������ �������� ����...
	for (int i=0; i<SQLWords->Count; i++) {
		startat = pos;
		toend = REdit->Text.Length();
		// ���� ������� ��������� ����������...
		while (0 <= (foundat = REdit->FindTextA(SQLWords->Strings[i], startat, toend, sOpts))) {
			// �������� �����
			chrgNew.cpMin = foundat;
			chrgNew.cpMax = foundat + SQLWords->Strings[i].Length();
			::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
			// � ��������� ������
			REdit->SelAttributes->Color = HiLite_wds.FontColor;
			REdit->SelAttributes->Style = HiLite_wds.FontStyle;
			// ��������� ���������� ��� ������
			startat += SQLWords->Strings[i].Length();
			toend = REdit->Text.Length() - startat;
		}
	}

	sOpts >> stWholeWord; // ����� ������ - �� ������
	// ���� �� ������ �������� ��������...
	for (int i=0; i<SQLSymbols->Count; i++) {
		startat = pos;
		toend = REdit->Text.Length();
		// ���� ������� ��������� ����������...
		while (0 <= (foundat = REdit->FindTextA(SQLSymbols->Strings[i], startat, toend, sOpts))) {
			// �������� �����
			chrgNew.cpMin = foundat;
			chrgNew.cpMax = foundat + SQLSymbols->Strings[i].Length();
			::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
			// � ��������� ������
			REdit->SelAttributes->Color = HiLite_symb.FontColor;
			REdit->SelAttributes->Style = HiLite_symb.FontStyle;
			// ��������� ���������� ��� ������
			startat += SQLSymbols->Strings[i].Length();
			toend = REdit->Text.Length() - startat;
		}
	}

	// ��������������� ��������� ������� / ���������
	::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgSave);
 
	// ��������������� �����������
	::SendMessage(REdit->Handle, WM_SETREDRAW, true, 0);
	::InvalidateRect(REdit->Handle, 0, true);
	// ��������������� ����� �������
	::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, eventMask);

	/////////////////////////// �������� �������
//	StaticText2->Caption = FloatToStr((GetTickCount()-start)/1000.);
//---
//---
}


void __fastcall TFraLightRichEdit::HighLightDynamic()
{
        TRichEdit *REdit = RichEdit1;
	// ���������� �� 2 ����� �����
	int pos = ::SendMessage(REdit->Handle, EM_FINDWORDBREAK,
				WB_MOVEWORDLEFT, REdit->SelStart);
	pos = ::SendMessage(REdit->Handle, EM_FINDWORDBREAK,
				WB_MOVEWORDLEFT, pos);
	HighLight(pos);
}


void __fastcall TFraLightRichEdit::RichEdit1KeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  bool bHL = true;
	if (!(Key==VK_RETURN || Key==VK_BACK || Key==VK_SPACE || Key==VK_TAB ||
									RichEdit1->SelStart > 1)) return; // ���������, ����� �� ������ ������������...

	if (bHL) HighLightDynamic(); // bHL - ������ ����������-���� ��� ���������/���������� ������ ���������

}
//---------------------------------------------------------------------------
