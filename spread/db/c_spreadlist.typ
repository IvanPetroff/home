create or replace force type c_spreadlist force as object
(
  -- Author  : Администратор
  -- Created : 29.12.2014 19:52:00
  -- Purpose : 
  
  -- Attributes
  tmp number,
  static function create_obj(in_id number := null) return c_spreadlist,
  
  -- Member functions and procedures
  member function CreateList(self in out c_spreadlist, in_d_beg date, in_d_end date) return number,
  member function getSpreadList(x xmltype := null) return xmltype,
  member function load_prc_trud#(in_type varchar2) return xmltype,
  member function getListOfList return xmltype
  
)
not final;
/
create or replace type body c_spreadlist is
  
  static function create_obj(in_id number := null) return c_spreadlist is
  begin
    return treat(class_spreadlist(in_id) as c_spreadlist);
    null;
  end;

  -- Member procedures and functions
  member function CreateList(self in out c_spreadlist, in_d_beg date, in_d_end date) return number is
  begin
    null;
  end;

  member function getSpreadList(x xmltype := null) return xmltype is
  begin
    null;
  end;
  
  member function load_prc_trud#(in_type varchar2) return xmltype is
  begin
    null;
  end;
  
  member function getListOfList return xmltype is
  begin
    null;
  end;
  
  

end;
/
