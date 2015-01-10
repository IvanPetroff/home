-- Create table
create table PERSON
(
  id        NUMBER,
  fam       VARCHAR2(32 CHAR),
  name1     VARCHAR2(32 CHAR),
  name2     VARCHAR2(32 CHAR),
  sex       VARCHAR2(1 CHAR),
  d_birth   DATE,
  tel1      VARCHAR2(20 CHAR),
  tel2      VARCHAR2(50 CHAR),
  email     VARCHAR2(30 CHAR),
  d_reg     DATE,
  usr       VARCHAR2(16 CHAR),
  dat       DATE,
  city_id   NUMBER,
  street    VARCHAR2(20 CHAR),
  house     VARCHAR2(10 CHAR),
  apartment VARCHAR2(10 CHAR)
)
tablespace USERS
  pctfree 10
  pctused 40
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    next 1M
    minextents 1
    maxextents unlimited
  );
-- Add comments to the table 
comment on table PERSON
  is '������������ ������ ��������';
-- Add comments to the columns 
comment on column PERSON.fam
  is '�������';
comment on column PERSON.name1
  is '���';
comment on column PERSON.name2
  is '��������';
comment on column PERSON.sex
  is '��� (�/�)';
comment on column PERSON.d_birth
  is '���� ��������';
comment on column PERSON.tel1
  is '�������(��������)';
comment on column PERSON.tel2
  is '�������(��������������)';
comment on column PERSON.d_reg
  is '���� �����������';
comment on column PERSON.usr
  is '���';
comment on column PERSON.dat
  is '�����';
comment on column PERSON.city_id
  is '�����';
comment on column PERSON.street
  is '�����';
comment on column PERSON.house
  is '���/������ � �.�.';
comment on column PERSON.apartment
  is '��������';