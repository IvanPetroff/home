create or replace force type Dok46_ceh force under Dok46
(
  -- Author  : �������������
  -- Created : 12.12.2014 22:46:43
  -- Purpose : 
  constructor function Dok46_ceh return self as result,
  overriding member procedure Init,
  
  overriding member procedure OnBeforeStoreDok,
  overriding member procedure doNextStepDok(in_nz number, in_x XMLtype),
  overriding member procedure doPrevStepDok(in_nz number, in_x XMLtype)
  
  
)
/
create or replace type body Dok46_ceh is
  
  -- Member procedures and functions
  constructor function Dok46_ceh return self as result is
  begin
    Init();
    return;
  end;


  overriding member procedure Init is
  begin
    (self as Dok46).Init();
    null;
  end;
  
  
  overriding member procedure OnBeforeStoreDok is
  begin
    (self as Dok46).OnBeforeStoreDok;
  end;
  
  
  overriding member procedure doNextStepDok(in_nz number, in_x XMLtype) is
  begin
    if get_env_var(user,'SIGNATURE_CEH') is null then
      raise_application_error(-20001, '��� ����� ������� ���������!');
    end if;
    
    (self as Dok46).doNextStepDok(in_nz, in_x);

    if (rec_zag.d_snab is not null) then
      raise_application_error(-20001,'�������� ��� ������ ����� ���������! ['||rec_zag.d_snab||']');
    end if;
    
    self.OnBeforeStoreDok();
    rec_zag.update_rec(in_dd_ceh=>sysdate, in_uu_ceh=>user);

    null;
  end;

  overriding member procedure doPrevStepDok(in_nz number, in_x XMLtype) is
  begin
    if get_env_var(user,'SIGNATURE_CEH') is null then
      raise_application_error(-20001, '��� ����� ������� ���������!');
    end if;

    (self as Dok46).doPrevStepDok(in_nz, in_x);

    if (rec_zag.d_snab is not null) then
      raise_application_error(-20001,'�������� ��� ������ ����� ���������! ['||rec_zag.d_snab||']');
    end if;
    if (rec_zag.dd_ceh is null) then
      raise_application_error(-20001,'�������� � ��� �� ����� �������!');
    end if;
    
    self.OnBeforeStoreDok();
    rec_zag.null_rec(in_dd_ceh=>null);

    null;
  end;
    
end;
/
