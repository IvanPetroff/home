create or replace force package test_dok46 is

  -- Author  : Администратор
  -- Created : 11.12.2014 10:36:25
  -- Purpose : 
  
procedure run;
procedure test1;


end test_dok46;
/
create or replace force package body test_dok46 is



procedure chk(b boolean) is
begin
  if b = true then
    dbms_output.put_line('OK');
  else
    dbms_output.put_line('failed! Test case '||debug_pkg.who_called_me(1) ); 
  end if;
  null;
end;

procedure test1 is
x m_Dok46;  
nz number := null;
begin
  x := m_Dok46;--(null,null,null,null,null);
  x.rec_zag := m_T_ZagDok(null);
  x.rec_sod := m_T_SodDok(null);
  x.createdok46(nz, 'М', XMLtype('<DOC><SOD><ROW><KOD_MAT>qwe</KOD_MAT><DOP_KOD>dop_kod</DOP_KOD><NZ_CEH>5678</NZ_CEH><NZ_PRIH>1234</NZ_PRIH><D_GAR>11.11.2014</D_GAR><DCE>dce</DCE><PRIM>prim</PRIM><SHPZ>shpz</SHPZ><IZD>izd</IZD><KOL_TREB>111</KOL_TREB></ROW><ROW><KOD_MAT>rty</KOD_MAT><KOL_TREB>222</KOL_TREB></ROW></SOD></DOC>'));
  chk(x.rec_sod.last = 2);
  chk(x.rec_sod.rec(1).kod_mat = 'qwe');
  chk(x.rec_sod.rec(1).kol_treb = '112');
  chk(x.rec_sod.rec(1).dop_kod = 'dop_kod');
  chk(x.rec_sod.rec(2).kod_mat = 'rty');
  chk(x.rec_sod.rec(2).kol_treb = '222');
  chk(x.rec_sod.rec(1).shpz = 'shpz');
  chk(x.rec_sod.rec(1).izd = 'izd');
  chk(x.rec_sod.rec(1).prim = 'prim');
  chk(x.rec_sod.rec(1).dce = 'dce');
  chk(x.rec_sod.rec(1).d_gar = to_date('11.11.2014'));
  chk(x.rec_sod.rec(1).nz_prih = 1234);
  chk(x.rec_sod.rec(1).nz_ceh = 5678);

  null;
end;

procedure test2 is
x m_Dok46;  
nz number := null;
begin
  x := m_Dok46;--(null,null,null,null,null);
  x.rec_zag := m_T_ZagDok(null);
  x.rec_sod := m_T_SodDok(null);
  x.createdok46(nz, 'М', XMLtype('<DOC><ZAG><ROW><PRIM>prim</PRIM><OP>33</OP><CEH_POST>11.11</CEH_POST><CEH_POTR>22.22</CEH_POTR></ROW></ZAG><SOD></SOD></DOC>'));
  chk(x.rec_zag.ceh_post = '11.11');
  chk(x.rec_zag.ceh_potr = '22.22');
  chk(x.rec_zag.post = 11.11);
  chk(x.rec_zag.potr = 22.22);
  chk(x.rec_zag.op = 33);
  chk(x.rec_zag.prim = 'prim');
  null;
end;


procedure test3 is
x m_Dok46;  
nz number := null;
begin
  x := m_Dok46;--(null,null,null,null,null);
  x.rec_zag := m_T_ZagDok(null);
  x.rec_sod := m_T_SodDok(null);
  x.DeleteDok(1234);
  null;
end;



/*
TODO: owner="Администратор" created="11.12.2014"
text="продумать API описания проверки вызовов перекрытых методов. с контролем передаваемых параметров"
*/

procedure run is
begin
  test1;
  test2;
  test3;
  null;
end;


begin
  -- Initialization
  null;
end test_dok46;
/
