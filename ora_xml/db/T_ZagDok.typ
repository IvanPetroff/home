create or replace type T_ZagDok force as object
(
  -- Author  : Администратор
  -- Created : 09.12.2014 8:35:46
  -- Purpose : 
  
  -- Attributes
  nz number,
  wid_dok number,
  type varchar2(1),
  ceh_post varchar2(8),
  ceh_potr varchar2(8),
  d_snab date,
  d_skl_post date,
  d_skl_potr date,
  dd_ceh date,
  u_snab varchar2(16),
  u_skl_post varchar2(16),
  u_skl_potr varchar2(16),
  uu_ceh varchar2(16),
  
  constructor function T_ZagDok(in_nz number) return self as result,

  member procedure update_rec(
    in_d_snab date := null,
    in_d_skl_post date  := null,
    in_d_skl_potr date := null,
    in_dd_ceh date := null,
    in_u_snab varchar2 := null,
    in_u_skl_post varchar2 := null,
    in_u_skl_potr varchar2 := null,
    in_uu_ceh varchar2 := null),

  member procedure null_rec(
    in_d_snab number := 1,
    in_d_skl_post number := 1,
    in_d_skl_potr number := 1,
    in_dd_ceh number := 1,
    in_u_snab number := 1,
    in_u_skl_post number := 1,
    in_u_skl_potr number := 1,
    in_uu_ceh number := 1)

  
  
  -- Member functions and procedures
)
/
create or replace type body T_ZagDok is
  
  -- Member procedures and functions
  constructor function T_ZagDok(in_nz number) return self as result is
  begin
    select nz,wid_dok,type,ceh_post,ceh_potr,d_snab,d_skl_post,d_skl_potr,dd_ceh,u_snab,u_skl_post,u_skl_potr,uu_ceh
    into nz,wid_dok,type,ceh_post,ceh_potr,d_snab,d_skl_post,d_skl_potr,dd_ceh,u_snab,u_skl_post,u_skl_potr,uu_ceh
    from asu_zag_dok where nz = in_nz;
  end;
  
  member procedure update_rec(
    in_d_snab date := null,
    in_d_skl_post date  := null,
    in_d_skl_potr date := null,
    in_dd_ceh date := null,
    in_u_snab varchar2 := null,
    in_u_skl_post varchar2 := null,
    in_u_skl_potr varchar2 := null,
    in_uu_ceh varchar2 := null) is
  begin
    update zag_dok set 
      d_snab     =nvl(in_d_snab,d_snab),
      d_skl_post =nvl(in_d_skl_post,d_skl_post),
      d_skl_potr =nvl(in_d_skl_potr,d_skl_potr),
      dd_ceh     =nvl(in_dd_ceh,dd_ceh),
      u_snab     =nvl(in_u_snab,u_snab),
      u_skl_post =nvl(in_u_skl_post,u_skl_post),
      u_skl_potr =nvl(in_u_skl_potr,u_skl_potr),
      uu_ceh     =nvl(in_uu_ceh,uu_ceh)
    where 
      nz=self.nz;
    null;
  end;

  member procedure null_rec(
    in_d_snab number := 1,
    in_d_skl_post number := 1,
    in_d_skl_potr number := 1,
    in_dd_ceh number := 1,
    in_u_snab number := 1,
    in_u_skl_post number := 1,
    in_u_skl_potr number := 1,
    in_uu_ceh number := 1) is
  begin
    update zag_dok set 
      d_snab     =decode(in_d_snab,null,null,d_snab),
      d_skl_post =decode(in_d_skl_post,null,null,d_skl_post),
      d_skl_potr =decode(in_d_skl_potr,null,null,d_skl_potr),
      dd_ceh     =decode(in_dd_ceh,null,null,dd_ceh),
      u_snab     =decode(in_u_snab,null,null,u_snab),
      u_skl_post =decode(in_u_skl_post,null,null,u_skl_post),
      u_skl_potr =decode(in_u_skl_potr,null,null,u_skl_potr),
      uu_ceh     =decode(in_uu_ceh,null,null,uu_ceh)
    where 
      nz=self.nz
    returning   nz,wid_dok,type,ceh_post,ceh_potr,d_snab,d_skl_post,d_skl_potr,dd_ceh,u_snab,u_skl_post,u_skl_potr,uu_ceh
    into nz,wid_dok,type,ceh_post,ceh_potr,d_snab,d_skl_post,d_skl_potr,dd_ceh,u_snab,u_skl_post,u_skl_potr,uu_ceh;
    null;
  end;
  
  
end;
/
