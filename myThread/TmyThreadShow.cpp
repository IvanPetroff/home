//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TmyThreadShow.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit2::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------


__fastcall TmyThreadShow::TmyThreadShow(TImage* img)
    : TThread(true)
{
    for (int I = 0; I < MAX_CACHED_SIZE; I++) {
        Files.push_back(0);
    }
    this->flgStop = true;
    this->FileToShow = 0;
    this->img = img;
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::Execute()
{
    //---- Place thread code here ----
    while (true) {
        if (flgStop) {
            FileToShow = 0;
            this->Suspend();
        }
        if (FileToShow != 0) {
            try {
                if (FileToShow->isComplete) {
                    this->Synchronize(_Show);
                    flgStop = true;
                }
            }
            catch(...) {
                flgStop = true;
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmyThreadShow::_Show()
{
    FileToShow->ShowImage(img);
}


int __fastcall TmyThreadShow::GetIndexFile(AnsiString FileName)
{
    for (int I = 0; I < MAX_CACHED_SIZE; I++) {
        if ( Files[I] == 0) continue;
        if (Files[I]->FileName==FileName) {
            return I;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::FreeLastCacheSlot()
{
    if ( isLastSlotEmpty()) return;
    if (Files[MAX_CACHED_SIZE-1]==FileToShow) {
        SendStopSignal();
        WaitToStop();
    }
    delete Files[MAX_CACHED_SIZE-1];
    Files[MAX_CACHED_SIZE-1] = 0;
}
//---------------------------------------------------------------------------


bool __fastcall TmyThreadShow::isLastSlotEmpty()
{
    return (Files[MAX_CACHED_SIZE-1] == 0);
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::ShiftDownCacheSlots()
{
    for (int I = MAX_CACHED_SIZE-1; I>0; I--) {
        Files[I] = Files[I-1];
    }
    Files[0] = 0;
}
//---------------------------------------------------------------------------


bool __fastcall TmyThreadShow::MoveUpFileCacheSlot(AnsiString FileName)
{
    int IndexFile = GetIndexFile(FileName);
    if (IndexFile<0) return false;
    swap( Files[0], Files[IndexFile]);
    return true;
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::SendStopSignal()
{
    flgStop = true;
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::SendRunSignal()
{
    flgStop = false;
    this->Resume();
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::WaitToStop()
{
    while (!this->Suspended) {
        SendStopSignal();
        Application->ProcessMessages();
        Sleep(10);
    }
}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::ShowFile(AnsiString FileName)
{
    if (!MoveUpFileCacheSlot(FileName)) {
        LoadFile(FileName);
        if (!MoveUpFileCacheSlot(FileName)) {
            return;
        }
    }

    SendStopSignal();
    WaitToStop();
    FileToShow = Files[0];
    SendRunSignal();

}
//---------------------------------------------------------------------------


void __fastcall TmyThreadShow::LoadFile(AnsiString FileName)
{
    if (MoveUpFileCacheSlot(FileName)) {
        return;
    }

    FreeLastCacheSlot();
    ShiftDownCacheSlots();

    Files[0] = new TmyThreadFile(FileName, 800, 600);
}
//---------------------------------------------------------------------------
