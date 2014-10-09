//---------------------------------------------------------------------------

#ifndef TmyThreadShowH
#define TmyThreadShowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <vector.h>
#include "TmyThreadFile.h"
//---------------------------------------------------------------------------

#define MAX_CACHED_SIZE 10

class TmyThreadShow : public TThread
{
private:
    int __fastcall GetIndexFile(AnsiString FileName);
    bool __fastcall isLastSlotEmpty();
    void __fastcall FreeLastCacheSlot();
    void __fastcall ShiftDownCacheSlots();
    bool __fastcall MoveUpFileCacheSlot(AnsiString FileName);
    void __fastcall SendStopSignal();
    void __fastcall SendRunSignal();
    void __fastcall WaitToStop();
    void __fastcall _Show();
    void __fastcall ClearCache();
    TmyThreadFile* FileToShow;
    bool flgStop;
    AnsiString LastShow;

protected:
    void __fastcall Execute();
    vector<TmyThreadFile*> Files;
public:
    __fastcall TmyThreadShow(TImage* img);
    void __fastcall LoadFile(AnsiString FileName, TThreadPriority Priority = tpLowest);
    void __fastcall ShowFile(AnsiString FileName);
    void __fastcall SetImage(TImage* img);
    TImage* img;

};
//---------------------------------------------------------------------------
#endif
