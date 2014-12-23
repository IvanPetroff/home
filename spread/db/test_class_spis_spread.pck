create or replace package test_class_spis_spread is

  -- Author  : Администратор
  -- Created : 23.12.2014 8:14:30
  -- Purpose : 
  
  -- Public type declarations
  procedure test_document_should_be_loaded;
  

end test_class_spis_spread;
/
create or replace package body test_class_spis_spread is

  function get_output return varchar2 is
    s varchar2(2000);
    n number;
  begin
    dbms_output.get_line(s,n);
    return s;
    null;
  end;  


  procedure chk(b boolean) is
  begin
    if b = true then
      dbms_output.put_line('OK');
    else
      dbms_output.put_line('failed! Test case '||debug_pkg.who_called_me(1) ); 
    end if;
    null;
  end;  
 
  -- Private type declarations
  procedure test_document_should_be_loaded is
    obj class_spis_spread#;
  begin
    obj := class_spis_spread#(1234);
    chk(get_output = 'load_dok#(1234)');
  end;

begin
  -- Initialization
  null;
end test_class_spis_spread;
/
