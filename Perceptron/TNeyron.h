//---------------------------------------------------------------------------

#ifndef TNeyronH
#define TNeyronH
#include <vector.h>
#include <inifiles.hpp>

//---------------------------------------------------------------------------
class TNeyron {
private:
    vector<double> w; // массив весов
    vector<int> sn;
    vector<TNeyron*> s;
    vector<TNeyron*> bs;
    void __fastcall InitWeights();
    void __fastcall InitSinaps(vector<TNeyron*> &Layer);
    double __fastcall Activator(double in);
    void __fastcall LoadSynapses(TIniFile* F, AnsiString SectionName, vector<TNeyron*> &Layer);
    void __fastcall LoadWeights(TIniFile* F, AnsiString SectionName);

public:
    double out;
    __fastcall TNeyron(int cnt_inputs, vector<TNeyron*> &Layer);
    __fastcall TNeyron(TIniFile* F, AnsiString SectionName, vector<TNeyron*> &Layer);
    void __fastcall Transfer();
    void __fastcall CalcErr();
    void __fastcall Learn();
    void __fastcall Save(TIniFile* F, AnsiString SectionName);
    double Err;
};
#endif
