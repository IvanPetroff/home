create or replace type T_SodDok force as object
(
  -- Author  : Администратор
  -- Created : 09.12.2014 8:35:46
  -- Purpose : 
  
  -- Attributes
  rec T_SodDok_tab,

  
  constructor function T_SodDok(in_nz_zag number) return self as result
  
  -- Member functions and procedures
)
/
create or replace type body T_SodDok is
  
  -- Member procedures and functions
  constructor function T_SodDok(in_nz_zag number) return self as result is
  my_last number;
  begin
    for Cur in (select * from asu_sod_dok where nz_zag=in_nz_zag) loop
      self.rec.extend(1);
      my_last := self.rec.last;
      self.rec( my_last).nz := Cur.nz;
      self.rec( my_last).nz_zag := Cur.nz_zag;
      self.rec( my_last).kod_mat := Cur.kod_mat;
      self.rec( my_last).dop_kod := Cur.dop_kod;
    null;
    end loop;
    
--    for Cur in (select * from asu_sod_dok where nz_zag=in_nz) loop
    --  self.rec
    null;
--    end loop;
    
/*    select nz,nz_zag,kod_mat,dop_kod
    into nz,nz_zag,kod_mat,dop_kod
    from asu_sod_dok where nz_zag = in_nz_zag;
*/  end;
  
end;
/
