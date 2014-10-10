//---------------------------------------------------------------------------

#ifndef TmyInplaceEditorH
#define TmyInplaceEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TInplaceEditorBase.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TmyInplaceEditor : public TInplaceEditorBase
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TEdit *E_Cell;
    void __fastcall E_CellKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
    virtual void        __fastcall Show         (TRect Rect);
    virtual void        __fastcall SaveVal      ();
    virtual void        __fastcall LoadVal      ();
public:		// User declarations
    __fastcall TmyInplaceEditor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmyInplaceEditor *myInplaceEditor;
//---------------------------------------------------------------------------
#endif
