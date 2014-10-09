object Form1: TForm1
  Left = 369
  Top = 168
  Width = 887
  Height = 591
  Caption = 'Отпуск топлива'
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
    Width = 879
    Height = 129
    Align = alTop
    Caption = 'Реквизиты документа'
    Color = clBtnFace
    ParentColor = False
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 76
      Width = 26
      Height = 13
      Caption = 'Дата'
    end
    object Label2: TLabel
      Left = 160
      Top = 24
      Width = 70
      Height = 13
      Caption = 'Код операции'
    end
    object Label3: TLabel
      Left = 320
      Top = 24
      Width = 98
      Height = 13
      Caption = 'Склад-отправитель'
    end
    object Label4: TLabel
      Left = 432
      Top = 24
      Width = 91
      Height = 13
      Caption = 'Склад-получатель'
    end
    object Label5: TLabel
      Left = 160
      Top = 76
      Width = 63
      Height = 13
      Caption = 'Примечание'
    end
    object Label6: TLabel
      Left = 8
      Top = 24
      Width = 126
      Height = 13
      Caption = 'Регистрационный номер'
    end
    object DateTimePicker1: TDateTimePicker
      Left = 8
      Top = 96
      Width = 89
      Height = 21
      CalAlignment = dtaLeft
      Date = 41920.3902395486
      Time = 41920.3902395486
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 0
    end
    object CB_KodOper: TComboBox
      Left = 160
      Top = 44
      Width = 153
      Height = 22
      Style = csDropDownList
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ItemHeight = 14
      ParentFont = False
      TabOrder = 1
    end
    object E_SklFrom: TEdit
      Left = 320
      Top = 44
      Width = 105
      Height = 21
      TabOrder = 2
      Text = '80.09'
    end
    object Edit2: TEdit
      Left = 432
      Top = 44
      Width = 105
      Height = 21
      TabOrder = 3
      Text = '80.08'
    end
    object Edit3: TEdit
      Left = 160
      Top = 96
      Width = 377
      Height = 21
      TabOrder = 4
    end
    object ComboBox1: TComboBox
      Left = 8
      Top = 44
      Width = 141
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      Text = 'ComboBox1'
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 129
    Width = 879
    Height = 64
    Align = alTop
    Caption = 'GroupBox2'
    TabOrder = 1
    object Label7: TLabel
      Left = 8
      Top = 28
      Width = 63
      Height = 13
      Caption = 'Вид топлива'
    end
    object Label8: TLabel
      Left = 392
      Top = 28
      Width = 54
      Height = 13
      Caption = 'Плотность'
    end
    object CB_Benzin: TComboBox
      Left = 80
      Top = 24
      Width = 297
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
    end
    object CB_Dense: TComboBox
      Left = 452
      Top = 24
      Width = 81
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = '0.805'
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 193
    Width = 879
    Height = 371
    Align = alClient
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 2
    object Splitter1: TSplitter
      Left = 663
      Top = 0
      Width = 5
      Height = 371
      Cursor = crHSplit
      Align = alRight
      Color = clHighlight
      ParentColor = False
    end
    object GroupBox3: TGroupBox
      Left = 0
      Top = 0
      Width = 663
      Height = 371
      Align = alClient
      Caption = 'GroupBox3'
      TabOrder = 0
      object DBG_Sod: TDBGridEh
        Left = 2
        Top = 15
        Width = 659
        Height = 354
        Align = alBottom
        DataSource = DS_Sod
        Flat = True
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
        OnKeyPress = DBG_SodKeyPress
        OnMouseDown = DBG_SodMouseDown
        Columns = <
          item
            EditButtons = <>
            FieldName = 'IZD'
            Footers = <>
            Title.Caption = 'Гос. номер'
          end
          item
            Color = 12713921
            EditButtons = <>
            FieldName = 'KOL_TREB'
            Footers = <>
            Title.Caption = 'Кол-во литров'
            Width = 81
          end
          item
            EditButtons = <>
            FieldName = 'KOD_MAT'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'NZ_ZAG'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'DOP_KOD'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'KOL'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'CENA'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'CENA_F'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'SHPZ'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'DTR'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'USR'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'NZ'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'AKC'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'PRC_NDS'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'S_NDS'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'RSORT'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'PRIM'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'NZ_PRIH'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'DCE'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'NZ_CEH'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'BS'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'D_BS'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'D_GAR'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'PRIZN'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'OLD_KOD_MAT'
            Footers = <>
          end
          item
            EditButtons = <>
            FieldName = 'OLD_DOP_KOD'
            Footers = <>
          end>
      end
      object Panel4: TPanel
        Left = 180
        Top = 120
        Width = 185
        Height = 41
        Caption = 'Panel4'
        TabOrder = 1
        object Edit1: TEdit
          Left = 28
          Top = 8
          Width = 121
          Height = 21
          AutoSelect = False
          TabOrder = 0
          Text = 'Edit1'
        end
      end
    end
    object GroupBox4: TGroupBox
      Left = 668
      Top = 0
      Width = 211
      Height = 371
      Align = alRight
      Caption = 'Список автомобилей'
      TabOrder = 1
      object P_SloAvto: TPanel
        Left = 2
        Top = 15
        Width = 207
        Height = 354
        Align = alClient
        BevelOuter = bvNone
        Caption = 'P_SloAvto'
        TabOrder = 0
        object DBG_SloAvto: TDBGridEh
          Left = 0
          Top = 0
          Width = 207
          Height = 322
          Align = alClient
          AutoFitColWidths = True
          Color = 11075583
          DataSource = DS_SloAvto
          FixedColor = 13553075
          Flat = True
          FooterColor = clWindow
          FooterFont.Charset = DEFAULT_CHARSET
          FooterFont.Color = clWindowText
          FooterFont.Height = -11
          FooterFont.Name = 'MS Sans Serif'
          FooterFont.Style = []
          Options = [dgTitles, dgColumnResize, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
          OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghAutoSortMarking, dghDialogFind]
          ReadOnly = True
          RowHeight = 18
          SortLocal = True
          STFilter.Visible = True
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          OnApplyFilter = DBG_SloAvtoApplyFilter
          OnDblClick = DBG_SloAvtoDblClick
          OnDrawColumnCell = DBG_SloAvtoDrawColumnCell
          OnMouseMove = DBG_SloAvtoMouseMove
          OnSortMarkingChanged = DBG_SloAvtoSortMarkingChanged
          Columns = <
            item
              EditButtons = <>
              Footers = <>
              Width = 30
            end
            item
              EditButtons = <>
              FieldName = 'MARKA'
              Footers = <>
              Title.Caption = 'Марка'
              Title.TitleButton = True
              Width = 95
            end
            item
              EditButtons = <>
              FieldName = 'N_GAI'
              Footers = <>
              Title.Caption = 'Гос. номер'
              Title.TitleButton = True
              Width = 68
            end>
        end
        object Panel3: TPanel
          Left = 48
          Top = 92
          Width = 25
          Height = 24
          Caption = '<<'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          Visible = False
        end
        object Panel2: TPanel
          Left = 0
          Top = 322
          Width = 207
          Height = 32
          Align = alBottom
          TabOrder = 0
          object SpeedButton1: TSpeedButton
            Left = 8
            Top = 4
            Width = 191
            Height = 24
            Anchors = [akLeft, akTop, akRight]
            Caption = '<< Добавить'
            OnClick = SpeedButton1Click
          end
        end
      end
    end
  end
  object db: TOraSession
    Options.Direct = True
    Left = 628
    Top = 24
  end
  object OraQuery1: TOraQuery
    Session = db
    Left = 660
    Top = 24
  end
  object OraDataSource1: TOraDataSource
    Left = 692
    Top = 24
  end
  object Q_KodOper: TOraQuery
    Session = db
    SQL.Strings = (
      
        'select lpad(op,3,'#39' '#39')||'#39' - '#39'||naim txt from asu_spr_op where wid' +
        '_dok=46 order by naim')
    Left = 196
    Top = 4
  end
  object OraQuery2: TOraQuery
    Session = db
    SQL.Strings = (
      
        'select lpad(op,3,'#39' '#39')||'#39' - '#39'||naim txt from asu_spr_op where wid' +
        '_dok=46 order by naim')
    Left = 196
    Top = 4
  end
  object Q_Benzin: TOraQuery
    Session = db
    SQL.Strings = (
      
        'select o.mestoh||'#39'-'#39'||s.naim||'#39' '#39'||s.marka||'#39' ['#39'||s.m_kod||'#39']'#39' t' +
        'xt from asu_ost_mat o, (select m_kod,naim,marka from asu_slo_mt ' +
        'where naim like '#39'%БЕНЗИН%'#39' or naim like '#39'%ТОПЛИВО%'#39') s '
      'where o.skl=:skl and o.m_kod=s.m_kod')
    Left = 164
    Top = 136
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'skl'
      end>
  end
  object Q_Sod: TOraQuery
    Session = db
    SQL.Strings = (
      'select * from asu_sod_dok --where nz_zag=:nz_zag'
      'where rownum<10')
    CachedUpdates = True
    Left = 136
    Top = 261
  end
  object DS_Sod: TOraDataSource
    DataSet = Q_Sod
    Left = 172
    Top = 261
  end
  object Q_SloAvto: TOraQuery
    Session = db
    SQL.Strings = (
      'select marka, n_gai, id from asu_slo_avto')
    FetchAll = True
    Left = 616
    Top = 265
  end
  object DS_SloAvto: TOraDataSource
    DataSet = Q_SloAvto
    Left = 652
    Top = 265
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 276
    Top = 273
  end
end
