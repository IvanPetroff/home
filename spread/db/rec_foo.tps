create or replace type rec_foo as object
(
  -- Author  : Администратор
  -- Created : 21.12.2014 11:18:29
  -- Purpose : 
  id         number
  ,dok_id    number
  ,kol       number
  ,kol_treb  number
  ,d_ceh     date
  ,u_ceh     varchar2(16char)
  ,d_buh     date
  ,u_buh     varchar2(16char)
  ,ost_id    number
  ,type      varchar2(16char)

)
/
