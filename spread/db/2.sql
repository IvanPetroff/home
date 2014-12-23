declare 
obj class_spis_dok;
begin
for cur in (select class_spis_dok(dok_id) x from asu_spis_dok where skl like '8.%' and dok_id=917127) loop
Cur.x.set_spreadable(1,'234');

end loop;
end;
