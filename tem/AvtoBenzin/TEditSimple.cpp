//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditSimple.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TEditorBase"
#pragma resource "*.dfm"
TEditSimple *EditSimple;
//---------------------------------------------------------------------------
__fastcall TEditSimple::TEditSimple(TComponent* Owner)
        : TEditorBase(Owner)
{
}
//---------------------------------------------------------------------------
