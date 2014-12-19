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
	TStringList *SQLWords /* ����� */, *SQLSymbols /* ������� */;
	THiLt HiLite_wds /* ����� */, HiLite_symb /* ������� */;
        void __fastcall HighLightDynamic();
public:		// User declarations
        __fastcall TFraLightRichEdit(TComponent* Owner);
        void __fastcall HighLight(int pos);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraLightRichEdit *FraLightRichEdit;
//---------------------------------------------------------------------------
#endif
