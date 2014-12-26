object Form1: TForm1
  Left = 253
  Top = 184
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
  object Splitter1: TSplitter
    Left = 385
    Top = 49
    Width = 3
    Height = 513
    Cursor = crHSplit
  end
  object Button2: TButton
    Left = 624
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 0
    OnClick = Button2Click
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1222
    Height = 49
    Align = alTop
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 368
      Top = 8
      Width = 89
      Height = 22
      Caption = 'Пересчитать'
    end
    object GroupBox3: TGroupBox
      Left = 1
      Top = 1
      Width = 225
      Height = 47
      Align = alLeft
      Caption = 'Рег. № служебной записки'
      TabOrder = 0
      object Edit1: TEdit
        Left = 8
        Top = 16
        Width = 121
        Height = 25
        TabOrder = 0
        Text = '8223593'
      end
      object Button1: TButton
        Left = 134
        Top = 16
        Width = 75
        Height = 25
        Caption = 'Открыть'
        TabOrder = 1
        OnClick = Button1Click
      end
    end
    object RB_Norma: TRadioButton
      Left = 232
      Top = 11
      Width = 65
      Height = 17
      Caption = 'Норма'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = RB_NormaClick
    end
    object RB_Fact: TRadioButton
      Left = 301
      Top = 11
      Width = 57
      Height = 17
      Caption = 'Факт'
      TabOrder = 2
      OnClick = RB_NormaClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 49
    Width = 385
    Height = 513
    Align = alLeft
    Caption = 'Процентовка'
    TabOrder = 2
    inline FraPrcFact1: TFraPrcFact
      Left = 2
      Top = 15
      Width = 381
      Height = 496
      Align = alClient
      inherited DBGridEh1: TDBGridEh
        Width = 381
        Height = 496
        Columns = <
          item
            EditButtons = <>
            FieldName = 'UCH'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Участок'
          end
          item
            EditButtons = <>
            FieldName = 'UNIZAK'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'PZAK'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Заказ'
            Width = 66
          end
          item
            EditButtons = <>
            FieldName = 'IZD'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Изделие'
          end
          item
            EditButtons = <>
            FieldName = 'PRC'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Процент'
          end>
      end
      inherited DS: TOraQuery
        ParamData = <
          item
            DataType = ftString
            Name = 'x'
            Value = 
              '<ROWSET><ROW><UNIZAK>123</UNIZAK><UCH>456</UCH><PRC>789</PRC></R' +
              'OW></ROWSET>'
          end>
      end
    end
  end
  object GroupBox2: TGroupBox
    Left = 388
    Top = 49
    Width = 834
    Height = 513
    Align = alClient
    Caption = 'Расклад'
    TabOrder = 3
    inline FraSZ1: TFraSZ
      Left = 2
      Top = 15
      Width = 830
      Height = 496
      Align = alClient
      inherited DBGridEh1: TDBGridEh
        Width = 830
        Height = 496
        Columns = <
          item
            EditButtons = <>
            FieldName = 'KOD'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Код'
            Width = 97
          end
          item
            EditButtons = <>
            FieldName = 'NAIM'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Наименование'
            Width = 129
          end
          item
            EditButtons = <>
            FieldName = 'R_SORT'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Размер сортамента'
            Width = 111
          end
          item
            EditButtons = <>
            FieldName = 'UNIZAK'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Width = 49
          end
          item
            EditButtons = <>
            FieldName = 'PZAK'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Заказ'
            Width = 56
          end
          item
            EditButtons = <>
            FieldName = 'IZD'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Изделие'
          end
          item
            EditButtons = <>
            FieldName = 'KOL'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Количество'
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'KOL_CENA'
            Footers = <>
            KeyList.Strings = ()
            MRUList.Items.Strings = ()
            PickList.Strings = ()
            Title.Caption = 'Деньги'
          end>
      end
      inherited DS: TOraQuery
        ParamData = <
          item
            DataType = ftString
            Name = 'x'
            Value = 
              '<ROWSET><ROW><UNIZAK>123</UNIZAK><UCH>456</UCH><PRC>789</PRC></R' +
              'OW></ROWSET>'
          end
          item
            DataType = ftString
            Name = '1'
            Value = 
              '<ROWSET><ROW><UNIZAK>123</UNIZAK><UCH>456</UCH><PRC>789</PRC></R' +
              'OW></ROWSET>'
          end>
      end
    end
  end
  object db: TOraSession
    Options.Direct = True
    Username = 'tem'
    Password = 'jngecr'
    Server = 'ac-ceh::b'
    Connected = True
    Left = 88
    Top = 24
  end
  object qxml: TOraQuery
    Session = db
    SQL.Strings = (
      
        'select class_spreadlist.load_prc_trud#('#39'F'#39',:1).getstringval() x ' +
        'from dual')
    Left = 264
    Top = 24
    ParamData = <
      item
        DataType = ftUnknown
        Name = '1'
      end>
  end
end
