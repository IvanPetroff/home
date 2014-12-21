create or replace type class_spis_dok as object
(
  -- Author  : Администратор
  -- Created : 21.12.2014 19:27:52
  -- Purpose : 
  rec rec_foo,
  tab tab_foo,
  
  -- Attributes
  constructor function class_spis_dok(in_id number) return self as result,
  member procedure init(in_id number)
  
  
  -- Member functions and procedures
)
not final;
/
create or replace type body class_spis_dok is
  
  -- Member procedures and functions
  constructor function class_spis_dok(in_id number) return self as result is
  begin
    init(in_id);
    null;
  end;
  
  member procedure init(in_id number) is
  begin
    select rec_foo( id, dok_id, kol, kol_treb, d_ceh, u_ceh, d_buh, u_buh, ost_id, type) 
      bulk collect into tab 
      from spis_dok 
      where dok_id=in_id;    
    null;
  end;
  
end;
/
