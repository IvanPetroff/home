inherited FraGasPoint: TFraGasPoint
  Width = 817
  Height = 373
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 817
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label8: TLabel
      Left = 472
      Top = 12
      Width = 54
      Height = 13
      Caption = 'Плотность'
    end
    object CB_Dense: TComboBox
      Left = 532
      Top = 8
      Width = 81
      Height = 21
      Hint = 'Актуальная плотность топлива (кг/л)'
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = '0.805'
    end
    object E_SklFrom: TEdit
      Left = 624
      Top = 8
      Width = 49
      Height = 21
      Hint = 'Номер склада'
      Color = clInactiveBorder
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 1
      Text = '80.09'
    end
    inline FraTankGasolineList1: TFraTankGasolineList
      Left = 137
      Width = 328
      Height = 41
      Align = alLeft
      TabOrder = 2
      inherited CB: TComboBox
        Left = 8
        Width = 313
      end
    end
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 137
      Height = 41
      Align = alLeft
      BevelOuter = bvNone
      Caption = 'Цисцерна/Вид топлива'
      TabOrder = 3
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 41
    Width = 817
    Height = 332
    Align = alClient
    Caption = 'Журнал выдачи'
    TabOrder = 1
    object Edit1: TStaticText
      Left = 320
      Top = 80
      Width = 197
      Height = 17
      AutoSize = False
      Caption = 'Edit1'
      Color = clHighlight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      Visible = False
    end
    object DBG_Sod: TDBGridEh
      Left = 2
      Top = 15
      Width = 813
      Height = 315
      Align = alClient
      DataSource = DataSource1
      Flat = True
      FooterColor = clWindow
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -11
      FooterFont.Name = 'MS Sans Serif'
      FooterFont.Style = []
      OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind]
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      UseMultiTitle = True
      Columns = <
        item
          EditButtons = <>
          FieldName = 'nz'
          Footers = <>
          Visible = False
        end
        item
          EditButtons = <>
          FieldName = 'avto'
          Footers = <>
          Title.Caption = 'Автомобиль'
          Width = 240
        end
        item
          EditButtons = <>
          FieldName = 'kol_litre'
          Footers = <>
          Title.Caption = 'Кол-во|литров'
        end
        item
          EditButtons = <>
          FieldName = 'kol_kg'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Footers = <>
          Title.Caption = 'Кол-во|кг'
        end
        item
          EditButtons = <>
          FieldName = 'k_density'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Footers = <>
          Title.Caption = 'Плотность'
        end
        item
          EditButtons = <>
          FieldName = 'kod_mat'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Footers = <>
          Title.Caption = 'Код топлива'
          Width = 95
        end
        item
          EditButtons = <>
          FieldName = 'mestoh'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Footers = <>
          Title.Caption = 'Цисцерна'
          Width = 116
        end
        item
          EditButtons = <>
          FieldName = 'dat'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGray
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Footers = <>
        end>
    end
    inline EditAvto: TEditorGrid
      Left = 264
      Top = 128
      TabOrder = 2
    end
    inline EditSimple1: TEditSimple
      Left = 328
      Top = 32
      Width = 193
      Height = 81
      TabOrder = 3
    end
  end
  object Q_Sod: TOraQuery
    SQL.Strings = (
      'select * from asu_sod_dok --where nz_zag=:nz_zag'
      'where rownum<100')
    CachedUpdates = True
    Left = 80
    Top = 117
  end
  object DS_Sod: TOraDataSource
    DataSet = Q_Sod
    Left = 116
    Top = 117
  end
  object Q_listBenzin: TOraQuery
    SQL.Strings = (
      
        'select distinct '#39'№ '#39'||nvl(o.mestoh,'#39'<???>'#39')||'#39'; / '#39'||'#39' ['#39'||s.m_k' +
        'od||'#39'] '#39'||s.naim||'#39' '#39'||s.marka||'#39' '#39'||s.prim txt '
      
        'from asu_ost_mat o, (select m_kod,naim,marka,prim from asu_slo_m' +
        't where naim like '#39'%БЕНЗИН%'#39' or naim like '#39'%ТОПЛИВО%'#39') s '
      'where o.skl=:skl and o.m_kod=s.m_kod')
    Left = 140
    Top = 32
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'skl'
      end>
  end
  object Q_SloAvto: TOraQuery
    SQL.Strings = (
      'select marka, n_gai, id from asu_slo_avto')
    FetchAll = True
    Left = 80
    Top = 153
  end
  object MT: TMemTableEh
    FieldDefs = <>
    IndexDefs = <>
    Params = <>
    StoreDefs = True
    BeforeInsert = MTBeforeInsert
    AfterInsert = MTAfterInsert
    BeforePost = MTBeforePost
    Left = 80
    Top = 217
    object MemTableEh1nz: TIntegerField
      FieldName = 'nz'
    end
    object MemTableEh1avto: TStringField
      FieldName = 'avto'
      Size = 64
    end
    object MemTableEh1kol_kg: TFloatField
      FieldName = 'kol_kg'
    end
    object MemTableEh1kol_litre: TFloatField
      FieldName = 'kol_litre'
    end
    object MemTableEh1k_density: TFloatField
      FieldName = 'k_density'
    end
    object MemTableEh1kod_mat: TStringField
      FieldName = 'kod_mat'
      Size = 32
    end
    object MTmestoh: TStringField
      FieldName = 'mestoh'
      Size = 32
    end
    object MTdat: TDateTimeField
      FieldName = 'dat'
    end
  end
  object DataSource1: TDataSource
    DataSet = MT
    Left = 112
    Top = 217
  end
end
