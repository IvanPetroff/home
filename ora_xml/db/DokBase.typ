create or replace type DokBase force as object
(
  -- Author  : Администратор
  -- Created : 03.12.2014 9:03:06
  -- Purpose : 
  x XMLtype,
  nz number, -- регистрационный номер документа
  d_skl_post date,
  d_skl_potr date, 
  d_snab date, -- Дата прохождения через снабжение
  ceh_post varchar2(8),
  
  member procedure Init,
  member procedure OpenDok(in_nz number),
  member procedure CloseDok,
  member function GetSodRowCount return number,
  member function GetDateCommitOnSkl return date,
  member function GetDateCommitOnSnab return date,
  member procedure doCommitOnSnab,
  member procedure doCommitOnSkl(in_x XMLtype),
  member procedure doCommitOnSkl#(in_x XMLtype),
  member procedure doUpdateXMLvalue( in_x XMLtype, in_tag varchar2, in_val varchar2),
  member procedure doSeparateXMLtag(in_tag varchar2, out_path out varchar2, out_tag out varchar2),
  member procedure LoadZagDok,
  member function isCanCommitOnSkl return boolean,
  member function isUserCanCommitOnSkl return boolean
  
  
  
  

  
  

)
not final;
/
create or replace type body DokBase is
  
  -- Member procedures and functions
/************************************************************************************************/
  member procedure Init is
  begin
    x := XMLtype('<doc></doc>');
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
--    LoadSodDok();
    
    select appendchildxml(x, '/DOC/ZAG', xmltype(cursor(select * from asu_zag_dok where nz=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;
        
    select appendchildxml(x, '/DOC/SOD', xmltype(cursor(select * from asu_sod_dok where nz_zag=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;

    null;
  end;

/************************************************************************************************/
  member procedure LoadZagDok is
  begin
    select d_snab, d_skl_post, d_skl_potr, ceh_post 
      into self.d_snab, self.d_skl_post, self.d_skl_potr, self.ceh_post
      from asu_zag_dok
      where nz=self.nz;
    null;
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
    return nvl(self.d_skl_post,self.d_skl_potr);
--    select coalesce(extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POST'),extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POTR')) into d from dual;
--    return d;
  end;

/************************************************************************************************/
  member function GetDateCommitOnSnab return date is
  d date;
  begin
    return self.d_snab;
--    select extractvalue(x,'/DOC/ZAG/ROW/D_SNAB') into d from dual;
--    return d;
  end;

/************************************************************************************************/
  member procedure doCommitOnSnab is
  begin
    if nvl(get_env_var(user,'STEP_DOK'),' ') <> 'СНАБ' then
        raise_application_error(-20001,'Нет прав!');
    end if;
    
    update zag_dok set d_snab=sysdate where nz=self.nz 
    returning d_snab into self.d_snab;
    
    
    
--    doUpdateXMLvalue( x, 'DOC/ZAG/ROW/D_SKL_POTR', sysdate);

/*    for Cur in (select x.existsnode('DOC/ZAG/ROW/D_SKL_POTR') n from dual) loop
        if Cur.n=1 then
            select updatexml(x,'DOC/ZAG/ROW/D_SKL_POTR/text()',sysdate) into x from dual;
        else
            select appendchildxml(x,'DOC/ZAG/ROW',XMLelement("D_SKL_POTR",to_char(sysdate))) into x from dual;
        end if;
    end loop;
*/
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
  
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
  
end;
/
