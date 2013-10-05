//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "TmyRecords.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TPageControl *PageControl1;
        TTabSheet *TS_Game;
        TTabSheet *TS_Log;
        TGroupBox *GB_Info;
        TLabel *L_Count;
        TLabel *L_Add;
        TGroupBox *GroupBox1;
        TSpeedButton *SB_Start;
        TSpeedButton *SB_Stop;
        TPaintBox *PB;
        TGroupBox *GB_Answer;
        TEdit *E_Answer;
        TComboBox *CB_Name;
        TLabel *Label1;
        TStringGrid *StringGrid1;
        TStatusBar *msg;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall PBPaint(TObject *Sender);
        void __fastcall E_AnswerKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SB_StartClick(TObject *Sender);
        void __fastcall PageControl1Changing(TObject *Sender,
          bool &AllowChange);
        void __fastcall SB_StopClick(TObject *Sender);
private:	// User declarations
        int Step;
        int X1;
        int X2;
        AnsiString _Text;
        void __fastcall myNew();
        void __fastcall myCheckAnswer(AnsiString Answer);
        void __fastcall myCrash();
        void __fastcall mySetAdd();

        int _myCount;
        int _myAdd;
        void __fastcall set_myCount(int val);
        void __fastcall set_myAdd(int val);

        __property int myCount = {read=_myCount,write=set_myCount};
        __property int myAdd = {read=_myAdd,write=set_myAdd};

        TmyRecords* myRecords;
        int __fastcall getMinY();
        int __fastcall getMaxY();
        void __fastcall setTXT(AnsiString val);
        __property AnsiString Text = {write=setTXT};

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        __fastcall ~TForm1();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
