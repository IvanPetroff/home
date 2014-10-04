//---------------------------------------------------------------------------

#ifndef TFormImageH
#define TFormImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFraBase.h"
#include "TFraImage.h"

#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
#include <memory.h>
#include "TmyThreadShow.h"
//---------------------------------------------------------------------------
class TFormImage : public TForm
{
__published:	// IDE-managed Components
    TFraImage *FraImage1;
    TTimer *Timer1;
    TStatusBar *msg;
    TFileListBox *FileListBox1;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    void __fastcall NextFile();
    void __fastcall PrevFile();
    void __fastcall LoadFileListBox(AnsiString inFileName);
    void __fastcall ShowImage(AnsiString FileName);
    AnsiString FileName;

    std::auto_ptr <TmyThreadShow> myThreadShow;
    void __fastcall LoadNextFile();

public:		// User declarations
    __fastcall TFormImage(TComponent* Owner);
    void __fastcall LoadImage(AnsiString FileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImage *FormImage;
//---------------------------------------------------------------------------
#endif
