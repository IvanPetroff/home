//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraPrcFact.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TFraBase"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TFraPrcFact *FraPrcFact;
//---------------------------------------------------------------------------
__fastcall TFraPrcFact::TFraPrcFact(TComponent* Owner)
        : TFraBase(Owner)
{
}
//---------------------------------------------------------------------------
