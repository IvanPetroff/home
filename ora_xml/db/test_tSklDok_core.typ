create or replace type test_tSklDok_core
force under tSklDok_core
--as object
(
  -- Author  : Администратор
  -- Created : 02.12.2014 12:48:29
  -- Purpose :
  CONSTRUCTOR function test_tSklDok_core(x number) return self as result,
  overriding member procedure InsertZagDok(x XMLtype),
  member procedure test
);
/
create or replace type body test_tSklDok_core is
  
  -- Member procedures and functions
CONSTRUCTOR function test_tSklDok_core(x number) return self as result is
begin
  null;
end;

overriding member procedure InsertZagDok(x XMLtype) is
begin
  null;
end;

member procedure test is
begin
  null;
end;


end;
/
