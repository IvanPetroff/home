//---------------------------------------------------------------------------

#ifndef TmyThreadFileH
#define TmyThreadFileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <jpeg.hpp>
#include <memory>
//---------------------------------------------------------------------------
class TmyThreadFile : public TThread
{
private:
    void __fastcall _LoadFile();
    void __fastcall _GetBitmap();
    std::auto_ptr<Graphics::TBitmap> Bitmap;
    TJPEGImage* jpg;
    int SizeX;
    int SizeY;
    char* cFileName;
protected:
    void __fastcall Execute();
public:
    __fastcall TmyThreadFile(AnsiString inFileName, int inSizeX, int inSizeY);
    void __fastcall ShowImage(TImage* toImg);

    AnsiString FileName;
    bool isComplete;
};
//---------------------------------------------------------------------------
#endif
