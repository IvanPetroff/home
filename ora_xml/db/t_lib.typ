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
  member procedure chk_op_exist(in_op number, in_wid_dok number),
  member procedure chk_skl_kart_exists( in_ost_id number, in_type varchar2, in_m_kod varchar2, in_skl varchar2),
  member procedure chk_not_null(x varchar2, str1 varchar2 := null, str2 varchar2 := null, str3 varchar2 := null),
  member function get_env_var(in_usr varchar2, in_var_name varchar2) return varchar2
  
  
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
  
  member procedure chk_skl_kart_exists( in_ost_id number, in_type varchar2, in_m_kod varchar2, in_skl varchar2) is
  cnt number;
  begin
    for Cur in (select * from asu_ost_mat where id=in_ost_id and type=in_type) loop
      if in_m_kod is not null and Cur.m_kod<>in_m_kod then
        raise_application_error(-20001,'Неправильный код ['||in_m_kod||'] для карточки ['||in_ost_id||']');
      end if;      
      if in_skl is not null and Cur.skl<>in_skl then
        raise_application_error(-20001,'Неправильный склад ['||in_m_kod||'] для карточки ['||in_ost_id||']');
      end if;      
      return;
    end loop;
    raise_application_error(-20001,'Неправильный номер складской карточки ['||in_ost_id||']');
  end;
  
  member procedure chk_not_null(x varchar2, str1 varchar2 := null, str2 varchar2 := null, str3 varchar2 := null) is
  begin
    if x is null then
      raise_application_error(-20001,nvl(str1,' ')||' '||nvl(str2,' ')||' '||nvl(str3,' ')||' не может быть пустым!');
    end if;
    null;
  end;  
  
  member function get_env_var(in_usr varchar2, in_var_name varchar2) return varchar2 is
  begin
    return null;
  end;
  
  
end;
/
