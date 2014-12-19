//---------------------------------------------------------------------------


#ifndef TFraLightRichEditH
#define TFraLightRichEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <map.h>
//---------------------------------------------------------------------------
class THiLt
{
public:
	TColor FontColor;
	TFontStyles FontStyle;
        THiLt() {}
        THiLt(TColor inColor, TFontStyles inStyle) {
            FontColor = inColor;
            FontStyle = inStyle;
        }
};


class TFraLightRichEdit : public TFrame
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        void __fastcall RichEdit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	TStringList *SQLWords /* слова */, *SQLSymbols /* символы */;
//	THiLt HiLite_wds /* слова */, HiLite_symb /* символы */;
        void __fastcall HighLightDynamic();
public:		// User declarations
        __fastcall TFraLightRichEdit(TComponent* Owner);
        map<AnsiString,THiLt> myWords;
        void __fastcall HighLight(int pos);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraLightRichEdit *FraLightRichEdit;
//---------------------------------------------------------------------------
#endif
