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
  m_kod varchar2(24),
  r_sort varchar2(18),
  skl varchar2(8),
  
  -- Member functions and procedures
  constructor function OstBase(in_id number, in_type varchar2) return self as result,
  member procedure OpenKart(in_id number, in_tip varchar2),
  member procedure AddKol(in_addkol number, in_prizn varchar2),
  member FUNCTION GetMD5(plain_text VARCHAR2) RETURN VARCHAR2,
  member function GetKol(in_prizn varchar2) return number
  
  
  
)
/
create or replace type body OstBase is
  
  -- Member procedures and functions
  constructor function OstBase(in_id number, in_type varchar2) return self as result is
  begin
    if in_id is not null and in_type is not null then
      OpenKart(in_id,in_type);
    end if;
    null;
  end;

  member procedure OpenKart(in_id number, in_tip varchar2) is
  begin
    select RAWTOHEX(DBMS_OBFUSCATION_TOOLKIT.MD5(INPUT => UTL_RAW.CAST_TO_RAW(
      xmltype(cursor(select * from asu_ost_mat where id=in_id and type=in_tip)).extract('/ROWSET/ROW').getstringval()
      ))) into md5 from dual;
      
    select xmltype(cursor(select * from asu_ost_mat where id=in_id and type=in_tip)).extract('/ROWSET/ROW') into rec_xml from dual;
      
    select kol, skl
      into kol, skl
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
  
  member function GetKol(in_prizn varchar2) return number is
  Result number;
  begin
    select decode(p.prizn,null,o.kol-(select nvl(sum(kol),0) from asu_prizn_ost_mat where ost_id=o.id and type=o.type), p.kol) x
    into Result
    from asu_ost_mat o, asu_prizn_ost_mat p 
    where o.type=self.tip and o.id=self.id and o.id=p.ost_id(+) and o.type=p.type(+)
    and nvl(p.prizn,' ')=nvl(in_prizn,' ');
    
    return Result;
  end;
  
  
member FUNCTION GetMD5(plain_text VARCHAR2) RETURN VARCHAR2 IS  
BEGIN  
   RETURN RAWTOHEX(DBMS_OBFUSCATION_TOOLKIT.MD5(INPUT => UTL_RAW.CAST_TO_RAW(plain_text) ));  
END;
  
  
end;
/
