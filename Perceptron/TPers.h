//---------------------------------------------------------------------------

#ifndef TPersH
#define TPersH
#include <vector.h>
//---------------------------------------------------------------------------
class TPers {
private:

    vector<double> _in;
    vector<vector<double> > _lay;
    vector< vector< vector<pair<int,double> > > > _links;
    double      __fastcall _get_in(int index);
    void        __fastcall _set_in(int index, double val);
    void __fastcall Init();
public:
    int cnt_in;
    int cnt_links;
    int cnt_lay;
    double out;
    int step;
    __fastcall TPers(int cnt_in, int cnt_lay, int cnt_links);
    void __fastcall Run();
    void __fastcall Evol();
    void __fastcall Fine(double targ);
    void __fastcall DrawLayer(TCanvas* Canvas, TRect Rect, int lay_number);
    void __fastcall DrawLinks(TCanvas* Canvas, TRect Rect, int lay_number);


    __property double in[int]  = {read=_get_in, write=_set_in};

};

#endif
 