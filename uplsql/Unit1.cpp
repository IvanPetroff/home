//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <memory>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "OdacVcl"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
TStringList* KeyWds;

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  KeyWds = new TStringList;
  KeyWds->Add("select");
  OraSession1->Connected = true;
  std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
  Q->Session = OraSession1;
  Q->SQL->Text = "select distinct object_name from all_objects where owner=user and object_type like 'TYPE%' order by 1";
  for (Q->Open(); !Q->Eof; Q->Next()) {
    ListBox1->Items->Add(Q->FieldByName("object_name")->AsString);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HighLight(TRichEdit *REdit, int pos)
// http://cbuilder.ru/index.php?topic=5870.30
{
	DWORD start=GetTickCount();
	///////////////////////////

	// получаем маску событий
	int eventMask = ::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, 0);
	// отключаем перерисовку
	::SendMessage(REdit->Handle, WM_SETREDRAW, false, 0);
	// запоминаем выделение
	CHARRANGE chrgSave, chrgNew;
	::SendMessage(REdit->Handle, EM_EXGETSEL, 0, (LPARAM) &chrgSave);

	int startat, toend, foundat, caretpos, slth;

	// сброс форматирования
	chrgNew.cpMin = pos;
	chrgNew.cpMax = -1;
	::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
	REdit->SelAttributes->Color = REdit->Font->Color;
	REdit->SelAttributes->Style = REdit->Font->Style;

	foundat = -1;

	// опции поиска - по словам
	TSearchTypes sOpts = TSearchTypes();
	sOpts << stWholeWord;

	// ищем по списку ключевых слов...
	for (int i=0; i<KeyWds->Count; i++) {
		startat = pos;
		toend = REdit->Text.Length();
		// если найдено следующее совпадение...
		while (0 <= (foundat = REdit->FindTextA(KeyWds->Strings[i], startat, toend, sOpts))) {
			// выделяем текст
			chrgNew.cpMin = foundat;
			chrgNew.cpMax = foundat + KeyWds->Strings[i].Length();
			::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgNew);
			// и применяем формат
			REdit->SelAttributes->Color = clRed;//HiLite.FontColor;
//			REdit->SelAttributes->Style = HiLite.FontStyle;
			// обновляем переменные для поиска
			startat += KeyWds->Strings[i].Length();
			toend = REdit->Text.Length() - startat;
		}
	}
 
	// восстанавливаем положение каретки / выделение
	::SendMessage(REdit->Handle, EM_EXSETSEL, 0, (LPARAM) &chrgSave);
 
	// восстанавливаем перерисовку
	::SendMessage(REdit->Handle, WM_SETREDRAW, true, 0);
	::InvalidateRect(REdit->Handle, 0, true);
	// восстанавливаем маску событий
	::SendMessage(REdit->Handle, EM_SETEVENTMASK, 0, eventMask);
 
	/////////////////////////// проверка времени
//	StaticText2->Caption = FloatToStr((GetTickCount()-start)/1000.);
}
void __fastcall TForm1::RichEdit1Change(TObject *Sender)
{
HighLight( RichEdit1, 0);
}
//---------------------------------------------------------------------------
