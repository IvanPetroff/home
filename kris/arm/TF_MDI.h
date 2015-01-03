//---------------------------------------------------------------------------

#ifndef TF_MDIH
#define TF_MDIH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TF_Base.h"
//---------------------------------------------------------------------------
class TF_MDI : public TF_Base
{
__published:	// IDE-managed Components
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TF_MDI(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_MDI *F_MDI;
//---------------------------------------------------------------------------
#endif
