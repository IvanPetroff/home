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
  overriding member procedure chk_op_exist(in_op number, in_wid_dok number),
  overriding member procedure chk_skl_kart_exists( in_ost_id number, in_type varchar2, in_m_kod varchar2, in_skl varchar2),
  overriding member function get_env_var(in_usr varchar2, in_var_name varchar2) return varchar2
  
  
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
  
  overriding member procedure chk_skl_kart_exists( in_ost_id number, in_type varchar2, in_m_kod varchar2, in_skl varchar2) is
  begin
    debug_pkg.put_line(in_ost_id || ', ' || in_type || ', ' || in_m_kod || ', ' || in_skl);
    null;
  end;
  
  overriding member function get_env_var(in_usr varchar2, in_var_name varchar2) return varchar2 is
  begin
    return null;
  end;
  
  

end;
/
