create or replace type tab_spis_dok force as table of rec_spis_dok
/
create or replace type body tab_spis_dok is
  
  -- Member procedures and functions
  member procedure <ProcedureName>(<Parameter> <Datatype>) is
  begin
    <Statements>;
  end;
  
end;
/
