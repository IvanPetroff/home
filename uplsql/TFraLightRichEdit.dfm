object FraLightRichEdit: TFraLightRichEdit
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  TabOrder = 0
  object RichEdit1: TRichEdit
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    TabOrder = 0
    OnKeyUp = RichEdit1KeyUp
  end
end
