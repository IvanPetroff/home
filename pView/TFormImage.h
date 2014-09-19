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
//---------------------------------------------------------------------------
class TFormImage : public TForm
{
__published:	// IDE-managed Components
    TFraImage *FraImage1;
    TTimer *Timer1;
    TStatusBar *msg;
    TFileListBox *FileListBox1;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
    void __fastcall NextFile();
    void __fastcall PrevFile();
public:		// User declarations
    __fastcall TFormImage(TComponent* Owner);
    void __fastcall LoadImage(AnsiString FileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImage *FormImage;
//---------------------------------------------------------------------------
#endif
