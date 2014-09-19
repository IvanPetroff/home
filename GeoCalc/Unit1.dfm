object Form1: TForm1
  Left = 246
  Top = 259
  Width = 1231
  Height = 394
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
  object SpeedButton1: TSpeedButton
    Left = 272
    Top = 88
    Width = 23
    Height = 22
    Caption = '>>'
    OnClick = SpeedButton1Click
  end
  object Label1: TLabel
    Left = 304
    Top = 72
    Width = 5
    Height = 13
    Caption = 'x'
  end
  object Label2: TLabel
    Left = 440
    Top = 72
    Width = 5
    Height = 13
    Caption = 'y'
  end
  object Label3: TLabel
    Left = 72
    Top = 72
    Width = 23
    Height = 13
    Caption = 'град'
  end
  object Label4: TLabel
    Left = 136
    Top = 72
    Width = 20
    Height = 13
    Caption = 'мин'
  end
  object Label5: TLabel
    Left = 200
    Top = 72
    Width = 18
    Height = 13
    Caption = 'сек'
  end
  object Button1: TButton
    Left = 96
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object E_grB: TEdit
    Left = 72
    Top = 88
    Width = 57
    Height = 21
    TabOrder = 1
  end
  object E_minB: TEdit
    Left = 136
    Top = 88
    Width = 57
    Height = 21
    TabOrder = 2
  end
  object E_secB: TEdit
    Left = 200
    Top = 88
    Width = 57
    Height = 21
    TabOrder = 3
  end
  object E_x: TEdit
    Left = 304
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object E_y: TEdit
    Left = 440
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object E_grL: TEdit
    Left = 72
    Top = 112
    Width = 57
    Height = 21
    TabOrder = 6
  end
  object E_secL: TEdit
    Left = 200
    Top = 112
    Width = 57
    Height = 21
    TabOrder = 7
  end
  object E_minL: TEdit
    Left = 136
    Top = 112
    Width = 57
    Height = 21
    TabOrder = 8
  end
end
