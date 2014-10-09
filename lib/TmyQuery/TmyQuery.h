//---------------------------------------------------------------------------

#ifndef TmyQueryH
#define TmyQueryH

#include "Ora.hpp"
#include "TmyStringList.h"


    class TmySmartQuery : public TOraQuery
    {
    public:
          TmySmartQuery(int);
          void InitAllParams();
          void ExecSQL();
    };
    TmySmartQuery::TmySmartQuery(int) : TOraQuery(0){}
    void TmySmartQuery::InitAllParams() {
        for (int I = 0; I < this->Params->Count; I++) {
            this->Params->Items[I]->AsString = " ";
        }
    }
    void TmySmartQuery::ExecSQL() {
        TmyStringList SL;
        for (int I = 0; I < this->Params->Count; I++) {
            SL->Add(  "["+this->Params->Items[I]->Name + "] \"" + this->Params->Items[I]->AsString + "\"");
        }

        try {
            TOraQuery::ExecSQL();
        }
        catch (Exception &exception)
        {
            TmyStringList SL_SQL( SQL->Text);
            for (int I = 0; I < SL_SQL->Count; I++) {
                SL_SQL->Strings[I] = "[" + IntToStr(I+1) + "] " + SL_SQL->Strings[I];
            }
            AnsiString txt = exception.Message;
#if __DLL__!=1
            txt = txt + "\n" + SL_SQL->Text + "\n" + SL->Text;
#endif
            throw Exception( txt);
//            Application->ShowException( &exception);
        }
    }



    class TmyQuery {
    protected:
      TmySmartQuery* Q;
    public:
      TmyQuery();
      TmyQuery(TOraSession* inDB);
      TmyQuery(TOraSession* inDB, AnsiString inSQL);
      TmyQuery(TOraSession* inDB, AnsiString inSQL, int Par1);
      TmyQuery(TOraSession* inDB, AnsiString inSQL, int Par1, int Par2);
      TmyQuery(TOraSession* inDB, AnsiString inSQL, AnsiString Par1);
      TmyQuery(TOraSession* inDB, AnsiString inSQL, int Par1, AnsiString Par2);
      ~TmyQuery();
      TmySmartQuery* operator->();
    };

    inline TmyQuery::TmyQuery() : Q(new TmySmartQuery(0))
    {}

    inline TmyQuery::TmyQuery(TOraSession* inDB) : Q(new TmySmartQuery(0))
    { Q->Session = inDB;}

    inline TmyQuery::TmyQuery(TOraSession* inDB, AnsiString inSQL) : Q(new TmySmartQuery(0))
    { Q->Session = inDB; Q->SQL->Text = inSQL; Q->Prepare();}

    inline TmyQuery::TmyQuery(TOraSession* inDB, AnsiString inSQL, int Par1) : Q(new TmySmartQuery(0))
    { Q->Session = inDB; Q->SQL->Text = inSQL; Q->Prepare(); Q->Params->Items[0]->AsInteger = Par1; Q->ExecSQL();}

    inline TmyQuery::TmyQuery(TOraSession* inDB, AnsiString inSQL, int Par1, int Par2) : Q(new TmySmartQuery(0))
    { Q->Session = inDB; Q->SQL->Text = inSQL; Q->Prepare(); Q->Params->Items[0]->AsInteger = Par1; Q->Params->Items[1]->AsInteger = Par2; Q->ExecSQL();}

    inline TmyQuery::TmyQuery(TOraSession* inDB, AnsiString inSQL, AnsiString Par1) : Q(new TmySmartQuery(0))
    { Q->Session = inDB; Q->SQL->Text = inSQL; Q->Prepare(); Q->Params->Items[0]->AsString = Par1; Q->ExecSQL();}

    inline TmyQuery::TmyQuery(TOraSession* inDB, AnsiString inSQL, int Par1, AnsiString Par2) : Q(new TmySmartQuery(0))
    { Q->Session = inDB; Q->SQL->Text = inSQL; Q->Prepare(); Q->Params->Items[0]->AsInteger = Par1; Q->Params->Items[1]->AsString = Par2; Q->ExecSQL();}

    inline TmyQuery::~TmyQuery()
    {
      delete Q;
    }

    inline TmySmartQuery* TmyQuery::operator->()
    {
      return Q;
    }

//---------------------------------------------------------------------------
#endif
 