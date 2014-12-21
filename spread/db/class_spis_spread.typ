create or replace force type class_spis_spread under class_spis_dok
(
  -- Author  : Администратор
  -- Created : 21.12.2014 19:27:52
  -- Purpose : 
  tab_out tab_foo,
  flg_spreadable varchar2(1),

  -- Attributes
  constructor function class_spis_spread(in_id number) return self as result,
  overriding member procedure init(in_id number),
  member procedure spread(x xmltype),
  member procedure kol_correction,
  member procedure store_dok
  
  
  
  
  -- Member functions and procedures
)
not final;
/
create or replace type body class_spis_spread is
  
  -- Member procedures and functions
  constructor function class_spis_spread(in_id number) return self as result is
  begin
    init(in_id);
    null;
  end;
  
  overriding member procedure init(in_id number) is
  begin
    (self as class_spis_dok).init(in_id);
    flg_spreadable := '1';
    for Cur in (select * from (select m.id from table(tab) t, more_attr m where t.id=m.key(+) and 'SPIS'=m.cat(+) and 'SPREAD'=m.prizn(+)) where id is null) loop
      flg_spreadable := '0';      
      null;
    end loop;
    
  end;
  /*
  TODO: owner="Администратор" created="21.12.2014"
  text="возможно нужно пересмотреть структуру классов. возможно нужно создать класс SPREAD
        который будет принимать на вход критерии документов, которые нужно обработать, искать эти документы в базе, открывать их и обрабатывать.
        возможно сам обрабатывать, а возможно используя class_spis_spread в качестве промежуточного звена
        
        главная цель - минимизировать операции обращения к базе и парсинга XML"
  */

  member procedure spread(x xmltype) is
  begin
    if flg_spreadable<>'1' then
      raise_application_error(-20001, 'документ не может быть spreadable!');
    end if;
    
    for Cur_xml in (
      select extractvalue( column_value, '/ROW/UNIZAK') unizak,
             extractvalue( column_value, '/ROW/PRC') prc
      from table(XMLsequence( x.extract('DOC/ROW')))
    )
    loop
        for Cur in (select rec_foo( id, dok_id, kol, kol_treb, d_ceh, u_ceh, d_buh, u_buh, ost_id, type) x from table(tab)) loop
            tab_out.extend(1);
            tab_out(tab_out.last) := Cur.x;
            tab_out(tab_out.last).id := tab_out.last;
            tab_out(tab_out.last).dok_id := Cur.x.id;
            tab_out(tab_out.last).kol := tab_out(tab_out.last).kol * Cur_xml.prc;
            tab_out(tab_out.last).kol := tab_out(tab_out.last).kol * Cur_xml.prc;
            null;
        end loop;
      null;
    end loop;
    kol_correction();
    store_dok();
    null;
  end;
  
  member procedure kol_correction is
  delta number;
  begin
    for Cur in (select kol, ost_id from table(tab)) loop
      for Cur_out in (select sum(kol) sum_kol, max(id) keep(dense_rank first order by kol desc) max_id from table(tab_out) where ost_id=Cur.ost_id) loop
        delta := Cur.kol - Cur_out.sum_kol;
        if delta<>0 then
          tab_out(Cur_out.max_id).kol := tab_out(Cur_out.max_id).kol + delta;
        end if;
        null;
      end loop;
      
      null;
    end loop;
    null;
  end;
  
  member procedure store_dok is
  begin
    
    
    null;
  end;
  

end;
/
