object Form1: TForm1
  Left = 292
  Top = 218
  Width = 1244
  Height = 606
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 1236
    Height = 579
    Align = alClient
    OnClick = Image1Click
    OnDblClick = Image1DblClick
  end
  object FileListBox1: TFileListBox
    Left = 16
    Top = 24
    Width = 145
    Height = 97
    ItemHeight = 13
    Mask = '*.jpg'
    TabOrder = 0
  end
end
