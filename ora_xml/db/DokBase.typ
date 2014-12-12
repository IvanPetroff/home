create or replace force type DokBase force  as object
( 
  -- Author  : Администратор
  -- Created : 03.12.2014 9:03:06
  -- Purpose : 
  lib t_lib,
  x XMLtype,
  nz number, -- регистрационный номер документа
  rec_zag T_ZagDok,
  rec_sod T_SodDok,

  constructor function DokBase return self as result,
  
  member procedure Init,
  member procedure OpenDok(in_nz number),
  member procedure CloseDok,
  member function GetSodRowCount return number,
  member function GetDateCommitOnSkl return date,
  member function GetDateCommitOnSnab return date,
  member procedure doCommitToSnab(in_x XMLtype),
  member procedure doCommitOnSkl(in_x XMLtype),
  member procedure doCommitOnSkl#(in_x XMLtype),
  member procedure doUpdateXMLvalue( in_x XMLtype, in_tag varchar2, in_val varchar2),
  member procedure doSeparateXMLtag(in_tag varchar2, out_path out varchar2, out_tag out varchar2),
  member procedure LoadZagDok,
  member procedure LoadSodDok,
  member function isCanCommitOnSkl return boolean,
  member function isUserCanCommitOnSkl return boolean,
  member procedure check_DokReadyToCommitSnab#,
  member procedure check_UserReadyToCommitSnab#,
  member procedure doCommitToSnab#(in_x XMLtype),
  member procedure check_DataReadyToCommitSnab#(in_x XMLtype),
  member procedure chk_not_null(x varchar2, str1 varchar2 := null, str2 varchar2 := null, str3 varchar2 := null),
  member procedure CreateDok(in_x XMLtype),
  member procedure StoreDok,
  member procedure DeleteDok(in_nz number)

)
not final;
/
create or replace type body DokBase is
  
    
  constructor function DokBase return self as result is
  begin 
    Init();
    return;
  end;
 
  -- Member procedures and functions
/************************************************************************************************/
  member procedure Init is
  begin
    lib := t_lib;
    null;
  end;
  
/************************************************************************************************/
  member procedure OpenDok(in_nz number) is
--  r asu_zag_dok%rowtype;
--  xx sys.anydata;
  begin
    x := XMLtype('<DOC><ZAG></ZAG><SOD></SOD></DOC>');
    for Cur in (select count(*) cnt from asu_zag_dok where nz=in_nz) loop
        if Cur.cnt=0 then
            raise_application_error(-20001,'Документ не найден!');
        end if;
    end loop;
    self.nz := in_nz;
    LoadZagDok();
    LoadSodDok();
    
/*    select appendchildxml(x, '/DOC/ZAG', xmltype(cursor(select * from asu_zag_dok where nz=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;
        
    select appendchildxml(x, '/DOC/SOD', xmltype(cursor(select * from asu_sod_dok where nz_zag=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;

    null;*/
  end;

/************************************************************************************************/
  member procedure LoadZagDok is
  begin
    rec_zag := T_ZagDok(self.nz);
  end;


/************************************************************************************************/
  member procedure LoadSodDok is
  begin
    rec_sod := T_SodDok(self.nz);
  end;

/************************************************************************************************/
  member procedure CloseDok is
  begin
    x := null;
    null;
  end;
  
/************************************************************************************************/
  member function GetSodRowCount return number is
  cnt number;
  begin
    select count(*) into cnt from table(xmlsequence(x.extract('DOC/SOD/ROW')));
    return cnt;
    null;
  end;
  
/************************************************************************************************/
  member function GetDateCommitOnSkl return date is
  d date;
  begin
    return nvl(rec_zag.d_skl_post,rec_zag.d_skl_potr);
--    select coalesce(extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POST'),extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POTR')) into d from dual;
--    return d;
  end;

/************************************************************************************************/
  member function GetDateCommitOnSnab return date is
  d date;
  begin
    return rec_zag.d_snab;
