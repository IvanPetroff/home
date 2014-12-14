create or replace force type m_Dok46 under Dok46
(
  -- Author  : Администратор
  -- Created : 11.12.2014 10:40:44
  -- Purpose : 
  constructor function m_Dok46 return self as result,
  overriding member procedure Init,

  overriding member procedure StoreDok,
  overriding member procedure DeleteDok(in_nz number)
  
  
  
)
/
create or replace force type body m_Dok46 is
  
/*
TODO: owner="Администратор" created="11.12.2014"
text="неплохо было бы сделать подсчёт количества вызовов перекрытых методов.
      а также проверку передаваемых им параметров.
      т.е. чтобы в тесте можно было бы описать, что ожидается вызов такого-то перекрытого метода столько-то раз,
      что в первом вызове будут переданы такие-то параметры, во втором такие-то и т.д."
*/

  constructor function m_Dok46 return self as result is
  begin
    Init();
    return; 
  end;

  

  overriding member procedure Init is
  begin
    (self as Dok46).Init();
    self.lib := m_t_lib;  
    null;
  end;


  -- Member procedures and functions
  overriding member procedure StoreDok is
  begin
    debug_pkg.put_line(null);
    null;
  end;
  
  overriding member procedure DeleteDok(in_nz number) is
  begin
    debug_pkg.put_line(in_nz);
    null;
  end;
  
  

  
end;
/
