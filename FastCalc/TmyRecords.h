//---------------------------------------------------------------------------

#ifndef TmyRecordsH
#define TmyRecordsH
#include <Grids.hpp>

class TmyRecords {
private:
    TStringGrid* SG;
    TComboBox*   CB;
    int  __fastcall getVal(int index);
    void        __fastcall setVal(int index, int val);
    AnsiString  __fastcall getName(int index);
    void        __fastcall setName(int index, AnsiString val);
public:
    TmyRecords(TStringGrid* SG, TComboBox* CB);
    ~TmyRecords();
    void __fastcall Load();
    void __fastcall Save();
    __property int Val[int] = {read=getVal,write=setVal};
    __property AnsiString Name[int] = {read=getName,write=setName};
};
//---------------------------------------------------------------------------
#endif
