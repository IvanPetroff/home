create or replace package test_dok46 is

  -- Author  : Администратор
  -- Created : 11.12.2014 10:36:25
  -- Purpose : 
  
procedure run;
procedure test1;


end test_dok46;
/
create or replace package body test_dok46 is


procedure who_called_me( steps_to_back  number,
                         owner      out varchar2,
                         name       out varchar2,
                         lineno     out number,
                         caller_t   out varchar2 )
as
   call_stack  varchar2(4096) default dbms_utility.format_call_stack;
   n           number;
   found_stack BOOLEAN default FALSE;
   line        varchar2(255);
   cnt         number := 0;
-- http://tkyte.blogspot.ru/2009/10/httpasktomoraclecomtkytewhocalledme.html   
begin
--
   loop
       n := instr( call_stack, chr(10) );
       exit when ( cnt = (2+steps_to_back) or n is NULL or n = 0 );
--
       line := substr( call_stack, 1, n-1 );
       call_stack := substr( call_stack, n+1 );
--
       if ( NOT found_stack ) then
           if ( line like '%handle%number%name%' ) then
               found_stack := TRUE;
           end if;
       else
           cnt := cnt + 1;
           -- cnt = 1 is ME
           -- cnt = 2 is MY Caller
           -- cnt = 3 is Their Caller
           if ( cnt = (2+steps_to_back) ) then
--dbms_output.put_line(line);
--dbms_output.put_line(substr( line, 13, 10 ));
--               lineno := to_number(substr( line, 13, 6 ));
               lineno := to_number(substr( line, 13, 10 ));
--               line   := substr( line, 21 );
               line   := substr( line, 24 );
               if ( line like 'pr%' ) then
                   n := length( 'procedure ' );
               elsif ( line like 'fun%' ) then
                   n := length( 'function ' );
               elsif ( line like 'package body%' ) then
                   n := length( 'package body ' );
               elsif ( line like 'pack%' ) then
                   n := length( 'package ' );
               elsif ( line like 'anonymous%' ) then
                   n := length( 'anonymous block ' );
               else
                   n := null;
               end if;
               if ( n is not null ) then
                  caller_t := ltrim(rtrim(upper(substr( line, 1, n-1 ))));
               else
                  caller_t := 'TRIGGER';
               end if;

               line := substr( line, nvl(n,1) );
               n := instr( line, '.' );
               owner := ltrim(rtrim(substr( line, 1, n-1 )));
               name  := ltrim(rtrim(substr( line, n+1 )));
           end if;
       end if;
   end loop;
end;

function who_called_me_str return varchar2 is 
my_owner varchar2(255);
my_name varchar2(255);
my_lineno varchar2(255);
my_caller_t varchar2(255);
begin
  who_called_me(2, my_owner,my_name,my_lineno,my_caller_t);
  for Cur in (select * from all_source where owner=my_owner and name=my_name and line=my_lineno and type=my_caller_t) loop
     return (my_name||', line '||my_lineno||' - '|| Cur.Text);
  end loop;
  null;
end;

procedure chk(b boolean) is
begin
  if b = true then
    dbms_output.put_line('OK');
  else
    dbms_output.put_line('failed! Test case '||who_called_me_str);
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
  x.createdok46(nz, 'М', XMLtype('<DOC><SOD><ROW><KOD_MAT>qwe</KOD_MAT><DOP_KOD>dop_kod</DOP_KOD><D_GAR>11.11.2014</D_GAR><DCE>dce</DCE><PRIM>prim</PRIM><SHPZ>shpz</SHPZ><IZD>izd</IZD><KOL_TREB>111</KOL_TREB></ROW><ROW><KOD_MAT>rty</KOD_MAT><KOL_TREB>222</KOL_TREB></ROW></SOD></DOC>'));
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
