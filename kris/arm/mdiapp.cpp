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
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TAboutBox), &AboutBox);
         Application->Run();

	return 0;
}
//---------------------------------------------------------------------
