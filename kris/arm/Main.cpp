//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
//---------------------------------------------------------------------------
#pragma link "DBAccess"
#pragma link "OdacVcl"
#pragma link "Ora"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateMDIChild(String Name)
{
	TMDIChild *Child;

	//--- create a new MDI child window ----
	Child = new TMDIChild(Application);
	Child->Caption = Name;
	if (FileExists (Name))
		Child->Memo1->Lines->LoadFromFile(Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileNew1Execute(TObject *Sender)
{
	CreateMDIChild("NONAME" + IntToStr(MDIChildCount + 1));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileOpen1Execute(TObject *Sender)
{
	if (OpenDialog->Execute())
		CreateMDIChild(OpenDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileExit1Execute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::dbAfterConnect(TObject *Sender)
{
    db->ExecSQL( "alter session set nls_numeric_characters='.,'", 0, 0);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::dbBeforeConnect(TObject *Sender)
{
    db->Password = "qwerty";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::print1Click(TObject *Sender)
{
    TF_Report* F = new TF_Report(Application);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SprQuestion1Click(TObject *Sender)
{
    TF_SprQuestion* F = new TF_SprQuestion(Application);
}
//---------------------------------------------------------------------------

