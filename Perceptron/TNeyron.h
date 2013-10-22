//---------------------------------------------------------------------------

#ifndef TNeyronH
#define TNeyronH
#include <vector.h>
//---------------------------------------------------------------------------
class TNeyron {
private:
    vector<double> w; // массив весов
    vector<TNeyron*> s;
    vector<TNeyron*> bs;
    void __fastcall InitWeights();
    void __fastcall InitSinaps(vector<TNeyron*> &Layer);
    double __fastcall Activator(double in);
public:
    double out;
    __fastcall TNeyron(int cnt_inputs, vector<TNeyron*> &Layer);
    void __fastcall Transfer();
    void __fastcall CalcErr();
    void __fastcall Learn();
    double Err;
};
#endif
