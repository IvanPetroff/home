//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include <Db.hpp>
#include "OdacVcl.hpp"
#include <ComCtrls.hpp>
#include "TFraLightRichEdit.h"
#include "TFraListObjects.h"
#include "TFraParse.h"
//---------------------------------------------------------------------------
// структура форматирования


class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOraSession *db;
        TOraQuery *OraQuery1;
        TOraDataSource *OraDataSource1;
        TConnectDialog *ConnectDialog1;
        TGroupBox *GroupBox1;
        TFraListObjects *FraListObjects1;
        TGroupBox *GroupBox2;
        TFraLightRichEdit *FraLightRichEdit1;
        void __fastcall FraListObjects1ListBox1Click(TObject *Sender);
private:	// User declarations
        void __fastcall LoadText(AnsiString objName);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
