create or replace type Dok46 force under DokBase
(
  -- Author  : Администратор
  -- Created : 03.12.2014 9:04:51
  -- Purpose : 
  overriding member procedure Init,
  overriding member procedure doCommitOnSkl(in_x XMLtype),
  overriding member function isCanCommitOnSkl return boolean,
  overriding member function isUserCanCommitOnSkl return boolean,
  member procedure xxx(xx asu_zag_dok%rowtype)
  


  
  
  
)
not final;
/
create or replace type body Dok46 is
  
  -- Member procedures and functions
  overriding member procedure Init is
  begin
    null;
  end;
  
  

  overriding member procedure doCommitOnSkl(in_x XMLtype) is
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
    if self.GetDateCommitOnSkl() is not null then
        raise_application_error(-20001,'Документ уже проведён на складе '||self.GetDateCommitOnSkl());
    end if;
    if self.GetDateCommitOnSnab() is null then
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
        self.doUpdateXMLvalue(tmp_x, '/DOC/SOD/ROW['||I||']/KOL', skl_kol);
        ost_from.OpenKart(tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ_PRIH/text()').getstringval(), 'П');
        ost_to.OpenKart(tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ_CEH/text()').getstringval(), 'П');
        ost_from.AddKol( -skl_kol, x_prizn);
        ost_to.AddKol( skl_kol, x_prizn );
      null;
    end loop;
    self.doUpdateXMLvalue(tmp_x, '/DOC/ZAG/ROW/D_SKL_POST', sysdate);
    self.doUpdateXMLvalue(tmp_x, '/DOC/ZAG/ROW/U_SKL_POST', user);
--    update asu_zag_dok set d_skl_post=sysdate, u_skl_post=user where nz=self.nz;
    x := tmp_x;    
    null;
  end;
  
  overriding member function isCanCommitOnSkl return boolean is
  begin
    if self.getdatecommitonsnab() is null then
        return false;
    end if;
    return true;
    null;
  end;


  overriding member function isUserCanCommitOnSkl return boolean is
  begin
    if get_env_var(user,'STEP_DOK')='СКЛАД' or get_env_var(user,'N_KLAD') = self.ceh_post then
      return true;
    end if;
    return false;
    null;
  end; 
  
  member procedure xxx(xx asu_zag_dok%rowtype) is
  begin
    null;
  end;
  
  
end;
/
