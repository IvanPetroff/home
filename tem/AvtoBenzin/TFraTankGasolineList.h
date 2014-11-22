//---------------------------------------------------------------------------

#ifndef TFraTankGasolineListH
#define TFraTankGasolineListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFraBase.h"
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include <Db.hpp>
#include <vector.h>
#include <map.h>
//---------------------------------------------------------------------------
class TFraTankGasolineList : public TFraBase
{
__published:	// IDE-managed Components
        TComboBox *CB;
        TOraQuery *Query;
        void __fastcall FrameMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
private:	// User declarations
    TOraSession* db;
    vector<map<AnsiString,AnsiString> > vTanks;
    AnsiString _GetCurrentTankTxt(){return vTanks[CB->ItemIndex]["TXT"];}
    AnsiString _GetCurrentTankMestoh(){return vTanks[CB->ItemIndex]["MESTOH"];}
    AnsiString _GetCurrentTankKod(){return vTanks[CB->ItemIndex]["KOD"];}
public:		// User declarations
        __fastcall TFraTankGasolineList(TComponent* Owner);
    void        __fastcall Init(TOraSession* in_db);
    void        __fastcall Load(AnsiString SKL);
    __property AnsiString CurrentTankTxt = {read=_GetCurrentTankTxt};
    __property AnsiString CurrentTankMestoh = {read=_GetCurrentTankMestoh};
    __property AnsiString CurrentTankKod = {read=_GetCurrentTankKod};
};
//---------------------------------------------------------------------------
extern PACKAGE TFraTankGasolineList *FraTankGasolineList;
//---------------------------------------------------------------------------
#endif
