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

    // получаем маску событий
    int eventMask = ::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, 0);
    // отключаем перерисовку
    ::SendMessage(REdit->Handle, WM_SETREDRAW, false, 0);
    // запоминаем выделение
    CHARRANGE chrgSave;
    ::SendMessage(REdit->Handle, EM_EXGETSEL, 0, (LPARAM) &chrgSave);

    // сброс форматирования
    PaintText(pos, -1, REdit->Font->Color, REdit->Font->Style);

    // ищем по списку ключевых слов...
    ParseText(REdit->Text);

    // восстанавливаем положение каретки / выделение
    ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgSave);
    // восстанавливаем перерисовку
    ::SendMessage(REdit->Handle, WM_SETREDRAW, true, 0);
    ::InvalidateRect(REdit->Handle, 0, true);
    // восстанавливаем маску событий
    ::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, eventMask);
}

void __fastcall TFraLightRichEdit::PaintText(int begWord, int endWord, TColor inFontColor, TFontStyles inFontStyle)
{
    CHARRANGE chrgNew;
    chrgNew.cpMin = begWord;
    chrgNew.cpMax = endWord;
    ::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
    // и применяем формат
    REdit->SelAttributes->Color = inFontColor;
    REdit->SelAttributes->Style = inFontStyle;
}
