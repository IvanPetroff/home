//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TF_Report.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TF_MDI"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TF_Report *F_Report;
//---------------------------------------------------------------------------
__fastcall TF_Report::TF_Report(TComponent* Owner)
    : TF_MDI(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_Report::Button1Click(TObject *Sender)
{
    QuickRep1->Preview();    
}
//---------------------------------------------------------------------------
