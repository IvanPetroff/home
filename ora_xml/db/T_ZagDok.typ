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
  op number,
  post number,
  potr number,
  
  constructor function T_ZagDok(in_nz number) return self as result,

  member procedure update_rec(
    in_d_snab date := null,
    in_d_skl_post date  := null,
    in_d_skl_potr date := null,
    in_dd_ceh date := null,
    in_u_snab varchar2 := null,
    in_u_skl_post varchar2 := null,
    in_u_skl_potr varchar2 := null,
    in_uu_ceh varchar2 := null,
    in_op number := null,
    in_wid_dok number := null,
    in_post number := null,
    in_potr number := null
    ),

  member procedure null_rec(
    in_d_snab number := 1,
    in_d_skl_post number := 1,
    in_d_skl_potr number := 1,
    in_dd_ceh number := 1,
    in_u_snab number := 1,
    in_u_skl_post number := 1,
    in_u_skl_potr number := 1,
    in_uu_ceh number := 1,
    in_op number := 1,
    in_wid_dok number := 1,
    in_post number := 1,
    in_potr number := 1
    ),
    
  member procedure clean,
  member procedure generate_id,
  member procedure Store
  

  
  
  -- Member functions and procedures
)
not final;
/
create or replace type body T_ZagDok is
  
  -- Member procedures and functions
  constructor function T_ZagDok(in_nz number) return self as result is
  begin
    if in_nz is null then
      self.clean();
      return;
    end if;
    select nz, wid_dok, type, ceh_post, ceh_potr, d_snab, d_skl_post, d_skl_potr, dd_ceh, u_snab, u_skl_post, u_skl_potr, uu_ceh, op, wid_dok, post, potr
      into nz, wid_dok, type, ceh_post, ceh_potr, d_snab, d_skl_post, d_skl_potr, dd_ceh, u_snab, u_skl_post, u_skl_potr, uu_ceh, op, wid_dok, post, potr
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
    in_uu_ceh varchar2 := null,
    in_op number := null,
    in_wid_dok number := null,
    in_post number := null,
    in_potr number := null
    ) is
  begin
    update zag_dok set 
      d_snab     =nvl(in_d_snab,d_snab),
      d_skl_post =nvl(in_d_skl_post,d_skl_post),
      d_skl_potr =nvl(in_d_skl_potr,d_skl_potr),
      dd_ceh     =nvl(in_dd_ceh,dd_ceh),
      u_snab     =nvl(in_u_snab,u_snab),
      u_skl_post =nvl(in_u_skl_post,u_skl_post),
      u_skl_potr =nvl(in_u_skl_potr,u_skl_potr),
      uu_ceh     =nvl(in_uu_ceh,uu_ceh),
      op         =nvl(in_op, op),
      wid_dok    =nvl(in_wid_dok, wid_dok),
      post       =nvl(in_post, post),
      potr       =nvl(in_potr, potr)
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
    in_uu_ceh number := 1,
    in_op number := 1,
    in_wid_dok number := 1,
    in_post number := 1,
    in_potr number := 1
    ) is
  begin
    update zag_dok set 
      d_snab     =decode(in_d_snab,     null,null, d_snab),
      d_skl_post =decode(in_d_skl_post, null,null, d_skl_post),
      d_skl_potr =decode(in_d_skl_potr, null,null, d_skl_potr),
      dd_ceh     =decode(in_dd_ceh,     null,null, dd_ceh),
      u_snab     =decode(in_u_snab,     null,null, u_snab),
      u_skl_post =decode(in_u_skl_post, null,null, u_skl_post),
      u_skl_potr =decode(in_u_skl_potr, null,null, u_skl_potr),
      uu_ceh     =decode(in_uu_ceh,     null,null, uu_ceh),
      op         =decode(in_op,         null,null, op),
      wid_dok    =decode(in_wid_dok,    null,null, wid_dok),
      post       =decode(in_post,       null,null, post),
      potr       =decode(in_potr,       null,null, potr)
    where 
      nz=self.nz
    returning   nz, wid_dok, type, ceh_post, ceh_potr, d_snab, d_skl_post, d_skl_potr, dd_ceh, u_snab, u_skl_post, u_skl_potr, uu_ceh, op, post, potr
           into nz, wid_dok, type, ceh_post, ceh_potr, d_snab, d_skl_post, d_skl_potr, dd_ceh, u_snab, u_skl_post, u_skl_potr, uu_ceh, op, post, potr;
    null;
  end;
  
  member procedure clean is
  begin
    nz         := null; 
    wid_dok    := null;
    type       := null;
    ceh_post   := null;
    ceh_potr   := null;
    d_snab     := null;
    d_skl_post := null;
    d_skl_potr := null;
    dd_ceh     := null;
    u_snab     := null;
    u_skl_post := null;
    u_skl_potr := null;
    uu_ceh     := null;
    op         := null;
    post       := null;
    potr       := null;
  end;
  
  member procedure generate_id is
  begin
    null;
  end;

  member procedure Store is
  begin
    null;
  end;
  
end;
/
