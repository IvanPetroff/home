//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TEditAvto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TEditorBase"
#pragma resource "*.dfm"
TEditAvto *EditAvto;
//---------------------------------------------------------------------------
__fastcall TEditAvto::TEditAvto(TComponent* Owner)
        : TEditorBase(Owner)
{
}
//---------------------------------------------------------------------------
