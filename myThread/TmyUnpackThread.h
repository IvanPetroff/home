//---------------------------------------------------------------------------

#ifndef TmyUnpackThreadH
#define TmyUnpackThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <jpeg.hpp>
#include <memory>
//---------------------------------------------------------------------------
class TmyUnpackThread : public TThread
{
private:
    TImage* img;
    TJPEGImage* jpg;

    void __fastcall _GetBitmap();

protected:
    void __fastcall Execute();
public:
    __fastcall TmyUnpackThread(bool CreateSuspended, TImage* img, TJPEGImage* jpg);
};
//---------------------------------------------------------------------------
#endif
 