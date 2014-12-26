//---------------------------------------------------------------------------


#ifndef TFraBaseH
#define TFraBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include <Db.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class TFraBase : public TFrame
{
__published:	// IDE-managed Components
        TOraQuery *DS;
        TOraDataSource *OraDataSource1;
        TDBGridEh *DBGridEh1;
private:	// User declarations
public:		// User declarations
        __fastcall TFraBase(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraBase *FraBase;
//---------------------------------------------------------------------------
#endif
