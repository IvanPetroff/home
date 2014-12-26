//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TFraBase *FraBase;
//---------------------------------------------------------------------------
__fastcall TFraBase::TFraBase(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
