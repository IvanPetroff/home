object FraPreview: TFraPreview
  Left = 0
  Top = 0
  Width = 136
  Height = 128
  Color = clWhite
  ParentColor = False
  TabOrder = 0
  object Shape1: TShape
    Left = 0
    Top = 0
    Width = 136
    Height = 104
    Align = alClient
    Pen.Color = clSilver
    Shape = stRoundRect
  end
  object img: TImage
    Left = 8
    Top = 12
    Width = 120
    Height = 80
    OnClick = imgClick
    OnDblClick = imgDblClick
  end
  object pFileName: TPanel
    Left = 0
    Top = 104
    Width = 136
    Height = 24
    Align = alBottom
    BevelOuter = bvNone
    Caption = 'pFileName'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = True
    ParentFont = False
    TabOrder = 0
    object CheckBox1: TCheckBox
      Left = 4
      Top = 3
      Width = 17
      Height = 17
      TabStop = False
      TabOrder = 0
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = Timer1Timer
    Left = 56
    Top = 40
  end
end
