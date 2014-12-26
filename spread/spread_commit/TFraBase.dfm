object FraBase: TFraBase
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  TabOrder = 0
  object DBGridEh1: TDBGridEh
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    Align = alClient
    AutoFitColWidths = True
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
  object DS: TOraQuery
    Left = 48
    Top = 32
  end
  object OraDataSource1: TOraDataSource
    DataSet = DS
    Left = 88
    Top = 32
  end
end
