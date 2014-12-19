object Form1: TForm1
  Left = 311
  Top = 160
  Width = 1230
  Height = 589
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
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 185
    Height = 562
    Align = alLeft
    Caption = 'GroupBox1'
    TabOrder = 0
    inline FraListObjects1: TFraListObjects
      Left = 2
      Top = 15
      Width = 181
      Height = 545
      Align = alClient
      inherited ListBox1: TListBox
        Width = 181
        Height = 545
        OnClick = FraListObjects1ListBox1Click
      end
    end
  end
  object GroupBox2: TGroupBox
    Left = 185
    Top = 0
    Width = 1037
    Height = 562
    Align = alClient
    Caption = 'GroupBox2'
    TabOrder = 1
    inline FraLightRichEdit1: TFraLightRichEdit
      Left = 2
      Top = 15
      Width = 1033
      Height = 545
      Align = alClient
      inherited REdit: TRichEdit
        Width = 1033
        Height = 545
      end
    end
  end
  object db: TOraSession
    Options.Direct = True
    Username = 'tem'
    Server = 'test'
    ConnectDialog = ConnectDialog1
    Left = 144
    Top = 8
  end
  object OraQuery1: TOraQuery
    Session = db
    Left = 192
    Top = 8
  end
  object OraDataSource1: TOraDataSource
    DataSet = OraQuery1
    Left = 224
    Top = 8
  end
  object ConnectDialog1: TConnectDialog
    Caption = 'Connect'
    UsernameLabel = 'User Name'
    PasswordLabel = 'Password'
    ServerLabel = 'Server'
    ConnectButton = 'Connect'
    CancelButton = 'Cancel'
    Left = 112
    Top = 8
  end
end
