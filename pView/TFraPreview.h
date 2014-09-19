//---------------------------------------------------------------------------


#ifndef TFraPreviewH
#define TFraPreviewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <memory>
#include <jpeg.hpp>
#include "TFraImage.h"
//---------------------------------------------------------------------------
class TFraPreview : public TFrame
{
__published:	// IDE-managed Components
    TPanel *pFileName;
    TShape *Shape1;
    TImage *img;
    TCheckBox *CheckBox1;
    TTimer *Timer1;
    void __fastcall imgDblClick(TObject *Sender);
    void __fastcall imgClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    static TFraPreview* Selected;
public:		// User declarations
    __fastcall TFraPreview(TComponent* Owner);
    inline __fastcall virtual ~TFraPreview(void) {
        Selected = 0;
    }
    static TFraImage* SelectedPreview;
};
TFraPreview* TFraPreview::Selected = 0;
TFraImage* TFraPreview::SelectedPreview = 0;
//---------------------------------------------------------------------------
extern PACKAGE TFraPreview *FraPreview;
//---------------------------------------------------------------------------
#endif
