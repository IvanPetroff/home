//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    myRecords = new TmyRecords(StringGrid1, CB_Name);
    randomize();
    Step = 5;
    PB->Canvas->Font->Name = PB->Font->Name;
    PB->Canvas->Font->Size = PB->Font->Size;
    myCount = 0;
    myAdd = 0;
    this->DoubleBuffered = true;
}
//---------------------------------------------------------------------------

__fastcall TForm1::~TForm1()
{
    delete myRecords;
}


void __fastcall TForm1::myCrash()
{
    Timer1->Enabled = false;
    Beep();
    ShowMessage("Проиграл!");
    if (myCount > myRecords->Val[CB_Name->ItemIndex]) {
        ShowMessage("У вас новый рекорд "+ String(myCount)+"!");
        myRecords->Val[CB_Name->ItemIndex] = myCount;
    }
    myCount = 0;
    myNew();
}


void __fastcall TForm1::mySetAdd()
{
    double X_Top = GB_Info->Top+GB_Info->Height;
    double X_Bottom = GB_Answer->Top-PB->Height;
    double K = 10.0/(X_Bottom-X_Top);
    myAdd = 10-(PB->Top-X_Top)*K;
}



void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    if ((!E_Answer->Focused())&&(E_Answer->CanFocus())) E_Answer->SetFocus(); 
    PB->Top += Step;
    if ((PB->Top+PB->Height)>GB_Answer->Top) myCrash();
    mySetAdd();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::myNew()
{
    X1 = random(8)+2;
    X2 = random(8)+2;
    E_Answer->Text = "";
    Text = String(X1) +"x"+ String(X2) + "=?";
    PB->Top = GB_Info->Top+GB_Info->Height;
    PB->Left = random(this->ClientWidth - PB->Width);
    myAdd = 10;
    msg->SimpleText = "Ваш рекорд " + String(myRecords->Val[CB_Name->ItemIndex]);
    Timer1->Enabled = true;
}


void __fastcall TForm1::PBPaint(TObject *Sender)
{
    PB->Canvas->Font->Color = clBlue;
    PB->Canvas->TextOut(0,0, String(X1) +"x"+ String(X2) + "=?");
}


void __fastcall TForm1::myCheckAnswer(AnsiString Answer)
{
    int Ans = 0;
    try {
        Ans = StrToInt(Answer.Trim());
    }
    catch(Exception &e) {

    }

    if ((X1*X2)==Ans) {
        myCount = myCount + myAdd;
        myNew();
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::E_AnswerKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_RETURN) {
        myCheckAnswer(E_Answer->Text);
        E_Answer->Text = "";
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::set_myCount(int val)
{
    _myCount = val;
    L_Count->Caption = String(_myCount);
}


void __fastcall TForm1::set_myAdd(int val)
{
    _myAdd = val;
    L_Add->Caption = "+"+String(_myAdd);
}

void __fastcall TForm1::SB_StartClick(TObject *Sender)
{
    if (CB_Name->ItemIndex<0) {
        ShowMessage("Укажите имя!");
        return;
    }
    myCount = 0;
    myNew();
    SB_Stop->Enabled = true;
    SB_Start->Enabled = false;
}
//---------------------------------------------------------------------------

int __fastcall TForm1::getMinY()
{
    return GB_Info->Top +GB_Info->Height;
}

int __fastcall TForm1::getMaxY()
{
    return GB_Answer->Top -PB->Height;
}



void __fastcall TForm1::setTXT(AnsiString val)
{
    this->_Text = val;
    PB->Width = PB->Canvas->TextWidth(val);
    PB->Height = PB->Canvas->TextHeight(val);
}

void __fastcall TForm1::PageControl1Changing(TObject *Sender,
      bool &AllowChange)
{
    if (Timer1->Enabled) AllowChange=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_StopClick(TObject *Sender)
{
    SB_Stop->Enabled = false;
    SB_Start->Enabled = true;
    Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

