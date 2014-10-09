#ifndef ALLHEADERS_H
#define ALLHEADERS_H

#define INC_VCLDB_HEADERS
#define INC_VCLEXT_HEADERS
#include <vcl.h>

// /* Все, что подключается предыдущими 3-мя строчками
// Core (minimal) Delphi RTL headers
#include <System.hpp>
//#include <Types.hpp>
#include <Windows.hpp>
#include <Messages.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>

// Core (minimal) VCL headers
#if defined(INC_VCL)
#include <Controls.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>

// VCL Database related headers
#if defined(INC_VCLDB_HEADERS)
#include <DBCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#endif  //  INC_VCLDB_HEADERS

// Full set of VCL headers
#if defined(INC_VCLEXT_HEADERS)
#include <Buttons.hpp>
#include <ChartFX.hpp>
#include <ComCtrls.hpp>
#include <DBCGrids.hpp>
#include <DBGrids.hpp>
#include <DBLookup.hpp>
#include <DdeMan.hpp>
#include <FileCtrl.hpp>
#include <GraphSvr.hpp>
#include <Grids.hpp>
#include <MPlayer.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <OleCtnrs.hpp>
#include <OleCtrls.hpp>
#include <Outline.hpp>
#include <Tabnotbk.hpp>
#include <Tabs.hpp>
#include <VCFImprs.hpp>
#include <VCFrmla1.hpp>
#include <VCSpell3.hpp>
#endif  // INC_VCLEXT_HEADERS

#endif  //  INC_VCL

// */

#include <sysset.h>
#include <IniFiles.hpp>
#include <AppEvnts.hpp>
//#include <ActnMan.hpp>
//#include <ActnCtrls.hpp>
//#include <BandActn.hpp>
//#include <CustomizeDlg.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ExtDlgs.hpp>
#include <ActnList.hpp>

//#include <IBDatabase.hpp>
//#include <IBCustomDataSet.hpp>
//#include <IBQuery.hpp>
//#include <IBTable.hpp>
//#include <IBSQL.hpp>
//#include <IBServices.hpp>

#include <math.h>
#include <assert.h>
#include <complex.h>
#include <values.h>

#include <map>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <memory>
#include <fstream>

//нестандартные компоненты RxLib и EhLib
//#include "CURREDIT.hpp"
//#include "RXSpin.hpp"
//#include "RxCalc.hpp"
//#include "RxCombos.hpp"
//#include "APPUTILS.hpp"
//#include "RXDBCtrl.hpp"
//#include "Placemnt.hpp"
//#include "DBGridEh.hpp"

//#include "TFraBase.h"
//#include "TFraBaseDB.h"
//#include "TFraOstBase.h"
//#include "TFraSaveNew.h"
//#include "TFraTools.h"
//#include "TFraTrebzBase.h"
//#include "TFraViewParams.h"
//#include "TFormBase.h"
//#include "TFormMDIBase.h"
#include "Ora.hpp"
#include "MemTableEh.hpp"
#include "DBAccess.hpp"
#include "GridsEh.hpp"
#include "MemDS.hpp"
//#include "DBGridEh.hpp"
#include <stdio.h>
#include <jpeg.hpp>

#endif