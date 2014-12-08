create or replace type OstBase as object
(
  -- Author  : Администратор
  -- Created : 05.12.2014 13:52:49
  -- Purpose : 
  id number,
  tip varchar2(1),
  kol number,
  md5 varchar2(32),
  rec_xml XMLtype,
  
  -- Member functions and procedures
  member procedure OpenKart(in_id number, in_tip varchar2),
  member procedure AddKol(in_addkol number, in_prizn varchar2),
  member FUNCTION GetMD5(plain_text VARCHAR2) RETURN VARCHAR2
  
  
)
/
create or replace type body OstBase is
  
  -- Member procedures and functions
  member procedure OpenKart(in_id number, in_tip varchar2) is
  begin
    select RAWTOHEX(DBMS_OBFUSCATION_TOOLKIT.MD5(INPUT => UTL_RAW.CAST_TO_RAW(
      xmltype(cursor(select ceeded * from asu_ost_mat where id=in_id and type=in_tip)).extract('/ROWSET/ROW').getstringval()
      ))) into md5 from dual;
      
    select xmltype(cursor(select * from asu_ost_mat where id=in_id and type=in_tip)).extract('/ROWSET/ROW') into rec_xml from dual;
      
    select kol into kol
        from asu_ost_mat 
        where id=in_id and type=in_tip;
    null;
  end;

  member procedure AddKol(in_addkol number, in_prizn varchar2) is
  begin
    if (kol+in_addkol)<0 then
        raise_application_error(-20001,'Перерасход количества на карточке склада ['||id||'] на ('||(kol+in_addkol)||')');
    end if;
    kol := kol + in_addkol;
      
--    update asu_ost_mat set kol=self.kol where id=self.id and type=self.tip;
    null;
  end;
  
member FUNCTION GetMD5(plain_text VARCHAR2) RETURN VARCHAR2 IS  
BEGIN  
   RETURN RAWTOHEX(DBMS_OBFUSCATION_TOOLKIT.MD5(INPUT => UTL_RAW.CAST_TO_RAW(plain_text) ));  
END;
  
  
end;
/
