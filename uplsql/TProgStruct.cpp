//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TProgStruct.h"

//---------------------------------------------------------------------------
void TProgStruct::NewWord(AnsiString inWord) {
    inWord = inWord.UpperCase();
    switch (State) {
    case psNone:
        if (inWord == "CREATE" || inWord == "REPLACE") {
            State = psObjectTypeExpected;
        }
    break;
    case psObjectTypeExpected:
        if (inWord == "OR" || inWord == "CREATE" || inWord == "REPLACE" || inWord == "FORCE") {
            break;
        }
        State = psTypeObj;
        ObjType = inWord;
    break;
    case psTypeObj:
        if (inWord == "BODY") {
            ObjType = ObjType + " BODY";
            break;
        }
        ObjName = inWord;
        State = psNameObj;
    break;
    case psNameObj:
        if (inWord=="FORCE") break;
        if (inWord=="AS" || inWord=="IS") {
            State = psAsIs;
            break;
        }
        if (inWord=="UNDER") {
            State = psUnder;
            break;
        }
    break;
    case psAsIs:
        if (inWord=="OBJECT") {
            UnderObjName = "OBJECT";
            State=psZag;
            break;
        }
        if (inWord=="TABLE") {
            UnderObjName = "TABLE";
            State=psTable;
            break;
        }
    break;
    case psUnder:
        UnderObjName = inWord;
        State=psZag;
    break;
    case psTable:
        if (inWord == "OF") {
            State=psTableName;
        }
    break;
    case psTableName:
        TableTypeName = inWord;
        State=psZag;
    break;
    case psZag:
        if (inWord=="MEMBER") {
          State = psMember;
        }
    break;
    case psMember:
        if (inWord=="PROCEDURE" || inWord=="FUNCTION") {
          State = psProcFunc;
        }
    break;
    case psProcFunc:
        ProcFuncName = inWord;
        State = psProcFuncName;
    break;
    case psProcFuncName:
        if (inWord=="(") {
            State = psParams;
        }
        if (inWord==",") {
            State = psZag;
        }
        if (inWord=="(") {
            State = psParams;
        }
    break;
    }
}

//CREATE/REPLACE
///OR
//CREATE/REPLACE
///FORCE
//TYPE/PACKAGE/PROCEDURE/FUNCTION
///BODY
//&WORD
///FORCE
///AS OBJECT/AS TABLE OF/UNDER
//&WORD
//&CHAR(
//MEMBER/CONSTRUCTOR/&WORD



#pragma package(smart_init)
