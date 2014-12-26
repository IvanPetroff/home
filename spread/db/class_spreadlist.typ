create or replace force type class_spreadlist force as object
(
  -- Author  : Администратор
  -- Created : 23.12.2014 12:36:05
  -- Purpose : 
  id number,
  spis_count number,
  ceh number,
  
  
  -- Attributes
  constructor function class_spreadlist(in_id number:=null, in_d_beg date := null, in_d_end date := null) return self as result,
  member procedure ClearList,

  member procedure more_attr_set_num#(in_cat varchar2, in_name_attr varchar2, in_key number, in_val number),
  member procedure more_attr_set_txt#(in_name_attr varchar2, in_key number, in_val varchar2),
  member procedure more_attr_set_dat#(in_name_attr varchar2, in_key number, in_val date),
  member function get_ListID# return number,
  member procedure more_attr_set_prc_trud#( in_type varchar2, in_uch varchar2, in_ListID number, in_Unizak number, in_prc number),

  member function CreateList(self in out class_spreadlist, in_d_beg date, in_d_end date) return number,
  member procedure FixListNorma(in_ListID number),
  static function get_prc_trud#(in_type varchar2, in_ceh varchar2, in_d_beg date, in_d_end date) return xmltype,  
  static function load_prc_trud#(in_type varchar2, in_ListID number) return xmltype,
  member procedure store_prc_trud#( in_type varchar2, x xmltype)
  
  
  

  
)
not final;
/
create or replace type body class_spreadlist is
  
  -- Member procedures and functions
  constructor function class_spreadlist(in_id number:=null, in_d_beg date := null, in_d_end date := null) return self as result is
  begin
    if in_id is not null then
        select count(distinct s.id), max(substr(s.skl,1,instr(s.skl,'.')-1)) 
        into spis_count, ceh
        from asu_spis_dok s, asu_more_attr m 
        where s.id=m.key and m.val_num=in_id and m.cat='SPIS_DOK' and m.name_attr='SPREAD';
        id := in_id;
        return;
    end if;
    if in_d_beg is not null and in_d_end is not null then
        id := CreateList( in_d_beg, in_d_end);
        null;
        return;
    end if;
    raise_application_error(-20001, 'Не указаны обязательные параметры!');
    return;
  end;
  
  member procedure ClearList is
  begin
    if coalesce(get_env_var(user,'CEH'),get_env_var(user,'OTDEL'),'-')<>nvl(self.ceh,'!') then 
        raise_application_error(-20001,'Нет права удалять чужой объект'); 
    end if;
    update asu_more_attr set val_num=-1 where cat='SPIS_DOK' and name_attr='SPREAD' and val_num=self.id;
    delete asu_more_attr where cat in ('PRC_TR_N','PRC_TR_F') and key=self.id;
    id := null;
    null;
  end;
  

/*****************************************************************************************/
  member procedure more_attr_set_num#(in_cat varchar2, in_name_attr varchar2, in_key number, in_val number) is
  begin
    admdba.more_attr_pkg.SET_NUM( in_cat, in_name_attr, in_key, in_val);
  end;
  

/*****************************************************************************************/
  member procedure more_attr_set_txt#(in_name_attr varchar2, in_key number, in_val varchar2) is
  begin
    admdba.more_attr_pkg.SET_TXT( 'SPIS_DOK', in_name_attr, in_key, in_val);
  end;


/*****************************************************************************************/
  member procedure more_attr_set_dat#(in_name_attr varchar2, in_key number, in_val date) is
  begin
    admdba.more_attr_pkg.SET_DAT( 'SPIS_DOK', in_name_attr, in_key, in_val);
    null;
  end;
  

/*****************************************************************************************/
  member function get_ListID# return number is
  begin
    return asu_spis_dok_id_seq.nextval();
  end;
  

/*****************************************************************************************/
  member procedure more_attr_set_prc_trud#( in_type varchar2, in_uch varchar2, in_ListID number, in_Unizak number, in_prc number) is
  begin
    admdba.more_attr_pkg.SET_NUM( 
       in_cat        => 'PRC_TR'||'_'||in_type
      ,in_name_attr  => rpad(in_uch,5,' ')||';'||in_unizak
      ,in_key        => in_ListID
      ,in_val        => in_prc
    );
  end;
  
  static function get_prc_trud#(in_type varchar2, in_ceh varchar2, in_d_beg date, in_d_end date) return xmltype is
    x xmltype;
  begin
    select XMLtype(cursor(select dce0 uch, dce1 xxx, na_se unizak, na_izd prc from table( admdba.get_prc_trud_for_unz( in_ceh, in_d_beg, in_d_end, in_type||'R')))) into x from dual;
    return x;
  end;

  member procedure store_prc_trud#( in_type varchar2, x xmltype) is
  begin
      for Cur in (select 
                    extractvalue(column_value,'/ROW/UCH') uch
                    ,extractvalue(column_value,'/ROW/UNIZAK') unizak
                    ,extractvalue(column_value,'/ROW/PRC') prc
                  from table(xmlsequence(x.extract('/ROWSET/ROW')))
                 )
      loop
          more_attr_set_prc_trud#( in_type, Cur.uch, self.id, Cur.Unizak, Cur.Prc);
      end loop;

    null;
  end;

  static function load_prc_trud#(in_type varchar2, in_ListID number) return xmltype is
    x xmltype;
  begin
    select XMLtype(cursor(select 
                            trim(substr(m.name_attr, instr(m.name_attr,';')+1) ) unizak,
                            trim(substr(m.name_attr, 1, instr(m.name_attr,';')-1) ) uch,
                          m.val_num prc
                          from asu_more_attr m
                          where m.cat='PRC_TR'||'_'||in_type and m.key=in_ListID
                          )) 
    into x from dual;

    return x;
    null;
  end;

/*****************************************************************************************/
  member function CreateList(self in out class_spreadlist, in_d_beg date, in_d_end date) return number is
    ListDate date          := sysdate;
    flg_found_recs boolean := false;
  begin
    ceh := coalesce(get_env_var(user,'CEH'),get_env_var(user,'OTDEL'));
    -- перебираем все списания, удовлетворяющие критериям и помеченные как "к распределению"
    for Cur in (select s.id from asu_spis_dok s, asu_more_attr m 
      where s.id=m.key and m.cat='SPIS_DOK' and name_attr='SPREAD' and val_num=-1
      and s.d_ceh>=in_d_beg and s.d_ceh <= in_d_end and s.skl like self.ceh||'.%'
    ) loop
      if self.id is null then
        self.id := get_ListID#();
      end if;
      more_attr_set_num#('SPIS_DOK', 'SPREAD', Cur.id, self.id); -- запоминаем номер служебки
      self.more_attr_set_dat#('SPREAD', Cur.id, ListDate); -- запоминаем дату служебки
      flg_found_recs := true;
      null;
    end loop;
    if flg_found_recs=false then
      raise_application_error(-20001, 'Не найдено записей для формирования служебной записки!');
    end if;
    
    -- в море атрибутов запоминаем текущий список распределения трудоёмкости
    store_prc_trud#( 'N', class_spreadlist.get_prc_trud#('N', self.ceh, in_d_beg, in_d_end));
    store_prc_trud#( 'F', class_spreadlist.get_prc_trud#('F', self.ceh, in_d_beg, in_d_end));

    null;
    return self.id;
  end;
  
  member procedure FixListNorma(in_ListID number) is
  begin

    null;
  end;
  
  
end;
/
