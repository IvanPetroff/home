create or replace type t_lib force as object
(
  -- Author  : Администратор
  -- Created : 12.12.2014 10:48:13
  -- Purpose : 
  
  -- Attributes
  tmp number,
  constructor function t_lib return self as result,
 
  -- Member functions and procedures
  member procedure chk_Kod_mat_exist(in_kod_mat varchar2, in_type varchar2),
  member procedure chk_nklad_exist(in_nklad varchar2, in_type varchar2),
  member procedure chk_op_exist(in_op number, in_wid_dok number)
)
not final;
/
create or replace type body t_lib is

  constructor function t_lib return self as result is
  begin
    return;
  end;

  
  -- Member procedures and functions
  member procedure chk_Kod_mat_exist(in_kod_mat varchar2, in_type varchar2) is
  cnt number := 0;
  begin
    if in_type is null then
      raise_application_error(-20001,'Не указан тип для проверки кода!');
    end if;
    if (in_type = 'М') then
        select count(1) into cnt from asu_slo_mt where m_kod=in_kod_mat and rownum<2;
    end if;
    if (in_type = 'П') then
        select count(1) into cnt from asu_slo_pk where dce0=in_kod_mat and rownum<2;
    end if;
    if (in_type = 'И') then
        select count(1) into cnt from asu_slo_ins where i_kod=in_kod_mat and rownum<2;
    end if;
    if cnt=0 then
      raise_application_error(-20001,'Неправильный код ['||in_kod_mat||']');
    end if;
    null;
  end;
  
  member procedure chk_nklad_exist(in_nklad varchar2, in_type varchar2) is
  cnt number;
  begin
    select count(1) into cnt from asu_n_klad t where instr(t.user_type,in_type)>0 and t.n_klad=in_nklad and rownum<2;
    if cnt=0 then
      raise_application_error(-20001,'Неправильный номер склада/кладовой ['||in_nklad||']');
    end if;
    null;
  end;
  
  member procedure chk_op_exist(in_op number, in_wid_dok number) is
  cnt number;
  begin
    select count(1) into cnt from asu_spr_op t where t.wid_dok=in_wid_dok and t.op=in_op and rownum<2;
    if cnt=0 then
      raise_application_error(-20001,'Неправильный код операции ['||in_op||']');
    end if;
    null;
  end;
  
  
end;
/
