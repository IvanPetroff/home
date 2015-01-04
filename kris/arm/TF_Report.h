//---------------------------------------------------------------------------

#ifndef TF_ReportH
#define TF_ReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include "TF_MDI.h"
#include <Db.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <QRPrntr.hpp>
//---------------------------------------------------------------------------
class TF_Report : public TF_MDI
{
__published:	// IDE-managed Components
    TOraQuery *OraQuery1;
    TOraDataSource *OraDataSource1;
    TDBGridEh *DBGridEh1;
    TButton *Button1;
    TPanel *Panel1;
    TQuickRep *QuickRep1;
    TQRBand *QRBand1;
    TQRDBText *QRDBText1;
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TF_Report(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Report *F_Report;
//---------------------------------------------------------------------------
#endif
