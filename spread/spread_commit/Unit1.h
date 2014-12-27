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
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "TFraBase.h"
#include "TFraPrcFact.h"
#include "TFraSZ.h"
#include "TFraFactNew.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOraSession *db;
        TButton *Button2;
        TOraQuery *qxml;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TFraPrcFact *FraPrcFact1;
        TGroupBox *GroupBox2;
        TFraSZ *FraSZ1;
        TSplitter *Splitter1;
        TGroupBox *GroupBox3;
        TEdit *Edit1;
        TButton *Button1;
        TSpeedButton *SpeedButton1;
        TRadioButton *RB_Norma;
        TRadioButton *RB_Fact;
        TTimer *Timer1;
        TSpeedButton *SpeedButton2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall RB_NormaClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
    AnsiString sFact;
    AnsiString sNorma;
    AnsiString sFactMy;
    AnsiString CurrentState;
    AnsiString __fastcall Check100prc();
    void __fastcall ShowPrc();

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        AnsiString __fastcall GetXML();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
