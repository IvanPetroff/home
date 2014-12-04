create or replace type DokBase force as object
(
  -- Author  : Администратор
  -- Created : 03.12.2014 9:03:06
  -- Purpose : 
  x XMLtype,
  nz number,
  member procedure Init,
  member procedure OpenDok(in_nz number),
  member procedure CloseDok,
  member function GetSodRowCount return number,
  member function GetDateCommitOnSkl return date,
  member function GetDateCommitOnSnab return date,
  member procedure doCommitOnSnab,
  member procedure doCommitOnSkl(in_x XMLtype)
  

  
  

)
not final;
/
create or replace type body DokBase is
  
  -- Member procedures and functions
  member procedure Init is
  begin
    x := XMLtype('<doc></doc>');
    null;
  end;
  
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
    
    select appendchildxml(x, '/DOC/ZAG', xmltype(cursor(select * from asu_zag_dok where nz=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;
        
    select appendchildxml(x, '/DOC/SOD', xmltype(cursor(select * from asu_sod_dok where nz_zag=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;

    null;
  end;

  member procedure CloseDok is
  begin
    x := null;
    null;
  end;
  
  member function GetSodRowCount return number is
  cnt number;
  begin
    select count(*) into cnt from table(xmlsequence(x.extract('DOC/SOD/ROW')));
    return cnt;
    null;
  end;
  
  member function GetDateCommitOnSkl return date is
  d date;
  begin
    select coalesce(extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POST'),extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POTR')) into d from dual;
    return d;
  end;

  member function GetDateCommitOnSnab return date is
  d date;
  begin
    select extractvalue(x,'/DOC/ZAG/ROW/D_SNAB') into d from dual;
    return d;
  end;

  member procedure doCommitOnSnab is
  begin
    if nvl(get_env_var(user,'STEP_DOK'),' ') <> 'СНАБ' then
--        raise_application_error(-20001,'Нет прав!');
        null;
    end if;

    for Cur in (select x.existsnode('DOC/ZAG/ROW/D_SKL_POTR') n from dual) loop
        if Cur.n=1 then
            select updatexml(x,'DOC/ZAG/ROW/D_SKL_POTR/text()',sysdate) into x from dual;
        else
            select appendchildxml(x,'DOC/ZAG/ROW',XMLelement("D_SKL_POTR",to_char(sysdate))) into x from dual;
        end if;
    end loop;
  end;

  member procedure doCommitOnSkl(in_x XMLtype) is
/*  cursor Cur_usr(xx XMLtype) is select extractvalue(column_value,'/ROW/NZ') nz, extractvalue(column_value,'/ROW/KOL') kol 
                from table(xmlsequence(xx.extract('/SKL/ROW')));
  cursor Cur_db(xx XMLtype) is select extractvalue(column_value,'/ROW/NZ') nz, extractvalue(column_value,'/ROW/KOL_TREB') kol_treb 
                from table(xmlsequence(xx.extract('/DOC/SOD/ROW')));
*/  
  begin
    for Cur in ( 
        with  db as (select extractvalue(column_value,'/ROW/NZ') nz, extractvalue(column_value,'/ROW/KOL_TREB') kol_treb 
                    from table(xmlsequence(x.extract('/DOC/SOD/ROW')))),
             usr as (select extractvalue(column_value,'/ROW/NZ') nz, extractvalue(column_value,'/ROW/KOL') kol 
                    from table(xmlsequence(in_x.extract('/SKL/ROW'))))
        select usr.nz,usr.kol,db.kol_treb 
        from db
        full join usr on db.nz=usr.nz
    ) loop
        if Cur.kol is null or Cur.kol_treb is null then
            raise_application_error(-20001,'Не все данные указаны, либо указаны лишние!');
        end if;
        if Cur.kol > Cur.kol_treb then
            raise_application_error(-20001,'Выдаваемое количество ['||Cur.kol||'] больше затребованного ['||Cur.kol_treb||']');
        end if;
        
        null;
    end loop;
    
    null;
  end;
  
  
end;
/
