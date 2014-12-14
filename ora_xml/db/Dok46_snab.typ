create or replace force type Dok46_snab force under Dok46
(
  -- Author  : Администратор
  -- Created : 12.12.2014 22:46:43
  -- Purpose : 
  constructor function Dok46_snab return self as result,
  overriding member procedure Init,
  
  overriding member procedure OnBeforeStoreDok,
  overriding member procedure doNextStepDok(in_nz number, in_x XMLtype),
  overriding member procedure doPrevStepDok(in_nz number, in_x XMLtype),
  overriding member procedure OnBeforeEditDok(in_nz number)
  
  
  
)
/
create or replace type body Dok46_snab is
  
  -- Member procedures and functions
  constructor function Dok46_snab return self as result is
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

    for I in 1..rec_sod.rec.last loop
      lib.chk_not_null(rec_sod.rec(I).nz_prih, 'Номер карточки складского учёта');
      lib.chk_skl_kart_exists( rec_sod.rec(I).nz_prih, rec_zag.type, rec_sod.rec(I).kod_mat, rec_zag.ceh_post);
    end loop;
--    self.rec_zag.d_snab := sysdate;
    self.rec_zag.u_snab := user;
  end;
  
  
  overriding member procedure doNextStepDok(in_nz number, in_x XMLtype) is
  begin
    (self as Dok46).doNextStepDok(in_nz, in_x);

    if (rec_zag.d_skl_post is not null) then
      raise_application_error(-20001,'Документ уже прошёл через склад! ['||rec_zag.d_skl_post||']');
    end if;
    if (rec_zag.dd_ceh is null) then
      raise_application_error(-20001,'Документ не имеет подписи цеха!');
    end if;
    
    self.OnBeforeStoreDok();
    rec_zag.update_rec(in_d_snab=>sysdate, in_u_snab=>user);

    null;
  end;

  overriding member procedure doPrevStepDok(in_nz number, in_x XMLtype) is
  begin
    (self as Dok46).doPrevStepDok(in_nz, in_x);

    if (rec_zag.d_skl_post is not null) then
      raise_application_error(-20001,'Документ уже прошёл через склад! ['||rec_zag.d_skl_post||']');
    end if;
    if (rec_zag.d_snab is null) then
      raise_application_error(-20001,'Документ и так не имеет подписи снабжения!');
    end if;
    
    self.OnBeforeStoreDok();
    rec_zag.null_rec(in_d_snab=>null);

    null;
  end;

  overriding member procedure OnBeforeEditDok(in_nz number) is
  begin
    (self as Dok46).OnBeforeEditDok(in_nz);
    if (rec_zag.d_skl_post is not null) then
      raise_application_error(-20001,'Документ уже прошёл через склад! ['||rec_zag.d_skl_post||']');
    end if;
    if (rec_zag.dd_ceh is null) then
      raise_application_error(-20001,'Документ не имеет подписи цеха!');
    end if;
        
    null;
  end;

    
end;
/
