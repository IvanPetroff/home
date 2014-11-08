//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Cash.res");
USEFORM("TMainForm.cpp", MainForm);
USEFORM("TEditorBase.cpp", EditorBase); /* TFrame: File Type */
USEFORM("TEditorGrid.cpp", EditorGrid); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
