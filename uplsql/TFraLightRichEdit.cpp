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
    myWords["CONSTRUCTOR"] = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["OVERRIDING"] = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["MEMBER"] = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["FUNCTION"] = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["PROCEDURE"] = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["BEGIN"] = THiLt(clRed, TFontStyles() << fsBold);
    myWords["END"] = THiLt(clRed, TFontStyles() << fsBold);

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
//	HiLite_wds.FontColor = clBlue; // ����� �����
//	HiLite_wds.FontStyle = TFontStyles() << fsBold; // ������
//	// �������������� ��������
//	HiLite_symb.FontColor = clRed; // ������� �����
//	HiLite_symb.FontStyle = TFontStyles(); // �� ������
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

        AnsiString State="";
        int begWord = 0;
        int endWord = 0;
        AnsiString Symbol = "~'!@#$%^&*()-=+\\|/?,.[]{}\"`;\n\t\r ";
        int length = REdit->Text.Length();
        char PredCh = 0;
        char Ch = 0;
        for (int I = 0; I < length; I++) {
            bool isWord = false;
            PredCh = Ch;
            Ch = REdit->Text.c_str()[I];
            if (Symbol.Pos(Ch)==0) {
                isWord = true;
            }
            if (State=="") {
                if (isWord) {
                    begWord = I;
                    State = "WORD";
                    continue;
                }
            }
            if (State=="WORD") {
                if (isWord==false) {
                    endWord = I;
                    State = "";

                    AnsiString myWord = REdit->Text.SubString(begWord+1, endWord-begWord).UpperCase();
                    map<AnsiString,THiLt>::iterator it = myWords.find(myWord);
                    if (it != myWords.end()) {
                        chrgNew.cpMin = begWord;
                        chrgNew.cpMax = endWord;
                        ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
                        // � ��������� ������
                        REdit->SelAttributes->Color = it->second.FontColor;
                        REdit->SelAttributes->Style = it->second.FontStyle;
                    }
                    int tt=0;
                }
//                continue;
            }

                if (Ch=='*' && PredCh=='/') {
                  int x=0;
                }

            if (State=="") {
                if (Ch=='*' && PredCh=='/') {
                    begWord = I-1;
                    State = "COMMENT_BLOCK";
                    continue;
                }
            }
            if (State=="COMMENT_BLOCK") {
                if (Ch=='/' && PredCh=='*') {
                    endWord = I+1;
                    State = "";
                    chrgNew.cpMin = begWord;
                    chrgNew.cpMax = endWord;
                    ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
                    // � ��������� ������
                    REdit->SelAttributes->Color = clSilver;
                    REdit->SelAttributes->Style = TFontStyles();
                }
            }
            if (State=="") {
                if (Ch=='-' && PredCh=='-') {
                    begWord = I-1;
                    State = "COMMENT_LINE";
                    continue;
                }
            }
            if (State=="COMMENT_LINE") {
                if (Ch=='\n' ) {
                    endWord = I+1;
                    State = "";
                    chrgNew.cpMin = begWord;
                    chrgNew.cpMax = endWord;
                    ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
                    // � ��������� ������
                    REdit->SelAttributes->Color = clSilver;
                    REdit->SelAttributes->Style = TFontStyles();
                }
                continue;
            }

        }

//	for (int i=0; i<SQLWords->Count; i++) {
//		startat = pos;
//		toend = REdit->Text.Length();
//		// ���� ������� ��������� ����������...
//		while (0 <= (foundat = REdit->FindTextA(SQLWords->Strings[i], startat, toend, sOpts))) {
//			// �������� �����
//			chrgNew.cpMin = foundat;
//			chrgNew.cpMax = foundat + SQLWords->Strings[i].Length();
//			::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
//			// � ��������� ������
//			REdit->SelAttributes->Color = HiLite_wds.FontColor;
//			REdit->SelAttributes->Style = HiLite_wds.FontStyle;
//			// ��������� ���������� ��� ������
//			startat += SQLWords->Strings[i].Length();
//			toend = REdit->Text.Length() - startat;
//		}
//	}
//
//	sOpts >> stWholeWord; // ����� ������ - �� ������
//	// ���� �� ������ �������� ��������...
//	for (int i=0; i<SQLSymbols->Count; i++) {
//		startat = pos;
//		toend = REdit->Text.Length();
//		// ���� ������� ��������� ����������...
//		while (0 <= (foundat = REdit->FindTextA(SQLSymbols->Strings[i], startat, toend, sOpts))) {
//			// �������� �����
//			chrgNew.cpMin = foundat;
//			chrgNew.cpMax = foundat + SQLSymbols->Strings[i].Length();
//			::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
//			// � ��������� ������
//			REdit->SelAttributes->Color = HiLite_symb.FontColor;
//			REdit->SelAttributes->Style = HiLite_symb.FontStyle;
//			// ��������� ���������� ��� ������
//			startat += SQLSymbols->Strings[i].Length();
//			toend = REdit->Text.Length() - startat;
//		}
//	}

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
