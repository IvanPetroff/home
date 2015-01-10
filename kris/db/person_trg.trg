create or replace trigger person_trg
  before insert or update on person
  for each row
begin
  :new.usr := user;
  :new.dat := sysdate;
  if INSERTING then
      :new.d_reg := sysdate;
      :new.u_reg := user;
  end if;
  if :new.id is null then
      :new.id := id_seq.nextval;
  end if;
  :new.sex := upper(:new.sex);
  if :new.sex not in ('М','Ж') then
      raise_application_error(-20001, 'Неправильный идентификатор пола пациента! ['||:new.sex||']');
  end if;


end person_trg;
/
