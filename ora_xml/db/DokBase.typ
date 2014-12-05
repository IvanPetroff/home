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
  member procedure doCommitOnSkl(in_x XMLtype),
  member procedure doCommitOnSkl#(in_x XMLtype),
  member procedure doUpdateXMLvalue( in_x XMLtype, in_tag varchar2, in_val varchar2),
  member procedure doSeparateXMLtag(in_tag varchar2, out_path out varchar2, out_tag out varchar2)
  
  
  

  
  

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
    
    select appendchildxml(x, '/DOC/ZAG', xmltype(cursor(select * from asu_zag_dok where nz=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;
        
    select appendchildxml(x, '/DOC/SOD', xmltype(cursor(select * from asu_sod_dok where nz_zag=in_nz)).extract('/ROWSET/ROW')) 
        into x 
        from dual;

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
    select coalesce(extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POST'),extractvalue(x,'/DOC/ZAG/ROW/D_SKL_POTR')) into d from dual;
    return d;
  end;

/************************************************************************************************/
  member function GetDateCommitOnSnab return date is
  d date;
  begin
    select extractvalue(x,'/DOC/ZAG/ROW/D_SNAB') into d from dual;
    return d;
  end;

/************************************************************************************************/
  member procedure doCommitOnSnab is
  begin
    if nvl(get_env_var(user,'STEP_DOK'),' ') <> 'СНАБ' then
--        raise_application_error(-20001,'Нет прав!');
        null;
    end if;
    doUpdateXMLvalue( x, 'DOC/ZAG/ROW/D_SKL_POTR', sysdate);

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
/*  cursor Cur_usr(xx XMLtype) is select extractvalue(column_value,'/ROW/NZ') nz, extractvalue(column_value,'/ROW/KOL') kol 
                from table(xmlsequence(xx.extract('/SKL/ROW')));
  cursor Cur_db(xx XMLtype) is select extractvalue(column_value,'/ROW/NZ') nz, extractvalue(column_value,'/ROW/KOL_TREB') kol_treb 
                from table(xmlsequence(xx.extract('/DOC/SOD/ROW')));
*/  
--  sod_cnt number := 0;
  x_nz number;
  x_kol number;
  x_prizn asu_sod_dok.prizn%TYPE;
  skl_kol number;
  I number;
  tmp_x XMLtype := x;
  ost_from OstBase := OstBase(null,null,null,null,null);
  ost_to OstBase := OstBase(null,null,null,null,null);
  begin
    -- Проверяем возможность прохождения документа через очередную инстанцию
    if GetDateCommitOnSkl() is not null then
        raise_application_error(-20001,'Документ уже проведён на складе '||GetDateCommitOnSkl());
    end if;
    if GetDateCommitOnSnab() is null then
        raise_application_error(-20001,'Документ ещё не обработан исполнителем отдела снабжения');
    end if;
    
    -- Проверяем, что кладовщик указал все количества
    I := 0;
    while true loop
        I := I+1;
        x_nz := tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ/text()').getstringval();
        exit when x_nz is null;
        x_kol := tmp_x.extract('/DOC/SOD/ROW['||I||']/KOL_TREB/text()').getstringval();
        x_prizn := tmp_x.extract('/DOC/SOD/ROW['||I||']/PRIZN/text()').getstringval();
        
        select max(extractvalue(column_value,'/ROW/KOL')) kol into skl_kol
                    from table(xmlsequence(in_x.extract('/SKL/ROW')))
                    where extractvalue(column_value,'/ROW/NZ')=x_nz;
        if skl_kol is null then
            raise_application_error(-20001,'Не все данные о количестве выдаваемого указаны (в строке '||I||')' );
        end if;
        if skl_kol > x_kol then
            raise_application_error(-20001,'Выдаваемое количество ['||skl_kol||'] больше затребованного ['||x_kol||'] (в строке '||I||')');
        end if;
        doUpdateXMLvalue(tmp_x, '/DOC/SOD/ROW['||I||']/KOL', skl_kol);
        ost_from.OpenKart(tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ_PRIH/text()').getstringval(), 'П');
        ost_to.OpenKart(tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ_CEH/text()').getstringval(), 'П');
        ost_from.AddKol( -skl_kol, x_prizn);
        ost_to.AddKol( skl_kol, x_prizn );
      null;
    end loop;
    doUpdateXMLvalue(tmp_x, '/DOC/ZAG/ROW/D_SKL_POST', sysdate);
    doUpdateXMLvalue(tmp_x, '/DOC/ZAG/ROW/U_SKL_POST', user);
--    update asu_zag_dok set d_skl_post=sysdate, u_skl_post=user where nz=self.nz;
    x := tmp_x;    
    null;
  end;
  
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
  
end;
/
