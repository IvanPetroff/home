object Form1: TForm1
  Left = 212
  Top = 137
  Width = 1230
  Height = 589
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 16
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '8223593'
  end
  object Button1: TButton
    Left = 152
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 1
    OnClick = Button1Click
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 112
    Width = 577
    Height = 273
    DataSource = OraDataSource1
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object DBGrid2: TDBGrid
    Left = 600
    Top = 112
    Width = 577
    Height = 273
    DataSource = OraDataSource2
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object db: TOraSession
    Left = 88
    Top = 24
  end
  object OraQuery1: TOraQuery
    Session = db
    SQL.Strings = (
      
        'select t.kod, t.unizak, (select pzak||'#39' / '#39'||izd from asu_zagzak' +
        ' where unizak=t.unizak), sum(t.kol), sum(t.kol)*t.cena from ('
      
        'select s.kod, trim(substr(m2.name_attr, instr(m2.name_attr,'#39';'#39')+' +
        '1) ) unizak, s.kol*s.kol_mat*m2.val_num/100 kol, s.cena'
      'from asu_more_attr m1, asu_more_attr m2, asu_spis_dok s'
      'where s.id=m1.key'
      
        'and m1.cat='#39'SPIS_DOK'#39' and m1.name_attr='#39'SPREAD'#39' and m1.val_num=:' +
        '1'
      'and m2.cat='#39'PRC_TR_N'#39' and m2.key=:1'
      
        'and nvl(m1.val_txt,'#39'-'#39')=nvl(trim(substr(m2.name_attr, 1, instr(m' +
        '2.name_attr,'#39';'#39')-1) ),'#39'-'#39')'
      ') t'
      'group by kod,unizak, cena')
    Left = 136
    Top = 64
    ParamData = <
      item
        DataType = ftUnknown
        Name = '1'
      end>
  end
  object OraDataSource1: TOraDataSource
    DataSet = OraQuery1
    Left = 176
    Top = 64
  end
  object OraQuery2: TOraQuery
    Session = db
    SQL.Strings = (
      
        'select m.unizak, (select pzak||'#39' / '#39'||izd from asu_zagzak where ' +
        'unizak=m.unizak), m.prc from  '
      '('
      'select '
      '  trim(substr(m.name_attr, instr(m.name_attr,'#39';'#39')+1) ) unizak,'
      '  trim(substr(m.name_attr, 1, instr(m.name_attr,'#39';'#39')-1) ) uch,'
      '  m.val_num prc'
      'from asu_more_attr m'
      'where m.cat='#39'PRC_TR_F'#39' and m.key=:1'
      ') m')
    Left = 672
    Top = 72
    ParamData = <
      item
        DataType = ftUnknown
        Name = '1'
      end>
  end
  object OraDataSource2: TOraDataSource
    DataSet = OraQuery2
    Left = 712
    Top = 72
  end
end
