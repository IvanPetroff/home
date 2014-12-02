create or replace type tSklDok_core force as object
(
  -- Author  : Администратор
  -- Created : 02.12.2014 12:48:29
  -- Purpose : 
  dummy number,
  xml XMLtype,
  xmlZag XMLtype,
  xmlSod XMLtype,
CONSTRUCTOR function tSklDok_core(x number) return self as result,
  member procedure setXML(x XMLtype),
  member procedure InsertZagDok(x XMLtype),
  member procedure newDok(x XMLtype),
  member procedure saveDok(x XMLtype),
  member function GetDokNZ(x XMLtype) return number



  
  -- Member functions and procedures
)
not final;
/
create or replace type body tSklDok_core is
  
  -- Member procedures and functions
CONSTRUCTOR function tSklDok_core(x number) return self as result is
begin
  xml := XMLtype('');
  xmlZag := XMLtype('');
  xmlSod := XMLtype('');
  null;
end;

member procedure InsertZagDok(x XMLtype) is
begin
  raise_application_error(-20001,'method not overriding!');
end;


member procedure setXML(x XMLtype) is
begin
  xml := x;
  xmlZag := xml.extract('/doc/zag');
  xmlSod := xml.extract('/doc/sod');
  InsertZagDok(xmlZag);
null;
end;

member function GetDokNZ(x XMLtype) return number is
begin
  return x.extract('/doc/@nz').getstringval();
  null;
end;

member procedure newDok(x XMLtype) is
begin
  xml := x;
  null;
end;

member procedure saveDok(x XMLtype) is
begin
  null;
end;

  
end;
/
