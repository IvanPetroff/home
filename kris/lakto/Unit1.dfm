object MainForm: TMainForm
  Left = 192
  Top = 108
  Width = 749
  Height = 449
  Caption = 'MainForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 88
    Top = 16
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Edit1: TEdit
    Left = 96
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'Edit1'
  end
  object Memo1: TMemo
    Left = 320
    Top = 56
    Width = 393
    Height = 345
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssBoth
    TabOrder = 1
    WordWrap = False
  end
  object Button1: TButton
    Left = 48
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 48
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Send1'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Edit2: TEdit
    Left = 176
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'Edit2'
  end
  object Button3: TButton
    Left = 48
    Top = 168
    Width = 75
    Height = 25
    Caption = 'Send2'
    TabOrder = 5
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 168
    Top = 160
    Width = 75
    Height = 25
    Caption = 'Button4'
    TabOrder = 6
  end
  object TimerTimeout: TTimer
    Enabled = False
    Interval = 5000
    OnTimer = TimerTimeoutTimer
    Left = 112
    Top = 64
  end
end
