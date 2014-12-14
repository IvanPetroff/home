create or replace type m_T_SodDok force under T_SodDok
(
  -- Author  : Администратор
  -- Created : 11.12.2014 10:40:44
  -- Purpose : 
  constructor function m_T_SodDok(in_nz_zag number) return self as result,

  overriding member procedure Store
  
)
/
create or replace type body m_T_SodDok is
  
  -- Member procedures and functions
  constructor function m_T_SodDok(in_nz_zag number) return self as result is
  begin
    self.rec := T_SodDok_tab();
    last := 0;
    if in_nz_zag is null then
      return;
    end if;
    return;
  end;
  
  overriding member procedure Store is
  begin
    null;
  end;
  
end;
/
