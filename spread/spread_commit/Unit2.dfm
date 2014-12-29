object Form2: TForm2
  Left = 476
  Top = 169
  Width = 1230
  Height = 589
  Caption = 'Form2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridEh1: TDBGridEh
    Left = 48
    Top = 160
    Width = 497
    Height = 265
    DataSource = OraDataSource1
    Flat = False
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object OraQuery1: TOraQuery
    SQL.Strings = (
      'select '
      '  m.dok_id'
      'from  '
      '('
      'select extractvalue(column_value,'#39'/ROW/DOK_ID'#39') dok_id'
      
        'from table(xmlsequence(c_spreadlist.create_obj().getListOfList()' +
        '.extract('#39'/ROWSET/ROW'#39')))'
      ') m')
    Active = True
    Left = 96
    Top = 32
  end
  object OraDataSource1: TOraDataSource
    DataSet = OraQuery1
    Left = 136
    Top = 32
  end
end
