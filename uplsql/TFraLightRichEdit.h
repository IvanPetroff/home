//---------------------------------------------------------------------------


#ifndef TFraLightRichEditH
#define TFraLightRichEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
struct THiLt
{
	TColor FontColor;
	TFontStyles FontStyle;
};


class TFraLightRichEdit : public TFrame
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        void __fastcall RichEdit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	TStringList *SQLWords /* слова */, *SQLSymbols /* символы */;
	THiLt HiLite_wds /* слова */, HiLite_symb /* символы */;
        void __fastcall HighLightDynamic();
public:		// User declarations
        __fastcall TFraLightRichEdit(TComponent* Owner);
        void __fastcall HighLight(int pos);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraLightRichEdit *FraLightRichEdit;
//---------------------------------------------------------------------------
#endif