--    select extractvalue(x,'/DOC/ZAG/ROW/D_SNAB') into d from dual;
--    return d;
  end;


  member procedure check_DokReadyToCommitSnab# is
  begin
    raise_application_error(-20001, 'Метод check_DokReadyToCommitSnab не реализован в базовом классе!');
    null;
  end;

  member procedure check_UserReadyToCommitSnab# is
  begin
    raise_application_error(-20001, 'Метод check_UserReadyToCommitSnab не реализован в базовом классе!');
  end;

  member procedure check_DataReadyToCommitSnab#(in_x XMLtype) is
  begin
    raise_application_error(-20001, 'Метод check_DataReadyToCommitSnab не реализован в базовом классе!');
  end;


  member procedure doCommitToSnab#(in_x XMLtype) is
  begin
    raise_application_error(-20001, 'Метод doCommitToSnab не реализован в базовом классе!');
  end;


/************************************************************************************************/
  member procedure doCommitToSnab(in_x XMLtype) is
  begin
    check_DokReadyToCommitSnab#();
    check_UserReadyToCommitSnab#();
    check_DataReadyToCommitSnab#(in_x);
    doCommitToSnab#(in_x);
  end;
  
  member procedure doSeparateXMLtag(in_tag varchar2, out_path out varchar2, out_tag out varchar2) is
  PosLastDelimiter number;
  begin
    PosLastDelimiter := instr(in_tag,'/',-1);
    out_Path := substr(in_tag, 1, PosLastDelimiter-1);
    out_Tag := substr(in_tag, PosLastDelimiter+1);
  end;
  
  member procedure doUpdateXMLvalue( in_x XMLtype, in_tag varchar2, in_val varchar2) is
  xmlPath varchar2(255);
  xmlTag varchar2(64);
  PosLastDelimiter number;
  begin
    doSeparateXMLtag(in_tag, xmlPath, xmlTag);
    for Cur in (select in_x.existsnode(in_tag) n from dual) loop
        if Cur.n=1 then
            select updatexml(in_x,in_tag||'/text()',in_val) into x from dual;
        else
            select appendchildxml( in_x, xmlPath, XMLelement( xmlTag, to_char(in_val))) into x from dual;
        end if;
    end loop;
    null;
  end;


  member procedure doCommitOnSkl#(in_x XMLtype) is
  begin
    
    null;
  end;

/************************************************************************************************/
  member procedure doCommitOnSkl(in_x XMLtype) is
  begin
    null;
  end;



  member function isCanCommitOnSkl return boolean is
  begin
    -- функция-заглушка. Должна переопределяться в производных классах
    -- делает проверку того, что документ может быть проведён на складе
    -- т.е. присутствуют все признаки (данные) этого
    null;
  end;

  member function isUserCanCommitOnSkl return boolean is
  begin
    -- функция-заглушка. Должна переопределяться в производных классах
    -- делает проверку того, что ПОЛЬЗОВАТЕЛЬ может провести этот документ через склад
    null;
  end;


  member procedure chk_not_null(x varchar2, str1 varchar2 := null, str2 varchar2 := null, str3 varchar2 := null) is
  begin
    if x is null then
      raise_application_error(-20001,nvl(str1,' ')||' '||nvl(str2,' ')||' '||nvl(str3,' ')||' не может быть пустым!');
    end if;
    null;
  end;


  member procedure CreateDok(in_x XMLtype) is
  begin
    raise_application_error(-20001, 'Метод не реализован в базовом классе!');
    null;
  end;
  
  member procedure StoreDok is
  -- Запись содержимого rec_zag и rec_sod в базу с базовым контролем целостности документа
  begin
    rec_zag.Store();
    rec_sod.Store();
    null;
  end;
  
  member procedure DeleteDok(in_nz number) is
  -- Удалить документ из базы
  begin
    null;
  end;


/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
  
end;
/
