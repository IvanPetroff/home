//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFraBase *FraBase;
//---------------------------------------------------------------------------
__fastcall TFraBase::TFraBase(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
