create or replace type T_SodDok_rec as object
(
  -- Author  : Администратор
  -- Created : 09.12.2014 8:35:46
  -- Purpose : 
  
  -- Attributes
  nz number,
  nz_zag number,
  kod_mat varchar2(24),
  dop_kod varchar2(18),
  
  constructor function T_SodDok_rec(in_nz number) return self as result
  
  -- Member functions and procedures
)
/
create or replace type body T_SodDok_rec is
  
  -- Member procedures and functions
  constructor function T_SodDok_rec(in_nz number) return self as result is
  begin
    select nz,nz_zag,kod_mat,dop_kod
    into nz,nz_zag,kod_mat,dop_kod
    from asu_sod_dok where nz = in_nz;
  end;
  
end;
/
