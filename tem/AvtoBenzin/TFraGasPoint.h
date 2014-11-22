//---------------------------------------------------------------------------

#ifndef TFraGasPointH
#define TFraGasPointH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBAccess.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include "TEditorBase.h"
#include "TEditorGrid.h"
#include "TEditSimple.h"
#include "TFraBase.h"
#include <Db.hpp>
#include <ExtCtrls.hpp>
#include "MemTableEh.hpp"
#include "TFraTankGasolineList.h"
//---------------------------------------------------------------------------
class TFraGasPoint : public TFraBase
{
__published:	// IDE-managed Components
        TPanel *Panel4;
        TLabel *Label8;
        TComboBox *CB_Dense;
        TGroupBox *GroupBox3;
        TStaticText *Edit1;
        TDBGridEh *DBG_Sod;
        TEditorGrid *EditAvto;
        TEditSimple *EditSimple1;
        TOraQuery *Q_Sod;
        TOraDataSource *DS_Sod;
        TOraQuery *Q_listBenzin;
        TEdit *E_SklFrom;
        TOraQuery *Q_SloAvto;
        TMemTableEh *MT;
        TIntegerField *MemTableEh1nz;
        TStringField *MemTableEh1avto;
        TFloatField *MemTableEh1kol_kg;
        TFloatField *MemTableEh1kol_litre;
        TFloatField *MemTableEh1k_density;
        TStringField *MemTableEh1kod_mat;
        TDataSource *DataSource1;
        TFraTankGasolineList *FraTankGasolineList1;
        TPanel *Panel1;
        TStringField *MTmestoh;
        TDateTimeField *MTdat;
        void __fastcall MTAfterInsert(TDataSet *DataSet);
        void __fastcall MTBeforeInsert(TDataSet *DataSet);
        void __fastcall MTBeforePost(TDataSet *DataSet);
private:	// User declarations
    TOraSession* db;
    void        __fastcall _CreateMemoryDataset();
    void        __fastcall _CreateInplaceEditors();
    void        __fastcall _LoadAvtoIntoHistoryList();

public:		// User declarations
                __fastcall TFraGasPoint (TComponent* Owner);
    void        __fastcall Init         (TOraSession* in_db);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraGasPoint *FraGasPoint;
//---------------------------------------------------------------------------
#endif
