create or replace force type class_spis_dok force as object
(
  -- Author  : Администратор
  -- Created : 21.12.2014 19:27:52
  -- Purpose : 
  dok_id number,
  rec rec_spis_dok,
  tab tab_spis_dok,
  
  -- Attributes
  constructor function class_spis_dok(in_dok_id number) return self as result,
  member procedure init(in_dok_id number),
  member procedure load_dok#(in_dok_id number)
  
  
  -- Member functions and procedures
)
not final;
/
create or replace type body class_spis_dok is
  
  -- Member procedures and functions
  constructor function class_spis_dok(in_dok_id number) return self as result is
  begin
    dok_id := in_dok_id;
    init(in_dok_id);
    return;
  end;
  
  
  member procedure init(in_dok_id number) is
  begin
    load_dok#(in_dok_id);
    null;
  end;


  member procedure load_dok#(in_dok_id number) is
  begin
    select rec_spis_dok(id,spk_id,kol,kol_mat,ost_id,shpz,izd,bs,prizn,usr,dat,
           dok_id,d_ceh,u_ceh,d_buh,u_buh,skl,type,kod,r_sort,cena,lim_id,
           dop_dok,r_zag,prc_nds,cntrl,t_id,kol_part,prih_id,razm_zag,fakt_rash,d_drag,dok_drag ) 
      bulk collect into tab 
      from asu_spis_dok 
      where dok_id=in_dok_id;    
  end;

  
end;
/
