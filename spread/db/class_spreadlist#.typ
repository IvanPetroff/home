create or replace type class_spreadlist# under class_spreadlist
(
  -- Author  : Администратор
  -- Created : 24.12.2014 13:19:46
  -- Purpose : 
  constructor function class_spreadlist# return self as result,

  overriding member procedure more_attr_set_num#(in_name_attr varchar2, in_key number, in_val number),
  overriding member procedure more_attr_set_txt#(in_name_attr varchar2, in_key number, in_val varchar2),
  overriding member procedure more_attr_set_dat#(in_name_attr varchar2, in_key number, in_val date),
  overriding member function get_ListID# return number,
  overriding member procedure more_attr_set_prc_trud#( in_uch varchar2, in_ListID number, in_Unizak number, in_prc number)
  
  -- Attributes
)
/
create or replace type body class_spreadlist# is
  
  -- Member procedures and functions
  constructor function class_spreadlist# return self as result is
  begin
    null;
  end;
  

/*****************************************************************************************/
  overriding member procedure more_attr_set_num#(in_name_attr varchar2, in_key number, in_val number) is
  begin
    dbms_output.put_line('more_attr_set_num#('||in_name_attr||','||in_key||','||in_val||')');
  end;
  

/*****************************************************************************************/
  overriding member procedure more_attr_set_txt#(in_name_attr varchar2, in_key number, in_val varchar2) is
  begin
    dbms_output.put_line('more_attr_set_txt#('||in_name_attr||','||in_key||','||in_val||')');
  end;


/*****************************************************************************************/
  overriding member procedure more_attr_set_dat#(in_name_attr varchar2, in_key number, in_val date) is
  begin
    dbms_output.put_line('more_attr_set_dat#('||in_name_attr||','||in_key||','||in_val||')');
  end;


/*****************************************************************************************/
  overriding member function get_ListID# return number is
  begin
    dbms_output.put_line('get_ListID#()');
  end;


/*****************************************************************************************/
  overriding member procedure more_attr_set_prc_trud#( in_uch varchar2, in_ListID number, in_Unizak number, in_prc number) is
  begin
    dbms_output.put_line('more_attr_set_prc_trud#('||in_uch||','||in_ListID||','||in_Unizak||','||in_prc||')');
  end;
  
  
end;
/
