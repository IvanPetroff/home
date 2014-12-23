create or replace type class_spreadlist as object
(
  -- Author  : Администратор
  -- Created : 23.12.2014 12:36:05
  -- Purpose : 
  id number,
  
  -- Attributes
  constructor function class_spreadlist return self as result,
  member procedure add_all
  
)
/
create or replace type body class_spreadlist is
  
  -- Member procedures and functions
  constructor function class_spreadlist return self as result is
  begin
    return;
  end;
  
  member procedure add_all is
  begin
    for Cur in (select s.id from asu_spis_dok s, asu_more_attr m where s.id=m.key and m.cat='SPIS_DOK' and name_attr='SPREAD') loop
      
      null;
    end loop;
    null;
  end;
  
end;
/
