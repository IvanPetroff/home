//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraSZ.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TFraBase"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TFraSZ *FraSZ;
//---------------------------------------------------------------------------
__fastcall TFraSZ::TFraSZ(TComponent* Owner)
        : TFraBase(Owner)
{
}
//---------------------------------------------------------------------------
