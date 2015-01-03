create or replace trigger spr_question_trg
  before insert or update on spr_question
  for each row
begin
  :new.usr := user;
  :new.dat := sysdate;
  if :new.id is null then
      :new.id := id_seq.nextval;
  end if;
  
  
end spr_question_trg;
/
