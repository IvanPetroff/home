create or replace force type class_spreadlist force as object
(
  -- Author  : Администратор
  -- Created : 23.12.2014 12:36:05
  -- Purpose : 
  id number, -- регистрационный номер служебной записки
  spis_count number, -- число позиций списания включённых в служебную записку
  ceh number, -- номер цеха, сформировавший служебную записку
  
  
  -- Attributes
  constructor function class_spreadlist(in_id number := null) return self as result,
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
  member procedure store_prc_trud#( in_type varchar2, x xmltype),
  member function getSpreadList(x xmltype := null) return xmltype
  
  
  
  

  
)
not final;
/
create or replace type body class_spreadlist is
  
  -- Member procedures and functions
  constructor function class_spreadlist(in_id number := null) return self as result is
  tmp_ceh varchar2(8);
  begin
    if in_id is not null then
        select count(distinct s.id), max(s.skl)
        into spis_count, tmp_ceh
        from asu_spis_dok s, asu_more_attr m 
        where s.id=m.key and m.val_num=in_id and m.cat='SPIS_DOK' and m.name_attr='SPREAD';
        id := in_id;
        ceh := substr(tmp_ceh,1,instr(tmp_ceh,'.')-1);
        return;
    end if;
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
    self.id := null;
    -- перебираем все списания, удовлетворяющие критериям и помеченные как "к распределению"
    for Cur in (select s.id from asu_spis_dok s, asu_more_attr m 
      where s.id=m.key and m.cat='SPIS_DOK' and name_attr='SPREAD' and val_num=-1
      and s.d_ceh>=in_d_beg and s.d_ceh <= in_d_end and s.skl like self.ceh||'.%'
    ) 
    loop
        if self.id is null then
          self.id := get_ListID#();
        end if;
        more_attr_set_num#('SPIS_DOK', 'SPREAD', Cur.id, self.id); -- запоминаем номер служебки
        self.more_attr_set_dat#('SPREAD', Cur.id, ListDate); -- запоминаем дату служебки
        flg_found_recs := true;
    end loop;
    if flg_found_recs=false then
        raise_application_error(-20001, 'Не найдено записей для формирования служебной записки!');
    end if;
    
    -- в море атрибутов запоминаем текущий список распределения трудоёмкости
    store_prc_trud#( 'N', class_spreadlist.get_prc_trud#('N', self.ceh, in_d_beg, in_d_end));
    store_prc_trud#( 'F', class_spreadlist.get_prc_trud#('F', self.ceh, in_d_beg, in_d_end));

    return self.id;
  end;
  
  member procedure FixListNorma(in_ListID number) is
  begin

    null;
  end;
  
  member function getSpreadList(x xmltype := null) return xmltype is
    x_out xmltype;
    x_in xmltype;
  begin
    x_in := nvl( x, class_spreadlist.load_prc_trud#('F', self.id));
    select XMLtype(cursor(
                            select 
                              t.kod, 
                              (select naim from asu_slo_mt where m_kod=t.kod) naim,
                              t.r_sort, 
                              t.unizak, 
                              (select pzak from asu_zagzak where unizak=t.unizak) pzak, 
                              (select izd from asu_zagzak where unizak=t.unizak) izd, 
                              sum(t.kol) kol, 
                              sum(t.kol)*t.cena kol_cena
                            from (
                            select s.kod, s.r_sort, m2.unizak unizak, s.kol*s.kol_mat*m2.prc/100 kol, s.cena
                            from asu_more_attr m1, (select extractvalue(column_value,'/ROW/UCH') uch
                                  ,extractvalue(column_value,'/ROW/UNIZAK') unizak
                                  ,extractvalue(column_value,'/ROW/PRC') prc
                            from table(xmlsequence(x_in.extract('/ROWSET/ROW')))
                            ) m2, asu_spis_dok s
                            where s.id=m1.key
                            and m1.cat='SPIS_DOK' and m1.name_attr='SPREAD' and m1.val_num=self.id
                            and nvl(m1.val_txt,'-')=nvl(m2.uch,'-')
                            ) t
                            group by kod,unizak, cena, r_sort    
                         )
                   ) 
    into x_out from dual;
    return x_out;
  end;
  
end;
/
