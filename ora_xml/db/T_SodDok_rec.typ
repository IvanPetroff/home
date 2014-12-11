create or replace type T_SodDok_rec force as object
(
  -- Author  : Администратор
  -- Created : 09.12.2014 8:35:46
  -- Purpose : 
  
  -- Attributes
  nz number,
  nz_zag number,
  kod_mat varchar2(24),
  dop_kod varchar2(18),
  kol_treb number,
  
  constructor function T_SodDok_rec(in_nz number) return self as result
  
  -- Member functions and procedures
)
/
create or replace type body T_SodDok_rec is
  
  -- Member procedures and functions
  constructor function T_SodDok_rec(in_nz number) return self as result is
  begin
    if in_nz is null then
      nz := null;
      nz_zag := null;
      kod_mat := null;
      dop_kod := null;
      kol_treb := null;
      return;
    end if;

    select nz, nz_zag, kod_mat, dop_kod, kol_treb
      into nz, nz_zag, kod_mat, dop_kod, kol_treb
      from asu_sod_dok where nz = in_nz;
  end;
  
end;
/
