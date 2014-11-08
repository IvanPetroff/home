object MainForm: TMainForm
  Left = 279
  Top = 153
  Width = 1230
  Height = 589
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
    Left = 8
    Top = 8
    Width = 1025
    Height = 473
    DataSource = DataSource1
    Flat = False
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
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
  object Button1: TButton
    Left = 64
    Top = 520
    Width = 75
    Height = 25
    Caption = 'save'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 520
    Width = 75
    Height = 25
    Caption = 'load'
    TabOrder = 4
    OnClick = Button2Click
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
      end>
    Left = 216
    Top = 40
    Data = {
      030007000200696403000000000000000300646174090000000000000004006E
      61696D01008000000000000300636174010020000000000003006B6F6C060000
      0000000000040063656E610600000000000000050073746F696D060000000000
      0000000003000000040000000100000000000000060000007177657274790000
      0000000000000000000000000000040000000200000000000000050000006173
      6466670000000000000000000000000000000004000000030000000000000000
      00000000000000000000000000000000000000}
    object MTid: TIntegerField
      FieldName = 'id'
    end
    object MTdat: TDateField
      FieldName = 'dat'
    end
    object MTnaim: TStringField
      FieldName = 'naim'
      Size = 128
    end
    object MTcat: TStringField
      FieldName = 'cat'
      Size = 32
    end
    object MTkol: TFloatField
      FieldName = 'kol'
    end
    object MTcena: TFloatField
      FieldName = 'cena'
    end
    object MTstoim: TFloatField
      FieldName = 'stoim'
    end
  end
end
