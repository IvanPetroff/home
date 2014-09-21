//---------------------------------------------------------------------------

#ifndef TImgThreadH
#define TImgThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <memory>
#include <jpeg.hpp>
//---------------------------------------------------------------------------

#define CMD_LOAD 1
#define CMD_BITMAP 2
class TImgThread : public TThread
{
private:
    std::auto_ptr<TJPEGImage> l_jpg;
    TImage* img;
    AnsiString FileName;
    int Quality;
    void __fastcall _LoadJpeg();
    void __fastcall _GetBitmap();
    char cmd;
    bool flgRun;
    void __fastcall _SetLoadCmd();
    void __fastcall _SetBitmapCmd();
protected:
    void __fastcall Execute();
public:
    __fastcall TImgThread(bool CreateSuspended);
    void __fastcall LoadJpeg(AnsiString FileName, int Quality=3);
    void __fastcall GetBitmap(TImage* inImage, int Quality=-1);
};
//---------------------------------------------------------------------------
#endif
