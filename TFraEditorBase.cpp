//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraEditorBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFraEditorBase *FraEditorBase;
//---------------------------------------------------------------------------
__fastcall TFraEditorBase::TFraEditorBase(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
