//---------------------------------------------------------------------------

#ifndef TEditAvtoH
#define TEditAvtoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TEditorBase.h"
//---------------------------------------------------------------------------
class TEditAvto : public TEditorBase
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TEditAvto(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditAvto *EditAvto;
//---------------------------------------------------------------------------
#endif
