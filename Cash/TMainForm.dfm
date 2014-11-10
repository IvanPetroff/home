object MainForm: TMainForm
  Left = 473
  Top = 135
  Width = 855
  Height = 418
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
  object DBG: TDBGridEh
    Left = 0
    Top = 0
    Width = 745
    Height = 391
    Align = alClient
    DataSource = DataSource1
    Flat = True
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    SortLocal = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'dat'
        Footers = <>
        Title.Caption = 'Дата'
        Width = 81
      end
      item
        EditButtons = <>
        FieldName = 'cat'
        Footers = <>
        Title.Caption = 'Категория'
        Width = 82
      end
      item
        EditButtons = <>
        FieldName = 'naim'
        Footers = <>
        Title.Caption = 'Название'
        Width = 181
      end
      item
        EditButtons = <>
        FieldName = 'kol'
        Footers = <>
        Title.Caption = 'Количество'
      end
      item
        EditButtons = <>
        FieldName = 'cena'
        Footers = <>
        Title.Caption = 'Цена за ед.'
      end
      item
        EditButtons = <>
        FieldName = 'stoim'
        Footers = <>
        Title.Caption = 'Стоимость'
      end
      item
        EditButtons = <>
        FieldName = 'curr'
        Footers = <>
        Title.Caption = 'Валюта'
        Width = 56
      end
      item
        EditButtons = <>
        FieldName = 'id'
        Footers = <>
      end>
  end
  inline EditorGrid1: TEditorGrid
    Left = 96
    Top = 88
    Width = 169
    TabOrder = 1
  end
  inline EditorCat: TEditorGrid
    Left = 328
    Top = 136
    Width = 185
    TabOrder = 2
  end
  object Panel1: TPanel
    Left = 745
    Top = 0
    Width = 102
    Height = 391
    Align = alRight
    Caption = 'Panel1'
    TabOrder = 3
    object Button1: TButton
      Left = 14
      Top = 8
      Width = 75
      Height = 25
      Caption = 'save'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 14
      Top = 40
      Width = 75
      Height = 25
      Caption = 'load'
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  inline EditorCurr: TEditorGrid
    Left = 584
    Top = 104
    Width = 145
    Height = 233
    TabOrder = 4
  end
  object MT2: TMemTableEh
    Active = True
    Params = <>
    AfterPost = MT2AfterPost
    Left = 128
    Top = 40
    object MT2id: TIntegerField
      FieldName = 'id'
    end
    object MT2dat: TDateField
      FieldName = 'dat'
    end
    object MT2naim: TStringField
      FieldName = 'naim'
      Size = 128
    end
    object MT2cat: TStringField
      FieldName = 'cat'
      Size = 32
    end
    object MT2kol: TFloatField
      FieldName = 'kol'
    end
    object MT2cena: TFloatField
      FieldName = 'cena'
    end
    object MT2stoim: TFloatField
      FieldName = 'stoim'
    end
    object MemTableData: TMemTableDataEh
      object DataStruct: TMTDataStructEh
        object id: TMTNumericDataFieldEh
          FieldName = 'id'
          NumericDataType = fdtIntegerEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
          currency = False
          Precision = 0
        end
        object dat: TMTDateTimeDataFieldEh
          FieldName = 'dat'
          DateTimeDataType = fdtDateEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
        end
        object naim: TMTStringDataFieldEh
          FieldName = 'naim'
          StringDataType = fdtStringEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
          Size = 128
          Transliterate = False
        end
        object cat: TMTStringDataFieldEh
          FieldName = 'cat'
          StringDataType = fdtStringEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
          Size = 32
          Transliterate = False
        end
        object kol: TMTNumericDataFieldEh
          FieldName = 'kol'
          NumericDataType = fdtFloatEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
          currency = False
          Precision = 0
        end
        object cena: TMTNumericDataFieldEh
          FieldName = 'cena'
          NumericDataType = fdtFloatEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
          currency = False
          Precision = 0
        end
        object stoim: TMTNumericDataFieldEh
          FieldName = 'stoim'
          NumericDataType = fdtFloatEh
          Alignment = taLeftJustify
          DisplayWidth = 0
          Required = False
          Visible = False
          currency = False
          Precision = 0
        end
      end
      object RecordsList: TRecordsListEh
        Data = (
          (
            1
            nil
            'qwerty'
            nil
            nil
            nil
            nil)
          (
            2
            nil
            'asdfghh'
            nil
            nil
            nil
            nil)
          (
            3
            nil
            nil
            nil
            nil
            nil
            nil))
      end
    end
  end
  object DataSource1: TDataSource
    DataSet = MT
    Left = 160
    Top = 40
  end
  object MT: TVirtualTable
    Active = True
    IndexFieldNames = 'dat desc'
    AfterInsert = MTAfterInsert
    BeforePost = MTBeforePost
    AfterPost = MTAfterPost
    FieldDefs = <
      item
        Name = 'id'
        DataType = ftInteger
      end
      item
        Name = 'dat'
        DataType = ftDate
      end
      item
        Name = 'naim'
        DataType = ftString
        Size = 128
      end
      item
        Name = 'cat'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'kol'
        DataType = ftFloat
      end
      item
        Name = 'cena'
        DataType = ftFloat
      end
      item
        Name = 'stoim'
        DataType = ftFloat
      end
      item
        Name = 'curr'
        DataType = ftString
        Size = 16
      end>
    Left = 216
    Top = 40
    Data = {
      030008000200696403000000000000000300646174090000000000000004006E
      61696D01008000000000000300636174010020000000000003006B6F6C060000
      0000000000040063656E610600000000000000050073746F696D060000000000
      00000400637572720100100000000000000000000000}
    object TIntegerField
      FieldName = 'id'
    end
    object TDateField
      FieldName = 'dat'
    end
    object TStringField
      FieldName = 'naim'
      Size = 128
    end
    object TStringField
      FieldName = 'cat'
      Size = 32
    end
    object TFloatField
      FieldName = 'kol'
    end
    object TFloatField
      FieldName = 'cena'
    end
    object TFloatField
      FieldName = 'stoim'
    end
    object TStringField
      FieldName = 'curr'
      Size = 16
    end
  end
end
