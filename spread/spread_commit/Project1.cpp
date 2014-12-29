//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Project1.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("TFraBase.cpp", FraBase); /* TFrame: File Type */
USEFORM("TFraSZ.cpp", FraSZ); /* TFrame: File Type */
USEFORM("TFraPrcFact.cpp", FraPrcFact); /* TFrame: File Type */
USEFORM("TFraFactNew.cpp", FraFactNew); /* TFrame: File Type */
USEFORM("Unit2.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
