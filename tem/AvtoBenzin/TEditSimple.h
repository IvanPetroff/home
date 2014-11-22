//---------------------------------------------------------------------------

#ifndef TEditSimpleH
#define TEditSimpleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TEditorBase.h"
//---------------------------------------------------------------------------
class TEditSimple : public TEditorBase
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TEditSimple(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditSimple *EditSimple;
//---------------------------------------------------------------------------
#endif
