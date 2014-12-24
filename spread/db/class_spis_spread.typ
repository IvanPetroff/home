create or replace force type class_spis_spread force under class_spis_dok
(
  -- Author  : Администратор
  -- Created : 21.12.2014 19:27:52
  -- Purpose : 
  tab_out tab_spis_dok,
  flg_spreadable varchar2(1),

  -- Attributes
  constructor function class_spis_spread(in_dok_id number) return self as result,
  overriding member procedure init(in_dok_id number),
  member function get_flg_spreadable#(in_dok_id number) return varchar2,
  
  member procedure spread(x xmltype),
  member procedure kol_correction,
  member procedure prepare_out_to_store,
  member procedure prepare_in_to_store,
  member procedure store_dok,
  member procedure more_attr_set_num#(in_key number, in_val number),
  member procedure more_attr_set_all#(in_key number, in_num number, in_txt varchar2, in_dat date),
  member procedure store_in_minus_recs#,
  member procedure store_out_spread_recs#,
  member procedure mark_to_spread(b number, uch varchar2)
  
  
  
  
  
  
  
  -- Member functions and procedures
)
not final;
/
create or replace type body class_spis_spread is
  
  -- Member procedures and functions
  constructor function class_spis_spread(in_dok_id number) return self as result is
  begin
    init(in_dok_id);
    return;
  end;
  
  
/*******************************************************************************************/  
  overriding member procedure init(in_dok_id number) is
  begin
    (self as class_spis_dok).init(in_dok_id);
    flg_spreadable := get_flg_spreadable#(in_dok_id);
  end;


/*******************************************************************************************/  
  member function get_flg_spreadable#(in_dok_id number) return varchar2 is
  begin
    for Cur in (select * from (select m.val_num 
                               from table(tab) t, asu_more_attr m 
                               where t.dok_id=in_dok_id and t.id=m.key(+) and 'SPIS_DOK'=m.cat(+) and 'SPREADABLE'=m.name_attr(+)) 
                         where nvl(val_num,0)<>-1
               )
    loop
      return '0'; -- документ имеет NONspreadable строки
    end loop;
    return '-1';
  end;

  /*
  TODO: owner="Администратор" created="21.12.2014"
  text="возможно нужно пересмотреть структуру классов. возможно нужно создать класс SPREAD
        который будет принимать на вход критерии документов, которые нужно обработать, искать эти документы в базе, открывать их и обрабатывать.
        возможно сам обрабатывать, а возможно используя class_spis_spread в качестве промежуточного звена
        
        главная цель - минимизировать операции обращения к базе и парсинга XML"
  */


/*******************************************************************************************/  
  member procedure mark_to_spread(b number, uch varchar2) is
  begin
    if nvl(b,0)<>1 then
      raise_application_error(-20001, '!');
    end if;
    
    for Cur in (select * from table(tab)) loop
      more_attr_SET_ALL#(in_key => Cur.id, in_num => -1, in_txt => uch, in_dat => null);
    end loop;
  end;


/*******************************************************************************************/  
  member procedure spread(x xmltype) is
  begin
    if flg_spreadable<>'-1' then
      raise_application_error(-20001, 'документ не может быть spreadable!');
    end if;
    
    for Cur_xml in (
      select extractvalue( column_value, '/ROW/SHPZ') shpz,
             extractvalue( column_value, '/ROW/IZD') izd,
             extractvalue( column_value, '/ROW/PRC') prc
      from table(XMLsequence( x.extract('ROWSET/ROW')))
    )
    loop
        for Cur in (select rec_spis_dok(id,spk_id,kol,kol_mat,ost_id,shpz,izd,bs,prizn,usr,dat,
           dok_id,d_ceh,u_ceh,d_buh,u_buh,skl,type,kod,r_sort,cena,lim_id,
           dop_dok,r_zag,prc_nds,cntrl,t_id,kol_part,prih_id,razm_zag,fakt_rash,d_drag,dok_drag ) x from table(tab)) loop
            tab_out.extend(1);
            tab_out(tab_out.last) := Cur.x;
            tab_out(tab_out.last).dok_id := tab_out.last; -- временно запоминаем порядковый номер строки в массиве (нужно для метода kol_correction)
            tab_out(tab_out.last).kol_mat := tab_out(tab_out.last).kol_mat * Cur_xml.prc;
            tab_out(tab_out.last).kol_mat := tab_out(tab_out.last).kol_mat * Cur_xml.prc;
            tab_out(tab_out.last).shpz := Cur.x.shpz;
            tab_out(tab_out.last).izd := Cur.x.izd;
            tab_out(tab_out.last).t_id := 'З';
            null;
        end loop;
      null;
    end loop;
    flg_spreadable := '0';
    kol_correction();
    store_dok();
    null;
  end;
  

/*******************************************************************************************/  
  member procedure kol_correction is
  delta number;
  begin
    for Cur in (select kol_mat, id from table(tab)) loop
      for Cur_out in (select sum(kol_mat) sum_kol, max(dok_id) keep(dense_rank first order by kol desc) max_id from table(tab_out) where id=Cur.id) loop
        delta := Cur.kol_mat - Cur_out.sum_kol;
        if delta<>0 then
          tab_out(Cur_out.max_id).kol_mat := tab_out(Cur_out.max_id).kol_mat + delta;
        end if;
        null;
      end loop;
      
      null;
    end loop;
    null;
  end;
  

/*******************************************************************************************/  
  member procedure prepare_out_to_store is
  begin
    for i in 1..tab_out.last loop
      tab_out(i).id := null;
      tab_out(i).dok_id := dok_id;
    end loop;
    null;
  end;
  

/*******************************************************************************************/  
  member procedure more_attr_set_num#(in_key number, in_val number) is
  begin
    admdba.more_attr_pkg.SET_NUM( 'SPIS_DOK', 'SPREAD', in_key, in_val);
  end;


/*******************************************************************************************/  
  member procedure more_attr_set_all#(in_key number, in_num number, in_txt varchar2, in_dat date) is
  begin
    admdba.more_attr_pkg.SET_ALL(in_cat=>'SPIS_DOK', in_name_attr => 'SPREAD', in_key => in_key, in_num => in_num, in_txt => in_txt, in_dat => in_dat);
  end;


/*******************************************************************************************/  
  member procedure prepare_in_to_store is
  begin
    for i in 1..tab.last loop
      more_attr_SET_NUM#( tab(i).id, 2);
      tab(i).id := null;
      tab(i).kol_mat := -tab(i).kol_mat;
    end loop;
    null;
  end;


/*******************************************************************************************/  
  member procedure store_dok is
  begin
    prepare_out_to_store();
    prepare_in_to_store();

    store_in_minus_recs#();
    store_out_spread_recs#();
  end;


/*******************************************************************************************/  
  member procedure store_in_minus_recs# is
  begin
    insert into asu_spis_dok(select * from table(tab)); -- добавляем в документ оригинальные строки с минусом
  end;


/*******************************************************************************************/  
  member procedure store_out_spread_recs# is
  begin
    insert into asu_spis_dok(select * from table(tab_out));
  end;


/*******************************************************************************************/  
  

end;
/
