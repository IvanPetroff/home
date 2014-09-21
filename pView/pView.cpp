//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TFormBrowse.h"
#include "TFormImage.h"
USERES("pView.res");
USEFORM("TFormBrowse.cpp", FormBrowse);
USEFORM("TFraPreview.cpp", FraPreview); /* TFrame: File Type */
USEFORM("TFraBase.cpp", FraBase); /* TFrame: File Type */
USEFORM("TFraImage.cpp", FraImage); /* TFrame: File Type */
USEFORM("TFormImage.cpp", FormImage);
USEUNIT("TImgThread.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdline, int)
{
    AnsiString sCmd = String(cmdline).Trim();
    try
    {
         Application->Initialize();
         if (sCmd.IsEmpty()) {
             Application->CreateForm(__classid(TFormBrowse), &FormBrowse);
         }
         else {
             if (sCmd.SubString(1,1)=="\"") sCmd = sCmd.SubString(2,sCmd.Length());
             if (sCmd.SubString(sCmd.Length(),1)=="\"") sCmd = sCmd.SubString(1,sCmd.Length()-1);
             Application->CreateForm(__classid(TFormImage), &FormImage);
             Application->ProcessMessages();
             FormImage->LoadImage(sCmd);
         }
         Application->Run();
    }
    catch (Exception &exception)
    {
         ShowMessage(sCmd);
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
