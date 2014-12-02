object Form1: TForm1
  Left = 258
  Top = 144
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
  object Button1: TButton
    Left = 344
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 56
    Top = 216
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 472
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Button3'
    TabOrder = 2
    OnClick = Button3Click
  end
  object OraSession1: TOraSession
    Options.Direct = True
    Username = 'admdba'
    Password = 'a5247'
    Server = 'localhost::xe'
    Connected = True
    LoginPrompt = False
    Left = 176
    Top = 64
  end
  object OraQuery1: TOraQuery
    SQLUpdate.Strings = (
      'begin'
      '  admdba.skldok.ADD_TO_DOK(:x);'
      'end;')
    Session = OraSession1
    SQL.Strings = (
      'begin'
      'declare'
      'c clob;'
      'x xmltype;'
      'begin'
      '--c := :1;'
      'x := admdba.skldok_pkg.blob_to_xmltype(null);'
      'return;'
      ':2 := :1;'
      '--x := admdba.skldok_pkg.blob_to_xmltype(:1);'
      '--admdba.skldok_pkg.add_to_dok( x);'
      '--admdba.skldok_pkg.add_to_dok(xmltype.createxml(:1));'
      'end;'
      'end;')
    Options.TemporaryLobUpdate = True
    Left = 232
    Top = 64
    ParamData = <
      item
        DataType = ftBlob
        Name = '2'
        Value = ''
      end
      item
        DataType = ftUnknown
        Name = '1'
      end>
  end
  object OraQuery2: TOraQuery
    SQLUpdate.Strings = (
      'begin'
      '  admdba.skldok.ADD_TO_DOK(:x);'
      'end;')
    Session = OraSession1
    SQL.Strings = (
      'begin'
      'admdba.skldok_pkg.add_to_dok(xmltype(:1));'
      'end;')
    Options.TemporaryLobUpdate = True
    Left = 368
    Top = 96
    ParamData = <
      item
        DataType = ftOraClob
        Name = '1'
        ParamType = ptInput
        Value = ''
      end>
  end
  object OraQuery3: TOraQuery
    Session = OraSession1
    SQL.Strings = (
      'declare'
      'x xmltype;'
      'begin'
      'x := xmltype(:1);'
      '--raise_application_error(-20001, length(:1));'
      'end;')
    Left = 32
    Top = 160
    ParamData = <
      item
        DataType = ftUnknown
        Name = '1'
      end>
  end
end
