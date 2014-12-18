object Form1: TForm1
  Left = 325
  Top = 176
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
  object ListBox1: TListBox
    Left = 0
    Top = 0
    Width = 169
    Height = 561
    Align = alLeft
    ItemHeight = 13
    TabOrder = 0
  end
  object RichEdit1: TRichEdit
    Left = 169
    Top = 0
    Width = 1053
    Height = 561
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    TabOrder = 1
    OnChange = RichEdit1Change
  end
  object OraSession1: TOraSession
    Username = 'tem'
    Server = 'test'
    ConnectDialog = ConnectDialog1
    Left = 144
    Top = 8
  end
  object OraQuery1: TOraQuery
    Session = OraSession1
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
