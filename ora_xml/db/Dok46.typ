create or replace force type Dok46 force under DokBase
(
  -- Author  : �������������
  -- Created : 03.12.2014 9:04:51
  -- Purpose : 
  constructor function Dok46 return self as result,
 

  overriding member procedure Init,
--  overriding member procedure doCommitOnSkl(in_x XMLtype),
  overriding member procedure OnBeforeEditDok(in_nz number),
  overriding member procedure EditDok(in_nz in out number, in_type varchar2, in_x XMLtype),
  overriding member procedure CreateDok(in_nz in out number, in_type varchar2, in_x XMLtype),
  overriding member procedure OnBeforeStoreDok,
  overriding member procedure doNextStepDok(in_nz number, in_x XMLtype),
  overriding member procedure doPrevStepDok(in_nz number, in_x XMLtype)

)
not final;
/
create or replace force type body Dok46 is
  
  -- Member procedures and functions

  constructor function Dok46 return self as result is
  begin
    Init();
    return;
  end;


  overriding member procedure Init is
  begin
    (self as DokBase).Init();
    null;
  end;
  
  

/*  overriding member procedure doCommitOnSkl(in_x XMLtype) is
  x_nz number;
  x_kol number;
  x_prizn asu_sod_dok.prizn%TYPE;
  skl_kol number;
  I number;
  tmp_x XMLtype := x;
  ost_from OstBase := OstBase(null,null);
  ost_to OstBase := OstBase(null,null);
  begin

    -- ��������� ����������� ����������� ��������� ����� ��������� ���������
    if self.GetDateCommitOnSkl() is not null then
        raise_application_error(-20001,'�������� ��� ������� �� ������ '||self.GetDateCommitOnSkl());
    end if;
    if self.GetDateCommitOnSnab() is null then
        raise_application_error(-20001,'�������� ��� �� ��������� ������������ ������ ���������');
    end if;
    
    -- ���������, ��� ��������� ������ ��� ����������
    I := 0;
    while true loop
        I := I+1;
        x_nz := tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ/text()').getstringval();
        exit when x_nz is null;
        x_kol := tmp_x.extract('/DOC/SOD/ROW['||I||']/KOL_TREB/text()').getstringval();
        x_prizn := tmp_x.extract('/DOC/SOD/ROW['||I||']/PRIZN/text()').getstringval();
        
        select max(extractvalue(column_value,'/ROW/KOL')) kol into skl_kol
                    from table(xmlsequence(in_x.extract('/SKL/ROW')))
                    where extractvalue(column_value,'/ROW/NZ')=x_nz;
        if skl_kol is null then
            raise_application_error(-20001,'�� ��� ������ � ���������� ����������� ������� (� ������ '||I||')' );
        end if;
        if skl_kol > x_kol then
            raise_application_error(-20001,'���������� ���������� ['||skl_kol||'] ������ �������������� ['||x_kol||'] (� ������ '||I||')');
        end if;
        self.doUpdateXMLvalue(tmp_x, '/DOC/SOD/ROW['||I||']/KOL', skl_kol);
        ost_from.OpenKart(tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ_PRIH/text()').getstringval(), '�');
        ost_to.OpenKart(tmp_x.extract('/DOC/SOD/ROW['||I||']/NZ_CEH/text()').getstringval(), '�');
        ost_from.AddKol( -skl_kol, x_prizn);
        ost_to.AddKol( skl_kol, x_prizn );
      null;
    end loop;
    self.doUpdateXMLvalue(tmp_x, '/DOC/ZAG/ROW/D_SKL_POST', sysdate);
    self.doUpdateXMLvalue(tmp_x, '/DOC/ZAG/ROW/U_SKL_POST', user);
--    update asu_zag_dok set d_skl_post=sysdate, u_skl_post=user where nz=self.nz;
    x := tmp_x;    
    null;
  end;
*/  
  overriding member procedure OnBeforeEditDok(in_nz number) is
  begin
    null;
  end;

 
  overriding member procedure EditDok(in_nz in out number, in_type varchar2, in_x XMLtype) is
  begin
    self.Opendok(in_nz, in_wid_dok=>46);
    OnBeforeEditDok(in_nz);
    self.DeleteDok(in_nz);
    self.CreateDok(in_nz, in_type, in_x);
    null; 
  end;  
  
  overriding member procedure CreateDok(in_nz in out number, in_type varchar2, in_x XMLtype) is
  begin
    (self as DokBase).CreateDok(in_nz, in_type, in_x);
    null;
  end;
  
  
  overriding member procedure OnBeforeStoreDok is
  -- �������� ������ ����� ������� ���������� (�������� 46)
  begin
    (self as DokBase).OnBeforeStoreDok;
    lib.chk_op_exist(rec_zag.op, 46);

    for I in 1..rec_sod.last loop
      rec_sod.rec(I).nz_ceh := null;
      lib.chk_not_null(rec_sod.rec(I).kol_treb, '����������');
    end loop;
  end;
  
  overriding member procedure doNextStepDok(in_nz number, in_x XMLtype) is
  begin
    self.OpenDok(in_nz, in_wid_dok=>46);
    null;
  end;
  
  overriding member procedure doPrevStepDok(in_nz number, in_x XMLtype) is
  begin
    self.OpenDok(in_nz, in_wid_dok=>46);
    null;
  end;
  
  
  
end;
/
