//---------------------------------------------------------------------------

#ifndef TImgThreadH
#define TImgThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <memory>
#include <jpeg.hpp>
//---------------------------------------------------------------------------

#define CMD_NONE 0
#define CMD_LOAD 1
#define CMD_BITMAP 2
class TImgThread : public TThread
{
private:
    std::auto_ptr<TJPEGImage> l_jpg;
    std::auto_ptr<Graphics::TBitmap> Bitmap;
    TImage* img;
    char        cmd;
    bool        flgRun;

    int Quality;
    void __fastcall _LoadJpegFile();
    void __fastcall _GetBitmap();
    void __fastcall _SetLoadCmd();
    void __fastcall _SetBitmapCmd();
    void __fastcall _WaitForThreadSuspended();

protected:
    void __fastcall Execute();
public:
    __fastcall TImgThread();
    void __fastcall LoadJpegFile(AnsiString FileName, int Quality=3);
    void __fastcall GetBitmap(TImage* toImage, int Quality=-1);
    AnsiString  FileName;
};
//---------------------------------------------------------------------------
#endif
