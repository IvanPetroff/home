//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Project1.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("..\..\lib\TInplaceEditorBase\TInplaceEditorBase.cpp", InplaceEditorBase); /* TFrame: File Type */
USEFORM("TmyInplaceEditor.cpp", myInplaceEditor); /* TFrame: File Type */
USEUNIT("..\..\lib\TInplaceEditorBase\THorizont.cpp");
USEUNIT("..\..\lib\TmyQuery\TmyQuery.cpp");
USEUNIT("..\..\lib\TmyStringList\TmyStringList.cpp");
USEFORM("TEditorBase.cpp", EditorBase); /* TFrame: File Type */
USEFORM("TEditorGrid.cpp", EditorGrid); /* TFrame: File Type */
USEFORM("TEditAvto.cpp", EditAvto); /* TFrame: File Type */
USEFORM("TEditSimple.cpp", EditSimple); /* TFrame: File Type */
USEFORM("TFraBase.cpp", FraBase); /* TFrame: File Type */
USEFORM("TFraGasPoint.cpp", FraGasPoint); /* TFrame: File Type */
USEFORM("TFraTankGasolineList.cpp", FraTankGasolineList); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
