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
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOraSession *OraSession1;
        TOraQuery *OraQuery1;
        TOraDataSource *OraDataSource1;
        TConnectDialog *ConnectDialog1;
        TListBox *ListBox1;
        TRichEdit *RichEdit1;
        void __fastcall RichEdit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall HighLight(TRichEdit *REdit, int pos);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
