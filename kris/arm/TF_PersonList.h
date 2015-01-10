//---------------------------------------------------------------------------

#ifndef TF_PersonListH
#define TF_PersonListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TF_MDI.h"
#include "DBAccess.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include <Db.hpp>
//---------------------------------------------------------------------------
class TF_PersonList : public TF_MDI
{
__published:	// IDE-managed Components
    TOraQuery *OraQuery1;
    TOraDataSource *OraDataSource1;
    TDBGridEh *DBGridEh1;
    void __fastcall DBGridEh1ApplyFilter(TObject *Sender);
    void __fastcall DBGridEh1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TF_PersonList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_PersonList *F_PersonList;
//---------------------------------------------------------------------------
#endif
