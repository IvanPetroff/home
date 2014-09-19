object FormImage: TFormImage
  Left = 336
  Top = 205
  Width = 1244
  Height = 623
  Caption = 'Fast Image Viewer'
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  WindowState = wsMaximized
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  inline FraImage1: TFraImage
    Width = 1236
    Height = 577
    Align = alClient
    inherited img: TImage
      Width = 1236
      Height = 558
    end
    inherited pFileName: TPanel
      Width = 1236
      Caption = 'NO PICTURE'
      Font.Color = clSilver
      ParentFont = False
    end
  end
  object msg: TStatusBar
    Left = 0
    Top = 577
    Width = 1236
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 232
    Top = 72
  end
end
