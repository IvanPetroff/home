create or replace package debug_pkg is

  -- Author  : �������������
  -- Created : 12.12.2014 11:07:19
  -- Purpose : 
  
  -- Public type declarations
function who_called_me( steps_to_back  number) return varchar2;
procedure put_line(s varchar2);
procedure chk(b boolean);



end debug_pkg;
/
create or replace package body debug_pkg is

  -- Private type declarations
function who_called_me( steps_to_back  number) return varchar2
is
                         my_owner      varchar2(255);
                         my_name       varchar2(255);
                         my_lineno     number;
                         my_caller_t   varchar2(255);

   call_stack  varchar2(4096);
   n           number;
   found_stack BOOLEAN := FALSE;
   line        varchar2(255);
   cnt         number := 0;
 
-- http://tkyte.blogspot.ru/2009/10/httpasktomoraclecomtkytewhocalledme.html   
begin
   call_stack  := dbms_utility.format_call_stack;
--dbms_output.put_line(call_stack);
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
line := trim(substr(line,instr(line,' ')));
my_lineno := to_number(substr( line, 1, instr(line,' ') ));
line := trim(substr(line,instr(line,' ')));
--               lineno := to_number(substr( line, 13, 6 ));
--               my_lineno := to_number(substr( line, 13, 10 ));
--               line   := substr( line, 21 );
--               line   := substr( line, 24 );
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
                  my_caller_t := ltrim(rtrim(upper(substr( line, 1, n-1 ))));
               else
--                  my_caller_t := 'TRIGGER';
                  my_caller_t := '%';
               end if;

               line := substr( line, nvl(n,1) );
               n := instr( line, '.' );
               my_owner := ltrim(rtrim(substr( line, 1, n-1 )));
               my_name  := ltrim(rtrim(substr( line, n+1 )));
           end if;
       end if;
   end loop;
--dbms_output.put_line(my_caller_t);
  for Cur in (select * from all_source where owner=my_owner and name=my_name and line=my_lineno and type like my_caller_t) loop
     return (my_name||', line '||my_lineno||' - '|| trim(Substr(Cur.Text,1,length(Cur.Text)-1)));
  end loop;
  return null;
end;


  procedure put_line(s varchar2) is
  begin
    dbms_output.put_line('>> '||who_called_me(2)||' >>> ('||s||')');
    null;
  end;
  
procedure chk(b boolean) is
begin
  if b = true then
    dbms_output.put_line('OK');
  else
    dbms_output.put_line('failed! Test case '||debug_pkg.who_called_me(1) ); 
  end if;
  null;
end;  

begin
  -- Initialization
  null;
end debug_pkg;
/