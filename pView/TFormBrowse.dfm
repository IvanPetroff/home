object FormBrowse: TFormBrowse
  Left = 424
  Top = 139
  AutoScroll = False
  Caption = 'Картинки'
  ClientHeight = 596
  ClientWidth = 1236
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter2: TSplitter
    Left = 185
    Top = 0
    Width = 3
    Height = 596
    Cursor = crHSplit
    Beveled = True
    Color = clHighlight
    ParentColor = False
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 185
    Height = 596
    Align = alLeft
    Color = clWhite
    ParentColor = False
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 2
      Top = 253
      Width = 181
      Height = 3
      Cursor = crVSplit
      Align = alTop
      Beveled = True
      Color = clHighlight
      ParentColor = False
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 2
      Top = 41
      Width = 181
      Height = 212
      TabStop = False
      Align = alTop
      FileList = FileListBox1
      ItemHeight = 16
      TabOrder = 0
      OnChange = FileListBox1Change
    end
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 181
      Height = 26
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 1
      object DriveComboBox1: TDriveComboBox
        Left = 8
        Top = 4
        Width = 169
        Height = 19
        TabStop = False
        Anchors = [akLeft, akTop, akRight]
        DirList = DirectoryListBox1
        TabOrder = 0
      end
    end
    object FileListBox1: TFileListBox
      Left = 2
      Top = 504
      Width = 181
      Height = 90
      TabStop = False
      Align = alBottom
      ItemHeight = 16
      Mask = '*.jpg'
      ShowGlyphs = True
      TabOrder = 2
      Visible = False
    end
    inline FraImage1: TFraImage
      Left = 2
      Top = 256
      Width = 181
      Height = 248
      Align = alClient
      TabOrder = 3
      inherited img: TImage
        Width = 181
        Height = 229
      end
      inherited pFileName: TPanel
        Width = 181
      end
    end
  end
  object ScrollBox1: TScrollBox
    Left = 188
    Top = 0
    Width = 1048
    Height = 596
    HorzScrollBar.Style = ssHotTrack
    VertScrollBar.Style = ssHotTrack
    Align = alClient
    BorderStyle = bsNone
    Color = clWhite
    ParentColor = False
    TabOrder = 1
  end
end
