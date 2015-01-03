//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TF_SprQuestion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TF_MDI"
#pragma link "DBAccess"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "MemDS"
#pragma link "Ora"
#pragma resource "*.dfm"
TF_SprQuestion *F_SprQuestion;
//---------------------------------------------------------------------------
__fastcall TF_SprQuestion::TF_SprQuestion(TComponent* Owner)
    : TF_MDI(Owner)
{
}
//---------------------------------------------------------------------------
