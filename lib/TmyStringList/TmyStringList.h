//---------------------------------------------------------------------------


#ifndef TmyStringListH
#define TmyStringListH
  class TmodStringList : public TStringList {
  public:
      TStringList* This() {return this;}
  };


class TmyStringList {
protected:
  TStringList* SL;
public:
  TmyStringList() : SL(new TStringList){};
  TmyStringList( AnsiString S);
  TmyStringList( AnsiString S, AnsiString Sep);
  ~TmyStringList();
  TmodStringList* operator->();
};


inline TmyStringList::TmyStringList( AnsiString S) : SL(new TStringList)
{
    SL->Text = S;
}


inline TmyStringList::TmyStringList( AnsiString S, AnsiString Sep) : SL(new TStringList)
{
    while (S.Pos( Sep)>0) {
       S.Insert( "\n", S.Pos( Sep));
       S.Delete( S.Pos( Sep), Sep.Length());
    }
    SL->Text = S;
}

inline TmyStringList::~TmyStringList()
{
  delete SL;
  SL = 0;
}

inline TmodStringList* TmyStringList::operator->()
{
  return (TmodStringList*)SL;
}

//---------------------------------------------------------------------------
#endif
