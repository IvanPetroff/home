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
#include <ComCtrls.hpp>
#include <Db.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ExtCtrls.hpp>
#include "DataDriverEh.hpp"
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include "TmyInplaceEditor.h"
#include "TmyQuery.h"
#include "TEditorBase.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TOraSession *db;
    TOraQuery *OraQuery1;
    TOraDataSource *OraDataSource1;
    TGroupBox *GroupBox1;
    TOraQuery *Q_KodOper;
    TLabel *Label1;
    TDateTimePicker *DateTimePicker1;
    TLabel *Label2;
    TComboBox *CB_KodOper;
    TOraQuery *OraQuery2;
    TEdit *E_SklFrom;
    TLabel *Label3;
    TEdit *Edit2;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *Edit3;
    TLabel *Label6;
    TComboBox *ComboBox1;
    TGroupBox *GroupBox2;
    TLabel *Label7;
    TComboBox *CB_Benzin;
    TOraQuery *Q_Benzin;
    TComboBox *CB_Dense;
    TLabel *Label8;
    TOraQuery *Q_Sod;
    TOraDataSource *DS_Sod;
    TOraQuery *Q_SloAvto;
    TOraDataSource *DS_SloAvto;
    TPanel *Panel1;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox4;
    TSplitter *Splitter1;
    TPanel *P_SloAvto;
    TPanel *Panel2;
    TSpeedButton *SpeedButton1;
    TDBGridEh *DBG_SloAvto;
    TPanel *Panel3;
    TTimer *Timer1;
    TStaticText *Edit1;
    TEditorBase *EditorBase1;
    TDBGridEh *DBG_Sod;
    void __fastcall DBG_SloAvtoSortMarkingChanged(TObject *Sender);
    void __fastcall DBG_SloAvtoApplyFilter(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall DBG_SloAvtoDblClick(TObject *Sender);
    void __fastcall DBG_SloAvtoDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumnEh *Column,
          TGridDrawState State);
    void __fastcall DBG_SloAvtoMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
private:	// User declarations
    void __fastcall BeginEdit();
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
