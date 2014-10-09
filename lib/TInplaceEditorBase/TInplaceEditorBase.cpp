//---------------------------------------------------------------------------

#include <vcl.h>
#include "AllHeaders.hpp"
#pragma hdrstop

#include "TInplaceEditorBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInplaceEditorBase *InplaceEditorBase;
//---------------------------------------------------------------------------
__fastcall TInplaceEditorBase::TInplaceEditorBase(TComponent* Owner)
        : TFrame(Owner)
{
      CreateFormForThisFrame();
}
//---------------------------------------------------------------------------


void __fastcall TInplaceEditorBase::CreateFormForThisFrame()
{
    myWindow = new TForm(Application);

    myWindow->BorderWidth=0;
    myWindow->BorderStyle=bsNone;


    myWindow->Name = "myWindow"+IntToStr((int)myWindow);
    myWindow->KeyPreview = true;
    myWindow->OnKeyUp           = _FormKeyUp;
    myWindow->OnKeyDown         = _FormKeyDown;
    myWindow->OnCloseQuery      = _FormCloseQuery;
    myWindow->OnClose           = _FormClose;
    myWindow->OnDeactivate      = _FormDeactivate;
    myWindow->OnShow            = _FormShow;

    myWindow->InsertControl( this);
    myWindow->RemoveControl( this);
    myWindow->InsertControl( this);
}


int __fastcall TInplaceEditorBase::ShowModal(TRect Rect, bool SelectAll)
{
    _SelectAll = SelectAll;
    ModalResult = mrNone;
    this->LoadVal();
    isChanging = true;
    this->Show(Rect);
    while (ModalResult==mrNone) {
        Application->ProcessMessages();
        Sleep(1);
    }
    myWindow->Hide();

    if (ModalResult==mrOk) {
        SaveVal();
        if (!isChanging) ModalResult = mrCancel;
    }

    return ModalResult;
}



void __fastcall TInplaceEditorBase::KillForm()
{
    if ( myWindow==0) return;

    myWindow->OnKeyUp = 0;
    myWindow->OnKeyDown = 0;
    myWindow->OnCloseQuery = 0;
    myWindow->OnClose = 0;
    myWindow->OnDeactivate = 0;
    myWindow->RemoveControl( this);
    myWindow = 0;

    delete myWindow;
}



// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------
void __fastcall TInplaceEditorBase::_FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
    KillForm();
}

// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------
void __fastcall TInplaceEditorBase::_FormClose(TObject *Sender, TCloseAction &Action)
{
}

// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------
void __fastcall TInplaceEditorBase::_DBG_FindKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
}

// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------
void __fastcall TInplaceEditorBase::_FormDeactivate(TObject *Sender)
{
    if (ModalResult==mrNone) ModalResult = mrCancel;
//    myWindow->Hide();
    return;
}

// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------
void __fastcall TInplaceEditorBase::_FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key==VK_TAB) { // “‡· ÔÓ˜ÂÏÛ-ÚÓ ÌÂ ÎÓ‚ËÚÒˇ ‚ OnKeyDown. œÓ˝ÚÓÏÛ ÎÓ‚ËÏ Â„Ó Á‰ÂÒ¸.

//        myWindow->Hide();
    }
}


void __fastcall TInplaceEditorBase::_FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key==VK_ESCAPE) {
        if (ModalResult==mrNone) ModalResult = mrCancel;
    }
    if ((Key==VK_RETURN)&&(ReadOnly==true)) {
          if (ModalResult==mrNone) ModalResult = mrOk;
    }
}

// Œ¡–¿¡Œ“◊» » —Œ¡€“»È ------------------------------------------------------
void __fastcall TInplaceEditorBase::_DBG_FindDblClick(TObject *Sender)
{
}



//---------------------------------------------------------------------------
void __fastcall TInplaceEditorBase::_AddControlIntoPerimeter(TControl* inControl, THorizont &Horizont)
{
    int maxTag = 10;
    TWinControl* WinControl = dynamic_cast<TWinControl *>(inControl);
    while ((inControl->Tag<=0)&&(WinControl != NULL)) {
        if (WinControl->ControlCount==0) break;
        for (int myTag = 0; myTag<maxTag; myTag++) {
            for (int I = 0; I < WinControl->ControlCount; I++) {
                if (( abs( WinControl->Controls[I]->Tag)==myTag)) {
                    _AddControlIntoPerimeter(WinControl->Controls[I], Horizont);
                }
            }
        }
        return;
    }

    if (inControl->Tag<=0) return;

    TPoint P = inControl->ClientToScreen( TPoint(0, 0));
    Horizont.AddRect(TRect(P.x,P.y,P.x +inControl->Width,P.y +inControl->Height));
}



void __fastcall TInplaceEditorBase::_CreateWindowPerimeter(TForm *inForm)
{
    THorizont Horizont;
    _AddControlIntoPerimeter(this, Horizont);

    TPoint P = this->ClientToScreen( TPoint(0, 0));

    SetWindowRgn(inForm->Handle, Horizont.GetHRGN( P.x, P.y), TRUE);
}


//---------------------------------------------------------------------------
void __fastcall TInplaceEditorBase::_FormShow(TObject *Sender)
{
    _CreateWindowPerimeter((TForm*)Sender);
}


