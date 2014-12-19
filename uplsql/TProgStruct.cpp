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
            State=psZag;
        }
    break;
    case psUnder:
        UnderObjName = inWord;
        State=psZag;
    break;
    }
}

#pragma package(smart_init)
