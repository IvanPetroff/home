-- Create table
create table SPR_QUESTION
(
  id    NUMBER,
  name  VARCHAR2(16 CHAR),
  label VARCHAR2(200 CHAR),
  ord   NUMBER,
  usr   VARCHAR2(16 CHAR),
  dat   DATE
)
tablespace USERS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    next 1M
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column SPR_QUESTION.name
  is 'Служебное имя';
comment on column SPR_QUESTION.label
  is 'Текстовое наименование на экране для человека';
comment on column SPR_QUESTION.ord
  is 'Порядок расположения. меньше - раньше';
