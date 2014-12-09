create or replace type Dok46 force under DokBase
(
  -- Author  : Администратор
  -- Created : 03.12.2014 9:04:51
  -- Purpose : 
  overriding member procedure Init,
  overriding member procedure doCommitOnSkl(in_x XMLtype),
  overriding member function isCanCommitOnSkl return boolean,
  overriding member function isUserCanCommitOnSkl return boolean,
  overriding member procedure check_DokReadyToCommitSnab#,
  overriding member procedure check_UserReadyToCommitSnab#,
  overriding member procedure doCommitToSnab#(in_x XMLtype),
  overriding member procedure check_DataReadyToCommitSnab#(in_x XMLtype)
  
  
  
  
  


  
  
  
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
  ost_from OstBase := OstBase(null,null);
  ost_to OstBase := OstBase(null,null);
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
    if get_env_var(user,'STEP_DOK')='СКЛАД' or get_env_var(user,'N_KLAD') = self.rec_zag.ceh_post then
      return true;
    end if;
    return false;
    null;
  end; 
  

  overriding member procedure check_DokReadyToCommitSnab# is
  begin
    if self.rec_zag.dd_ceh is null then
        raise_application_error(-20001,'Документ не имеет подписи цеха!');
    end if;
    if self.rec_zag.d_skl_post is not null then
        raise_application_error(-20001,'Документ уже проведён на складе!');
    end if;
    null;
  end;
  
  overriding member procedure check_UserReadyToCommitSnab# is
  begin
    if nvl(get_env_var(user,'STEP_DOK'),' ')<>'СНАБ' then
      raise_application_error(-20001,'Нет прав проводить документ!');
    end if;
  end;


  overriding member procedure check_DataReadyToCommitSnab#(in_x XMLtype) is
  tmp_x XMLtype := in_x;
  cnt number;
  I number;
  x_nz number;
  x_kol number;
  x_prizn asu_sod_dok.prizn%TYPE;
  x_nz_prih asu_sod_dok.nz_prih%TYPE;
  x_kod_mat asu_sod_dok.kod_mat%TYPE;
  x_ceh_post asu_zag_dok.ceh_post%TYPE;

  ost_from OstBase := OstBase(null,null);
  begin
    select count(*) into cnt from asu_sod_dok where nz_zag=self.rec_zag.nz;
    -- Проверяем, что снабженец указал все карточки
    x_ceh_post := in_x.extract('/ZAG/ROW['||I||']/CEH_POST/text()').getstringval();
    self.chk_not_null(x_ceh_post, 'Склад-поставщик');
    
    
  for Cur in (
    with x as (
      select in_x.extract('/SOD/ROW['||I||']/NZ/text()').getstringval() nz
      from table(xmlsequencetype(in_x.extract('/SOD/ROW')))
    )
    select x.* from 
    table(self.rec_sod.rec) t 
    full outer join 
    (select * from x) xx on xx.nz=t.nz
  
  ) loop
  null;
  end loop;
    
    I := 0;
    while true loop
        I := I+1;
        x_nz := in_x.extract('/SOD/ROW['||I||']/NZ/text()').getstringval();
        exit when x_nz is null;
        x_kol := in_x.extract('/SOD/ROW['||I||']/KOL_TREB/text()').getstringval();
        x_prizn := in_x.extract('/SOD/ROW['||I||']/PRIZN/text()').getstringval();
        x_nz_prih := in_x.extract('/SOD/ROW['||I||']/NZ_PRIH/text()').getstringval();
        x_kod_mat := in_x.extract('/SOD/ROW['||I||']/KOD_MAT/text()').getstringval();

        self.chk_not_null(x_kol, 'в строке', I, 'количество');
        self.chk_not_null(x_prizn, 'в строке', I, 'номер карточки');
        self.chk_not_null(x_kod_mat, 'в строке', I, 'код');
        
--        self.doUpdateXMLvalue(tmp_x, '/DOC/SOD/ROW['||I||']/KOL', skl_kol);
        ost_from.OpenKart(x_nz_prih, 'П');
        if ost_from.m_kod <> x_kod_mat then
          raise_application_error(-20001,'Несоответствие кода и номера карточки в строке '||I);
        end if;
        if ost_from.skl <> x_ceh_post then
          raise_application_error(-20001,'Несоответствие номера склада в строке '||I);
        end if;
        for Curr in (select * from table(self.rec_sod.rec) where nz=x_nz) loop
          null;
        end loop;
--        ost_from.GetKol(x_prizn);
      null;
    end loop;
    
      
    null;
  end;

  
  overriding member procedure doCommitToSnab#(in_x XMLtype) is
  begin
    rec_zag.null_rec(in_d_snab=>NULL, in_u_snab=>NULL);
    rec_zag.update_rec(in_d_snab=>sysdate, in_u_snab=>user);
  end;
  
  
end;
/
