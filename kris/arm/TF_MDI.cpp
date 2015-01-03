//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TF_MDI.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TF_Base"
#pragma resource "*.dfm"
TF_MDI *F_MDI;
//---------------------------------------------------------------------------
__fastcall TF_MDI::TF_MDI(TComponent* Owner)
    : TF_Base(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_MDI::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;    
}
//---------------------------------------------------------------------------
