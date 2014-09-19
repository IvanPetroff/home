//---------------------------------------------------------------------------


#ifndef TFraBaseH
#define TFraBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFraBase : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TFraBase(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraBase *FraBase;
//---------------------------------------------------------------------------
#endif
