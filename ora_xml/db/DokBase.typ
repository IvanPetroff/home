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
  member procedure OpenDok(in_nz number, in_wid_dok number := null, in_type varchar2 := null),
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
  member procedure StoreDok,
  member procedure DeleteDok(in_nz number),
  member procedure ParseXML(in_x XMLtype),
  member procedure CreateDok(in_nz in out number, in_type varchar2, in_x XMLtype),
  member procedure OnBeforeStoreDok,
  member procedure doNextStepDok(in_nz number, in_x XMLtype),
  member procedure doPrevStepDok(in_nz number, in_x XMLtype)
  

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
  member procedure OpenDok(in_nz number, in_wid_dok number := null, in_type varchar2 := null) is
--  r asu_zag_dok%rowtype;
--  xx sys.anydata;
  begin
--    x := XMLtype('<DOC><ZAG></ZAG><SOD></SOD></DOC>');
    for Cur in (select * from asu_zag_dok where nz=in_nz and rownum<2) loop
      exit when (in_wid_dok is not null and Cur.Wid_Dok<>in_wid_dok);
      exit when (in_type is not null and instr(in_type,Cur.Type)=0);
      
      self.nz := in_nz;
      LoadZagDok();
      LoadSodDok();
      return;
    end loop;
  
    raise_application_error(-20001,'Документ не найден!');
    
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
  
  member procedure ParseXML(in_x XMLtype) is
    xx XMLtype;
    my_type varchar2(1 char);
  begin
    xx := in_x.extract('DOC/ZAG/ROW');
    for Cur in (select extractvalue( column_value, '/ROW/CEH_POST') ceh_post,
                       extractvalue( column_value, '/ROW/CEH_POTR') ceh_potr,
                       extractvalue( column_value, '/ROW/PRIM') prim,
                       extractvalue( column_value, '/ROW/OP') op
                from table(XMLsequence(xx))) loop

      self.rec_zag.op := Cur.op;
      self.rec_zag.ceh_post := Cur.ceh_post;
      self.rec_zag.ceh_potr := Cur.ceh_potr;
      self.rec_zag.post := to_char(Cur.ceh_post);
      self.rec_zag.potr := to_char(Cur.ceh_potr);
      self.rec_zag.prim := to_char(Cur.prim);
      null;
    end loop;

    xx := in_x.extract('DOC/SOD/ROW');
    for Cur in (select extractvalue( column_value, '/ROW/KOD_MAT') kod_mat,
                       extractvalue( column_value, '/ROW/KOL_TREB') kol_treb,
                       extractvalue( column_value, '/ROW/DOP_KOD') dop_kod,
                       extractvalue( column_value, '/ROW/SHPZ') shpz,
                       extractvalue( column_value, '/ROW/IZD') izd,
                       extractvalue( column_value, '/ROW/PRIM') prim,
                       extractvalue( column_value, '/ROW/DCE') dce,
                       extractvalue( column_value, '/ROW/D_GAR') d_gar,
                       extractvalue( column_value, '/ROW/NZ_PRIH') nz_prih,
                       extractvalue( column_value, '/ROW/NZ_CEH') nz_ceh
                from table(XMLsequence(xx))) loop

      self.rec_sod.newline(); 
      self.rec_sod.rec(self.rec_sod.last).kod_mat := Cur.kod_mat;
      self.rec_sod.rec(self.rec_sod.last).kol_treb := Cur.kol_treb;
      self.rec_sod.rec(self.rec_sod.last).dop_kod := Cur.dop_kod;
      self.rec_sod.rec(self.rec_sod.last).shpz := Cur.shpz;
      self.rec_sod.rec(self.rec_sod.last).izd := Cur.izd;
      self.rec_sod.rec(self.rec_sod.last).prim := Cur.prim;
      self.rec_sod.rec(self.rec_sod.last).dce := Cur.dce;
      self.rec_sod.rec(self.rec_sod.last).d_gar := to_date(Cur.d_gar,'dd.mm.yyyy');
      self.rec_sod.rec(self.rec_sod.last).nz_prih := Cur.nz_prih;
      self.rec_sod.rec(self.rec_sod.last).nz_ceh := Cur.nz_ceh;
      null;
    end loop;
  end;
  
  member procedure CreateDok(in_nz in out number, in_type varchar2, in_x XMLtype) is
    i number;
    nz number;
  begin
    self.rec_zag.clean();
    self.rec_zag.type := in_type;
    self.ParseXML(in_x);
    self.OnBeforeStoreDok();

    self.rec_zag.generate_id();
    self.StoreDok();
    null;
  end;
  
  member procedure OnBeforeStoreDok is
  begin
    lib.chk_nklad_exist(rec_zag.ceh_post, rec_zag.type);
    lib.chk_nklad_exist(rec_zag.ceh_potr, rec_zag.type);
    for I in 1..rec_sod.last loop
      lib.chk_Kod_mat_exist(rec_sod.rec(I).kod_mat, rec_zag.type);
    end loop;
  end;
  
  member procedure doNextStepDok(in_nz number, in_x XMLtype) is
  -- Проводка документа на следующую ступень
  begin
    raise_application_error(-20001, 'Метод doNextStepDok должен быть переопределён в производном классе!');
    null;
  end;

  member procedure doPrevStepDok(in_nz number, in_x XMLtype) is
  -- Возврат документа на предыдущую ступень
  begin
    raise_application_error(-20001, 'Метод doPrevStepDok должен быть переопределён в производном классе!');
    null;
  end;

/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
  
end;
/
