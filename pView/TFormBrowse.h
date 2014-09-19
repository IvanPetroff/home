//---------------------------------------------------------------------------

#ifndef TFormBrowseH
#define TFormBrowseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <FileCtrl.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <vector.h>
#include "TFraBase.h"
#include "TFraImage.h"
#include "TFraPreview.h"

//---------------------------------------------------------------------------
class TFormBrowse : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TDirectoryListBox *DirectoryListBox1;
    TPanel *Panel1;
    TDriveComboBox *DriveComboBox1;
    TFileListBox *FileListBox1;
    TScrollBox *ScrollBox1;
    TSplitter *Splitter1;
    TSplitter *Splitter2;
    TFraImage *FraImage1;
    void __fastcall FileListBox1Change(TObject *Sender);
    void __fastcall ScrollBox1MouseWheel(TObject *Sender,
          TShiftState Shift, int WheelDelta, TPoint &MousePos,
          bool &Handled);
    void __fastcall ScrollBox1MouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
    void __fastcall ScrollBox1MouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
private:	// User declarations
    void foo();

    vector<TFraPreview*> mas_preview;
    vector<TImage*> mas_img;
public:		// User declarations
    __fastcall TFormBrowse(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBrowse *FormBrowse;
//---------------------------------------------------------------------------
#endif
