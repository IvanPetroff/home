inherited F_PersonList: TF_PersonList
  Left = 368
  Top = 218
  Width = 675
  Height = 421
  Caption = 'Список пациентов'
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridEh1: TDBGridEh
    Left = 0
    Top = 0
    Width = 667
    Height = 394
    Align = alClient
    DataSource = OraDataSource1
    Flat = True
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    STFilter.Visible = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnApplyFilter = DBGridEh1ApplyFilter
    OnDblClick = DBGridEh1DblClick
    Columns = <
      item
        EditButtons = <>
        FieldName = 'FIO'
        Footers = <>
        Title.Caption = 'Ф.И.О.'
        Width = 301
      end
      item
        EditButtons = <>
        FieldName = 'SEX'
        Footers = <>
        Title.Caption = 'Пол'
        Width = 28
      end
      item
        EditButtons = <>
        FieldName = 'D_BIRTH'
        Footers = <>
        Title.Caption = 'Дата рождения'
        Width = 85
      end
      item
        EditButtons = <>
        FieldName = 'ID'
        Footers = <>
      end
      item
        EditButtons = <>
        FieldName = 'D_REG'
        Footers = <>
        Title.Caption = 'Дата регистрации'
        Width = 105
      end>
  end
  object OraQuery1: TOraQuery
    SQL.Strings = (
      'select fio'
      ',sex'
      ',to_char(d_birth,'#39'dd.mm.yyyy'#39') d_birth'
      ',to_char(d_reg,'#39'dd.mm.yyyy'#39') d_reg'
      ',id '
      ''
      'from syn_person'
      'where 1=1'
      '/*FILTER*/'
      'order by FIO')
    Active = True
    Left = 48
    Top = 16
  end
  object OraDataSource1: TOraDataSource
    DataSet = OraQuery1
    Left = 80
    Top = 16
  end
end
