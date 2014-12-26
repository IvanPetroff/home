declare
obj class_spreadlist;
n number;
begin
  obj := class_spreadlist;
  n := obj.CreateList(62,'01-11-2014','01-12-2014');
  dbms_output.put_line(n);
  null;
end;
