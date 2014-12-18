//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <memory>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
//    ThisPort->PhoneEvents = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
    if (TimerTimeout->Enabled) return;
    Button2->Enabled = false;
    Button3->Enabled = false;
    std::auto_ptr<TComPort> ThisPort(new TComPort(&Buf));
    ThisPort->ComOpen("COM3", "9600", "");

    Buf = "";
    ThisPort->SendCommand("ў");
    TimerTimeout->Enabled = true;
    while ( TimerTimeout->Enabled && Buf.Length()==0)
    {
//        Sleep(100);
        Application->ProcessMessages();
    }

    if (Buf.Length()==0) {
        ShowMessage("Нет связи");
    }
    else {
        Memo1->Lines->Add( Buf);
    }
    ThisPort->ComClose();
    Button2->Enabled = true;
    Button3->Enabled = true;
    TimerTimeout->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
    if (TimerTimeout->Enabled) return;
    Button2->Enabled = false;
    Button3->Enabled = false;

    std::auto_ptr<TComPort> ThisPort(new TComPort(&Buf));
    ThisPort->ComOpen("COM3", "9600", "");
    Buf = "";
    ThisPort->SendCommand("Ђ");
    TimerTimeout->Enabled = true;
    while ( TimerTimeout->Enabled && Buf.Length()==0)
    {
//        Sleep(100);
        Application->ProcessMessages();
    }

    if (Buf.Length()==0) {
        ShowMessage("Нет связи");
    }
    else {
        Memo1->Lines->Add( Buf);
    }
    ThisPort->ComClose();

    Button2->Enabled = true;
    Button3->Enabled = true;
    TimerTimeout->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TimerTimeoutTimer(TObject *Sender)
{
    TimerTimeout->Enabled = false;
}
//---------------------------------------------------------------------------
