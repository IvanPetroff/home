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
    Text = 'Edit1'
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
    Left = 40
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
  object db: TOraSession
    Left = 88
    Top = 24
  end
  object OraQuery1: TOraQuery
    Session = db
    SQL.Strings = (
      'select s.* from asu_more_attr m, asu_spis_dok s'
      'where s.id=m.key'
      'and m.cat='#39'SPIS_DOK'#39' and m.name_attr='#39'SPREAD'#39' and m.val_num=:1')
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
end
