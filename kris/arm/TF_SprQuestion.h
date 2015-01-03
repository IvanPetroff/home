//---------------------------------------------------------------------------

#ifndef TF_SprQuestionH
#define TF_SprQuestionH
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
class TF_SprQuestion : public TF_MDI
{
__published:	// IDE-managed Components
    TDBGridEh *DBGridEh1;
    TOraDataSource *OraDataSource1;
    TOraQuery *OraQuery1;
private:	// User declarations
public:		// User declarations
    __fastcall TF_SprQuestion(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_SprQuestion *F_SprQuestion;
//---------------------------------------------------------------------------
#endif
