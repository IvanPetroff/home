//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraLightRichEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFraParse"
#pragma resource "*.dfm"
TFraLightRichEdit *FraLightRichEdit;
//---------------------------------------------------------------------------
__fastcall TFraLightRichEdit::TFraLightRichEdit(TComponent* Owner)
        : TFraParse(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFraLightRichEdit::HighLight(int pos)
// http://cbuilder.ru/index.php?topic=5870.30
{
    DWORD start=GetTickCount();
    ///////////////////////////

    // �������� ����� �������
    int eventMask = ::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, 0);
    // ��������� �����������
    ::SendMessage(REdit->Handle, WM_SETREDRAW, false, 0);
    // ���������� ���������
    CHARRANGE chrgSave;
    ::SendMessage(REdit->Handle, EM_EXGETSEL, 0, (LPARAM) &chrgSave);

    // ����� ��������������
    PaintText(pos, -1, REdit->Font->Color, REdit->Font->Style);

    // ���� �� ������ �������� ����...
    ParseText(REdit->Text);

    // ��������������� ��������� ������� / ���������
    ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgSave);
    // ��������������� �����������
    ::SendMessage(REdit->Handle, WM_SETREDRAW, true, 0);
    ::InvalidateRect(REdit->Handle, 0, true);
    // ��������������� ����� �������
    ::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, eventMask);
}

void __fastcall TFraLightRichEdit::PaintText(int begWord, int endWord, TColor inFontColor, TFontStyles inFontStyle)
{
    CHARRANGE chrgNew;
    chrgNew.cpMin = begWord;
    chrgNew.cpMax = endWord;
    ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
    // � ��������� ������
    REdit->SelAttributes->Color = inFontColor;
    REdit->SelAttributes->Style = inFontStyle;
}
