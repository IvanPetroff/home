create or replace force type class_spreadlist force as object
(
  -- Author  : Администратор
  -- Created : 23.12.2014 12:36:05
  -- Purpose : 
  id number,
  
  
  -- Attributes
  constructor function class_spreadlist return self as result,
  member procedure more_attr_set_num#(in_name_attr varchar2, in_key number, in_val number),
  member procedure more_attr_set_txt#(in_name_attr varchar2, in_key number, in_val varchar2),
  member procedure more_attr_set_dat#(in_name_attr varchar2, in_key number, in_val date),
  member function get_ListID# return number,
  member procedure more_attr_set_prc_trud#( in_uch varchar2, in_ListID number, in_Unizak number, in_prc number),

  member function CreateList(self in out class_spreadlist, in_ceh varchar2, in_d_beg date, in_d_end date) return number,
  member procedure FixListNorma(in_ListID number)

  
)
not final;
/
create or replace type body class_spreadlist is
  
  -- Member procedures and functions
  constructor function class_spreadlist return self as result is
  begin
    return;
  end;
  

/*****************************************************************************************/
  member procedure more_attr_set_num#(in_name_attr varchar2, in_key number, in_val number) is
  begin
    admdba.more_attr_pkg.SET_NUM( 'SPIS_DOK', in_name_attr, in_key, in_val);
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
  member procedure more_attr_set_prc_trud#( in_uch varchar2, in_ListID number, in_Unizak number, in_prc number) is
  begin
    admdba.more_attr_pkg.SET_NUM( in_cat => 'PRC_TRUD', in_name_attr => rpad(in_uch,5,' ')||';'||in_unizak, in_key => in_ListID, in_val => in_prc);
  end;


/*****************************************************************************************/
  member function CreateList(self in out class_spreadlist, in_ceh varchar2, in_d_beg date, in_d_end date) return number is
    ListDate date          := sysdate;
    ListID number          := null;
    flg_found_recs boolean := false;
  begin
    for Cur in (select s.id from asu_spis_dok s, asu_more_attr m 
      where s.id=m.key and m.cat='SPIS_DOK' and name_attr='SPREAD' and val_num=-1
      and s.d_ceh>=in_d_beg and s.d_ceh <= in_d_end and s.skl like in_ceh||'.%'
    ) loop
      if ListID is null then
        ListID := get_ListID#();
      end if;
      more_attr_set_num#('SPREAD', Cur.id, ListID); -- запоминаем номер служебки
      self.more_attr_set_dat#('SPREAD', Cur.id, ListDate); -- запоминаем дату служебки
      flg_found_recs := true;
      null;
    end loop;
    if flg_found_recs=false then
      raise_application_error(-20001, 'Не найдено записей для формирования служебной записки!');
    end if;
    
    -- в море атрибутов запоминаем текущий список распределения трудоёмкости
    for Cur in (select dce0 uch, dce1 xxx, na_se unizak, na_izd prc from table( admdba.get_prc_trud_for_unz( in_ceh, in_d_beg, in_d_end, 'NR'))) loop
      more_attr_set_prc_trud#( Cur.uch, ListID, Cur.Unizak, Cur.Prc);
    end loop;
    
    null;
    return ListID;
  end;
  
  member procedure FixListNorma(in_ListID number) is
  begin

    null;
  end;
  
end;
/
