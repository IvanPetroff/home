//---------------------------------------------------------------------------

#ifndef TFraImageH
#define TFraImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFraBase.h"
#include <ExtCtrls.hpp>
#include <memory>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFraImage : public TFraBase
{
__published:	// IDE-managed Components
    TImage *img;
    TPanel *pFileName;
    void __fastcall FrameResize(TObject *Sender);
private:	// User declarations
    TJPEGImage * l_jpg;
    AnsiString FileName;
    void __fastcall LoadJpeg();
public:		// User declarations
    __fastcall TFraImage(TComponent* Owner);
    __fastcall ~TFraImage();
    void __fastcall LoadImage(AnsiString inFileName);
    void __fastcall ShowImage(int Q);
    void __fastcall FastShowImage(int Q);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraImage *FraImage;
//---------------------------------------------------------------------------
#endif
