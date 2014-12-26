//---------------------------------------------------------------------------

#ifndef TFraFactNewH
#define TFraFactNewH
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
class TFraFactNew : public TFraBase
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TFraFactNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraFactNew *FraFactNew;
//---------------------------------------------------------------------------
#endif
