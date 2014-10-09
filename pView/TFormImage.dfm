object FormImage: TFormImage
  Left = 364
  Top = 107
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
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
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
  object FileListBox1: TFileListBox
    Left = 120
    Top = 224
    Width = 145
    Height = 97
    ItemHeight = 13
    Mask = '*.jpg'
    TabOrder = 2
    Visible = False
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    Left = 232
    Top = 72
  end
end
