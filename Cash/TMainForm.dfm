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
    TabOrder = 1
    inherited MemTableEh1: TMemTableEh
      ExternalMemData = MemTableEh1
    end
  end
  object MemTableEh1: TMemTableEh
    Active = True
    Params = <>
    Left = 128
    Top = 40
    object MemTableEh1id: TIntegerField
      FieldName = 'id'
    end
    object MemTableEh1dat: TDateField
      FieldName = 'dat'
    end
    object MemTableEh1naim: TStringField
      FieldName = 'naim'
      Size = 128
    end
    object MemTableEh1cat: TStringField
      FieldName = 'cat'
      Size = 32
    end
    object MemTableEh1kol: TFloatField
      FieldName = 'kol'
    end
    object MemTableEh1cena: TFloatField
      FieldName = 'cena'
    end
    object MemTableEh1stoim: TFloatField
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
      end
    end
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 160
    Top = 40
  end
end
