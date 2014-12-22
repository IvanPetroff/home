create or replace type rec_spis_dok force as object
(
  -- Author  : Администратор
  -- Created : 21.12.2014 11:18:29
  -- Purpose : 
  id        NUMBER,
  spk_id    NUMBER,
  kol       NUMBER,
  kol_mat   NUMBER,
  ost_id    NUMBER,
  shpz      VARCHAR2(12),
  izd       VARCHAR2(18),
  bs        VARCHAR2(11),
  prizn     VARCHAR2(2),
  usr       VARCHAR2(10),
  dat       DATE,
  dok_id    NUMBER,
  d_ceh     DATE,
  u_ceh     VARCHAR2(8),
  d_buh     DATE,
  u_buh     VARCHAR2(8),
  skl       VARCHAR2(6),
  type      VARCHAR2(1),
  kod       VARCHAR2(24),
  r_sort    VARCHAR2(18),
  cena      NUMBER(14,2),
  lim_id    NUMBER,
  dop_dok   VARCHAR2(40),
  r_zag     VARCHAR2(32),
  prc_nds   NUMBER(6,2),
  cntrl     VARCHAR2(1),
  t_id      VARCHAR2(1),
  kol_part  NUMBER,
  prih_id   NUMBER,
  razm_zag  VARCHAR2(30),
  fakt_rash NUMBER,
  d_drag    DATE,
  dok_drag  VARCHAR2(24)

)
/
