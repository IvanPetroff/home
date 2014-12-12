create or replace type m_T_ZagDok force under T_ZagDok
(
  -- Author  : Администратор
  -- Created : 11.12.2014 10:40:44
  -- Purpose : 
  
  constructor function m_T_ZagDok(in_nz number) return self as result,    
  overriding member procedure Store,
  overriding member procedure update_rec(    
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
    in_potr number := null,
    in_prim varchar2 := null
    ),

  overriding member procedure null_rec(
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
    in_potr number := 1,
    in_prim number := 1
    )
  
)
/
create or replace type body m_T_ZagDok is
  
  -- Member procedures and functions
  constructor function m_T_ZagDok(in_nz number) return self as result is
  begin
    if in_nz is null then
      self.clean();
      return;
    end if;
  end;


  overriding member procedure Store is
  begin
    null;
  end;
  
  overriding member procedure update_rec(
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
    in_potr number := null,
    in_prim varchar2 := null
    ) is
  begin
    null;
  end;

  overriding member procedure null_rec(
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
    in_potr number := 1,
    in_prim number := 1
    ) is
  begin
    null;
  end;
  
  
  
end;
/
