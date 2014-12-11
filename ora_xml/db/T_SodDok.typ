create or replace type T_SodDok force as object
(
  -- Author  : Администратор
  -- Created : 09.12.2014 8:35:46
  -- Purpose : 
  
  -- Attributes
  rec T_SodDok_tab,
  last number,
  
  -- Member functions and procedures
  constructor function T_SodDok(in_nz_zag number) return self as result,
  member procedure newline,
  member procedure clean,
  member procedure Store
  

)
not final;
/
create or replace type body T_SodDok is
  
  -- Member procedures and functions
  constructor function T_SodDok(in_nz_zag number) return self as result is
  begin
    self.rec := T_SodDok_tab();
    if in_nz_zag is null then
      return;
    end if;
     
    for Cur in (select * from asu_sod_dok where nz_zag=in_nz_zag) loop
      self.newline();
      self.rec( last).nz := Cur.nz;
      self.rec( last).nz_zag := Cur.nz_zag;
      self.rec( last).kod_mat := Cur.kod_mat;
      self.rec( last).dop_kod := Cur.dop_kod;
      self.rec( last).kol_treb := Cur.kol_treb;
    end loop;
  end;

  member procedure newline is
  begin
      self.rec.extend(1);
      last := self.rec.last;
      self.rec( last) := T_SodDok_rec(null);
  end;

  member procedure clean is
  begin
    rec := T_SodDok_tab();
    null;
  end;

  member procedure Store is
  begin
    null;
  end;
  
end;
/
