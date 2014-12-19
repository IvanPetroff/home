//---------------------------------------------------------------------------

#ifndef TFraLightRichEditH
#define TFraLightRichEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFraParse.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFraLightRichEdit : public TFraParse
{
__published:	// IDE-managed Components
        TRichEdit *REdit;
private:	// User declarations
    virtual void __fastcall PaintText(int begWord, int endWord, TColor inFontColor, TFontStyles inFontStyle);
public:		// User declarations
        __fastcall TFraLightRichEdit(TComponent* Owner);
        void __fastcall HighLight(int pos);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraLightRichEdit *FraLightRichEdit;
//---------------------------------------------------------------------------
#endif
