//---------------------------------------------------------------------------

#ifndef TFraPrcFactH
#define TFraPrcFactH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include "TFraBase.h"
#include <Db.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class TFraPrcFact : public TFraBase
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TFraPrcFact(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraPrcFact *FraPrcFact;
//---------------------------------------------------------------------------
#endif
