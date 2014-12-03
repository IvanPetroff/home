create or replace type DokBase force as object
(
  -- Author  : Администратор
  -- Created : 03.12.2014 9:03:06
  -- Purpose : 
  x XMLtype,
  member procedure Init,
  member procedure OpenDok(in_nz number)
)
not final;
/
create or replace type body DokBase is
  
  -- Member procedures and functions
  member procedure Init is
  begin
    x := XMLtype('<doc></doc>');
    null;
  end;
  
  member procedure OpenDok(in_nz number) is
  r asu_zag_dok%rowtype;
--  xx sys.anydata;
  begin
--    select * into xx from asu_zag_dok;
    select xmltype(cursor(select * from asu_zag_dok where rownum<2)) into x from dual;
    for Cur in (select * from asu_zag_dok where nz=in_nz) loop
      
      null;
    end loop;
    for Cur in (select * from asu_sod_dok where nz_zag=in_nz) loop
      null;
    end loop;
    null;
  end;
  
end;
/
