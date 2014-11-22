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
#include "TEditorGrid.h"
#include "TEditAvto.h"
#include "TEditSimple.h"
#include "TFraBase.h"
#include "TFraGasPoint.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TOraSession *db;
        TPageControl *PageControl1;
        TTabSheet *TabSheet3;
        TFraGasPoint *FraGasPoint1;
        TTabSheet *TabSheet1;
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
