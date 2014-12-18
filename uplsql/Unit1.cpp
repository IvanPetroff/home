//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <memory>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "OdacVcl"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  OraSession1->Connected = true;
  std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
  Q->Session = OraSession1;
  Q->SQL->Text = "select distinct object_name from all_objects where owner=user and object_type like 'TYPE%' order by 1";
  for (Q->Open(); !Q->Eof; Q->Next()) {
    ListBox1->Items->Add(Q->FieldByName("object_name")->AsString);
  }
}
//---------------------------------------------------------------------------
