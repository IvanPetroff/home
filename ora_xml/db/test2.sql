declare
x DokBase;
s1 varchar2(100);
s2 varchar2(100);
begin
  x := DokBase(null,null);
  x.doSeparateXMLtag('/DOC/SOD/ROW/KOL',s1,s2);
  dbms_output.put_line(s1);
  dbms_output.put_line(s2);
  null;
end;
