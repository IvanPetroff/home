create or replace package admdba.skldok_pkg is

  -- Author  : �������������
  -- Created : 28.11.2014 12:46:25
  -- Purpose : 
  
  -- Public type declarations
procedure ADD_TO_DOK(x xmltype);
procedure COMMIT_DOK(s clob);
FUNCTION blob_to_xmltype (blob_in IN BLOB) RETURN XMLTYPE;
procedure SAVE_DOK(x XMLtype);

  
end skldok_pkg;
/
create or replace package body admdba.skldok_pkg is
TYPE tGuidList is table of varchar2(32);
GuidList tGuidList;

procedure BEGIN_DOK(id out varchar2) is
begin
  id := sys_guid();
--  GuidList.
  null;
end;

procedure ADD_TO_DOK(x xmltype) is
  XX XMLTYPE;
begin
  raise_application_error(-20001, x.getrootelement());
--  XX := XMLTYPE(X);
  null;
end;

FUNCTION blob_to_xmltype (blob_in IN BLOB)
RETURN XMLTYPE
AS
v_clob CLOB;
v_varchar VARCHAR2(32000);
v_start PLS_INTEGER := 1;
v_buffer PLS_INTEGER := 32000;
BEGIN
  raise_application_error(-20001,'!');
DBMS_LOB.CREATETEMPORARY(v_clob, TRUE);

FOR i IN 1..CEIL(DBMS_LOB.GETLENGTH(blob_in) / v_buffer)
LOOP
if i=1 then
  raise_application_error(-20001,'!');
end if;

v_varchar := UTL_RAW.CAST_TO_VARCHAR2(DBMS_LOB.SUBSTR(blob_in, v_buffer, v_start));
DBMS_LOB.WRITEAPPEND(v_clob, LENGTH(v_varchar), v_varchar);
v_start := v_start + v_buffer;
END LOOP;

RETURN XMLTYPE(v_clob);
END blob_to_xmltype;


procedure COMMIT_DOK(s clob) is
x xmltype;
begin
  x := xmltype(s);
  raise_application_error(-20001, length(s));
  null;
end;

procedure ROLLBACK_DOK is
begin
  null;
end;

procedure SAVE_DOK(x XMLtype) is
wid_dok number;
tip varchar2(1);
x_zag XMLtype := x.extract('/doc/zag');
x_sod XMLtype := x.extract('/doc/sod');
cnt number := 0;
begin
  wid_dok := nvl(x.extract('/doc/@wid').GetStringVal(), 0);
  tip := nvl(x.extract('/doc/@type').GetStringVal(), ' ');
  for cur in (select * from table(XMLsequence(x_sod.extract('sod/row')))) loop
    cnt := cnt+1;
    null;
  end loop;
  raise_application_error(-20001, cnt);
  
  
  null;
end;


begin
  -- Initialization
  null;
end skldok_pkg;
/
