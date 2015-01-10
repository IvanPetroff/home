create or replace procedure person_upd(in_id number, x xmltype) is
begin
  for Cur in (select extractvalue(t.column_value,'/ROW/FIO') FIO,
                     extractvalue(t.column_value,'/ROW/SEX') SEX,
                     extractvalue(t.column_value,'/ROW/D_BIRTH') D_BIRTH,
                     extractvalue(t.column_value,'/ROW/ADDR') ADDR,
                     extractvalue(t.column_value,'/ROW/TEL') TEL,
                     extractvalue(t.column_value,'/ROW/EMAIL') EMAIL
              from table(XMLsequence(x.extract('/ROWSET/ROW'))) t) 
  loop
      update syn_person set fio=Cur.fio, sex=Cur.sex, d_birth=to_date(Cur.d_birth,'dd.mm.yyyy'), addr=Cur.addr, tel=Cur.tel, email=Cur.email
      where id=in_id;
      null;
  end loop;
  null;
  
end person_upd;
/
