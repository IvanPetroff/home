//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <ExtCtrls.hpp>
#include <vector.h>
#include "TmyThreadFile.h"


#define MAX_CACHED_SIZE 2

class TmyCachedFile {
private:

public:
    TmyCachedFile() {
        FileName = "";
        cntUse = 0;
    }

    AnsiString FileName;
    int cntUse;
};

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TFileListBox *FileListBox1;
    TImage *Image1;
    void __fastcall Image1Click(TObject *Sender);
    void __fastcall Image1DblClick(TObject *Sender);
private:	// User declarations
    void __fastcall myTerminate(TObject *Sender);
    void __fastcall _GetBitmap(TImage* img);

    void __fastcall Init();
    void __fastcall LoadFile(AnsiString FileName);
    void __fastcall ShowFile(AnsiString FileName);
    vector <TmyThreadFile*> CachedFiles;



public:		// User declarations
    TImage* CurrentImage;
    TImage* NextImage;
    void __fastcall SetImageSize(int Width, int Height);


    AnsiString CurrentFileName;
    AnsiString NextFileName;
    void __fastcall LoadCurrentImage(AnsiString FileName);
    void __fastcall LoadNextImage(AnsiString FileName);
    void __fastcall OnCurrentImageLoaded(TObject *Sender);
    void __fastcall OnNextImageLoaded(TObject *Sender);
    void __fastcall ShowCurrentImage(TImage* img);
    void __fastcall ShowNextImage(TImage* img);

    bool isCurrentImageLoaded;
    bool isNextImageLoaded;
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
