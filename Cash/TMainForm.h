//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "MemTableEh.hpp"
#include "TEditorBase.h"
#include "TEditorGrid.h"
#include <Db.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMemTableEh *MT;
        TDataSource *DataSource1;
        TDBGridEh *DBG;
    TIntegerField *MTid;
    TDateField *MTdat;
    TStringField *MTnaim;
    TStringField *MTcat;
    TFloatField *MTkol;
    TFloatField *MTcena;
    TFloatField *MTstoim;
        TEditorGrid *EditorGrid1;
        void __fastcall MTAfterPost(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
