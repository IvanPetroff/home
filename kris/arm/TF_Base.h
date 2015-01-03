//---------------------------------------------------------------------------

#ifndef TF_BaseH
#define TF_BaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TF_Base : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TF_Base(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Base *F_Base;
//---------------------------------------------------------------------------
#endif
