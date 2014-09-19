//---------------------------------------------------------------------------

#ifndef TFormImageH
#define TFormImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFraBase.h"
#include "TFraImage.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormImage : public TForm
{
__published:	// IDE-managed Components
    TFraImage *FraImage1;
    TTimer *Timer1;
    TStatusBar *msg;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TFormImage(TComponent* Owner);
    void __fastcall LoadImage(AnsiString FileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImage *FormImage;
//---------------------------------------------------------------------------
#endif
