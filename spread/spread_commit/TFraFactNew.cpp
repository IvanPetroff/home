//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraFactNew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TFraBase"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TFraFactNew *FraFactNew;
//---------------------------------------------------------------------------
__fastcall TFraFactNew::TFraFactNew(TComponent* Owner)
        : TFraBase(Owner)
{
}
//---------------------------------------------------------------------------
