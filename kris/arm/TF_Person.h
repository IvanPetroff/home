//---------------------------------------------------------------------------

#ifndef TF_PersonH
#define TF_PersonH
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
#include "TF_MDI.h"
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TF_Person : public TF_MDI
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TGroupBox *GroupBox1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TMemo *M_ADDR;
    TEdit *E_TEL;
    TEdit *E_EMAIL;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox2;
    TOraQuery *Q_Simptoms;
    TOraDataSource *DS_Simptoms;
    TDBGridEh *DBG_Simptoms;
    TTabSheet *TabSheet3;
    TGroupBox *GroupBox4;
    TOraQuery *Q_Other;
    TOraDataSource *DS_Other;
    TDBGridEh *DBG_Other;
    TEdit *E_D_BIRTH;
    TLabel *Label5;
    TLabel *Label8;
    TEdit *E_SEX;
    TOraQuery *Q_Person;
    TOraDataSource *DS_Person;
    TGroupBox *GroupBox5;
    TEdit *E_DAT;
    TLabel *Label7;
    TEdit *E_D_REG;
    TLabel *Label6;
    TEdit *E_FIO;
    TLabel *Label1;
    TOraQuery *Q_Quest_data;
    TGroupBox *GroupBox3;
    TSpeedButton *B_Edit;
    TSpeedButton *B_Save;
    TSpeedButton *B_Cancel;
    void __fastcall B_EditClick(TObject *Sender);
    void __fastcall B_CancelClick(TObject *Sender);
    void __fastcall B_SaveClick(TObject *Sender);
private:	// User declarations
    AnsiString BasicCaption;
    void __fastcall SetEditMode(bool flg);
    int PersonID;
    void __fastcall SavePersonInfo();


public:		// User declarations
    __fastcall TF_Person(TComponent* Owner);
    void __fastcall OpenPersonID(int in_ID);


};
//---------------------------------------------------------------------------
extern PACKAGE TF_Person *F_Person;
//---------------------------------------------------------------------------
#endif
