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
#include "TImgThread.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
#include <memory.h>
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
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    void __fastcall NextFile();
    void __fastcall PrevFile();
    void __fastcall LoadFileListBox(AnsiString inFileName);
    std::auto_ptr<TImgThread> imgThread;
    std::auto_ptr<TImgThread> imgThreadPrev;
    std::auto_ptr<TImgThread> imgThreadNext;
    void __fastcall ShowImage(TImgThread* imgThread);
    AnsiString FileName;
public:		// User declarations
    __fastcall TFormImage(TComponent* Owner);
    void __fastcall LoadImage(AnsiString FileName, TImgThread* imgThread);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImage *FormImage;
//---------------------------------------------------------------------------
#endif
