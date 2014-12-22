create or replace force type class_spis_spread# force under class_spis_spread
(
  -- Author  : Администратор
  -- Created : 22.12.2014 21:11:45
  -- Purpose : Класс-заглушка. перегружает методы обращения к реальной базе данных
  
  test_get_flg_spreadable# varchar2(1),
   
  constructor function class_spis_spread#(in_id number) return self as result,
  overriding member procedure init(in_dok_id number),
  
  overriding member function get_flg_spreadable#(in_dok_id number) return varchar2,
  overriding member procedure load_dok#(in_dok_id number),
  overriding member procedure more_attr_set_num#(in_key number, in_val number),
  overriding member procedure store_in_minus_recs#,
  overriding member procedure store_out_spread_recs#

)
/
create or replace type body class_spis_spread# is
  
  -- Member procedures and functions
  constructor function class_spis_spread#(in_id number) return self as result is
  begin
    init(in_id);
    return;
  end;
  
  overriding member procedure init(in_dok_id number) is
  begin
    (self as class_spis_spread).init(in_dok_id);
  end;
  

  overriding member function get_flg_spreadable#(in_dok_id number) return varchar2 is
  begin
    return test_get_flg_spreadable#;
  end;


  overriding member procedure load_dok#(in_dok_id number) is
  begin
    dbms_output.put_line('load_dok#('||in_dok_id||')');
    null;
  end;



  overriding member procedure more_attr_set_num#(in_key number, in_val number) is
  begin
    null;
  end;
  
  
  overriding member procedure store_in_minus_recs# is
  begin
    null;
  end;


  overriding member procedure store_out_spread_recs# is
  begin
    null;
  end;
  
  
end;
/
