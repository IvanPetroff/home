//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("ChildWin.cpp", MDIChild);
USERES("mdiapp.res");
USEFORM("about.cpp", AboutBox);
USEFORM("TF_Base.cpp", F_Base);
USEFORM("TF_MDI.cpp", F_MDI);
USEFORM("TF_SprQuestion.cpp", F_SprQuestion);
USEFORM("TF_Report.cpp", F_Report);
USEFORM("TF_Person.cpp", F_Person);
USEFORM("TF_PersonList.cpp", F_PersonList);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TAboutBox), &AboutBox);
         Application->CreateForm(__classid(TF_Person), &F_Person);
         Application->CreateForm(__classid(TF_PersonList), &F_PersonList);
         Application->Run();

	return 0;
}
//---------------------------------------------------------------------
