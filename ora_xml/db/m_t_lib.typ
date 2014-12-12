create or replace type m_t_lib force under t_lib
(
  -- Author  : Администратор
  -- Created : 12.12.2014 10:59:09
  -- Purpose : 
  
  -- Attributes
  
  -- Member functions and procedures
  constructor function m_t_lib return self as result,
  overriding member procedure chk_Kod_mat_exist(in_kod_mat varchar2, in_type varchar2),
  overriding member procedure chk_nklad_exist(in_nklad varchar2, in_type varchar2),
  overriding member procedure chk_op_exist(in_op number, in_wid_dok number)
  
)
/
create or replace type body m_t_lib is
  
  -- Member procedures and functions
  constructor function m_t_lib return self as result is
  begin
    return;
  end;
  
  overriding member procedure chk_Kod_mat_exist(in_kod_mat varchar2, in_type varchar2) is
  begin
    debug_pkg.put_line(in_kod_mat || ', ' || in_type);
    null;
  end;

  overriding member procedure chk_nklad_exist(in_nklad varchar2, in_type varchar2) is
  begin
    debug_pkg.put_line(in_nklad || ', ' || in_type);
    null;
  end;
  
  overriding member procedure chk_op_exist(in_op number, in_wid_dok number) is
  begin
    debug_pkg.put_line(in_op || ', ' || in_wid_dok);
    null;
  end;

end;
/
