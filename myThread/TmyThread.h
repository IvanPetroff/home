//---------------------------------------------------------------------------

#ifndef TmyThreadH
#define TmyThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <jpeg.hpp>
#include <memory>

//---------------------------------------------------------------------------
class TmyThread : public TThread
{
private:
    AnsiString FileName;
    TImage* img;
    TJPEGImage* jpg;

    void __fastcall _GetBitmap();
protected:
    void __fastcall Execute();
public:
    __fastcall TmyThread(bool CreateSuspended, AnsiString FileName, TImage* img);
};
//---------------------------------------------------------------------------
#endif
