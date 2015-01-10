inherited F_Person: TF_Person
  Left = 478
  Top = 144
  Width = 824
  Height = 609
  Caption = 'Карточка пациента'
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 816
    Height = 544
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Персональные данные'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 808
        Height = 225
        Align = alTop
        TabOrder = 0
        object Label2: TLabel
          Left = 8
          Top = 104
          Width = 31
          Height = 13
          Caption = 'Адрес'
        end
        object Label3: TLabel
          Left = 8
          Top = 176
          Width = 45
          Height = 13
          Caption = 'Телефон'
        end
        object Label4: TLabel
          Left = 248
          Top = 176
          Width = 28
          Height = 13
          Caption = 'E-mail'
        end
        object Label5: TLabel
          Left = 8
          Top = 60
          Width = 79
          Height = 13
          Caption = 'Дата рождения'
        end
        object Label8: TLabel
          Left = 144
          Top = 60
          Width = 20
          Height = 13
          Caption = 'Пол'
        end
        object Label1: TLabel
          Left = 8
          Top = 12
          Width = 36
          Height = 13
          Caption = 'Ф.И.О.'
        end
        object M_ADDR: TMemo
          Left = 8
          Top = 120
          Width = 465
          Height = 49
          Lines.Strings = (
            'Memo1')
          OEMConvert = True
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 0
        end
        object E_TEL: TEdit
          Left = 8
          Top = 192
          Width = 233
          Height = 21
          ReadOnly = True
          TabOrder = 1
          Text = 'E_TEL'
        end
        object E_EMAIL: TEdit
          Left = 248
          Top = 192
          Width = 225
          Height = 21
          ReadOnly = True
          TabOrder = 2
          Text = 'E_EMAIL'
        end
        object E_D_BIRTH: TEdit
          Left = 8
          Top = 76
          Width = 121
          Height = 21
          ReadOnly = True
          TabOrder = 3
          Text = 'E_D_BIRTH'
        end
        object E_SEX: TEdit
          Left = 144
          Top = 76
          Width = 33
          Height = 21
          ReadOnly = True
          TabOrder = 4
          Text = 'E_SEX'
        end
        object E_FIO: TEdit
          Left = 8
          Top = 28
          Width = 465
          Height = 21
          ReadOnly = True
          TabOrder = 5
          Text = 'E_FIO'
        end
      end
      object GroupBox5: TGroupBox
        Left = 0
        Top = 225
        Width = 808
        Height = 40
        Align = alTop
        TabOrder = 1
        object Label7: TLabel
          Left = 256
          Top = 12
          Width = 85
          Height = 13
          Caption = 'Дата изменения'
        end
        object Label6: TLabel
          Left = 8
          Top = 12
          Width = 93
          Height = 13
          Caption = 'Дата регистрации'
        end
        object E_DAT: TEdit
          Left = 352
          Top = 12
          Width = 121
          Height = 21
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 0
          Text = 'Edit5'
        end
        object E_D_REG: TEdit
          Left = 112
          Top = 12
          Width = 121
          Height = 21
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 1
          Text = 'E_D_REG'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Симптомы'
      ImageIndex = 1
      object GroupBox2: TGroupBox
        Left = 0
        Top = 0
        Width = 808
        Height = 516
        Align = alClient
        TabOrder = 0
        object DBG_Simptoms: TDBGridEh
          Left = 2
          Top = 15
          Width = 804
          Height = 499
          Align = alClient
          DataSource = DS_Simptoms
          Flat = True
          FooterColor = clWindow
          FooterFont.Charset = DEFAULT_CHARSET
          FooterFont.Color = clWindowText
          FooterFont.Height = -11
          FooterFont.Name = 'MS Sans Serif'
          FooterFont.Style = []
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          Columns = <
            item
              EditButtons = <>
              FieldName = 'ROWNUM'
              Footers = <>
              Title.Caption = ' '
              Width = 37
            end
            item
              EditButtons = <>
              FieldName = 'LABEL'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              Footers = <>
              Title.Caption = 'Симптом'
              Width = 382
            end
            item
              EditButtons = <>
              FieldName = 'ANS'
              Footers = <>
              Title.Caption = 'Оценка (0-10)'
              Width = 84
            end
            item
              EditButtons = <>
              FieldName = 'NAME'
              Footers = <>
              Visible = False
              Width = 28
            end
            item
              EditButtons = <>
              FieldName = 'ID'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'ORD'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'USR'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'DAT'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'SEX'
              Footers = <>
              Visible = False
            end>
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Дополнительные сведения'
      ImageIndex = 2
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 808
        Height = 516
        Align = alClient
        TabOrder = 0
        object DBG_Other: TDBGridEh
          Left = 2
          Top = 15
          Width = 804
          Height = 499
          Align = alClient
          DataSource = DS_Other
          Flat = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          FooterColor = clWindow
          FooterFont.Charset = DEFAULT_CHARSET
          FooterFont.Color = clWindowText
          FooterFont.Height = -11
          FooterFont.Name = 'MS Sans Serif'
          FooterFont.Style = []
          Options = [dgEditing, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          ReadOnly = True
          RowLines = 3
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          Columns = <
            item
              EditButtons = <>
              FieldName = 'ROWNUM'
              Footers = <>
              Width = 30
            end
            item
              EditButtons = <>
              FieldName = 'LABEL'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              Footers = <>
              Title.Caption = 'Вопрос'
              Width = 206
            end
            item
              EditButtons = <>
              FieldName = 'ANS'
              Footers = <>
              Title.Caption = 'Ответ'
              Width = 473
            end
            item
              EditButtons = <>
              FieldName = 'NAME'
              Footers = <>
              Visible = False
              Width = 35
            end
            item
              EditButtons = <>
              FieldName = 'ID'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'ORD'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'USR'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'DAT'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'SEX'
              Footers = <>
              Visible = False
            end
            item
              EditButtons = <>
              FieldName = 'TIP'
              Footers = <>
              Visible = False
            end>
        end
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 544
    Width = 816
    Height = 38
    Align = alBottom
    TabOrder = 1
    object B_Edit: TSpeedButton
      Left = 8
      Top = 10
      Width = 113
      Height = 22
      Caption = 'Редактировать'
      Flat = True
      OnClick = B_EditClick
    end
    object B_Save: TSpeedButton
      Left = 128
      Top = 10
      Width = 113
      Height = 22
      Caption = 'Сохранить'
      Enabled = False
      Flat = True
      OnClick = B_SaveClick
    end
    object B_Cancel: TSpeedButton
      Left = 248
      Top = 10
      Width = 113
      Height = 22
      Caption = 'Отмена'
      Enabled = False
      Flat = True
      OnClick = B_CancelClick
    end
  end
  object Q_Simptoms: TOraQuery
    SQL.Strings = (
      'select rownum, t.*, cast(null as varchar2(2)) ans '
      'from (select * from syn_spr_question'
      'where tip='#39'N'#39
      'order by ord) t')
    Active = True
    Left = 156
    Top = 32
  end
  object DS_Simptoms: TOraDataSource
    DataSet = Q_Simptoms
    Left = 196
    Top = 32
  end
  object Q_Other: TOraQuery
    SQL.Strings = (
      'select rownum, t.*, cast(null as varchar2(200)) ans '
      'from (select * from syn_spr_question'
      'where tip='#39'V'#39
      'order by ord) t')
    Active = True
    Left = 348
    Top = 88
  end
  object DS_Other: TOraDataSource
    DataSet = Q_Other
    Left = 380
    Top = 88
  end
  object Q_Person: TOraQuery
    SQL.Strings = (
      'select '
      'id'
      ',fio'
      ',sex'
      ',d_birth'
      ',addr'
      ',tel'
      ',email'
      ',to_char(d_reg,'#39'dd.mm.yyyy hh24:mi'#39') d_reg'
      ',usr'
      ',to_char(dat,'#39'dd.mm.yyyy hh24:mi'#39') dat'
      ',tel2'
      ',fam'
      ',name1'
      ',name2'
      ',city_id'
      ',street'
      ',house'
      ',apartment'
      ''
      'from syn_person'
      'where id=:id')
    Left = 40
    Top = 80
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'id'
      end>
  end
  object DS_Person: TOraDataSource
    DataSet = Q_Person
    Left = 72
    Top = 80
  end
  object Q_Quest_data: TOraQuery
    SQL.Strings = (
      
        'select spr_question_id, max(ans_n) keep(dense_rank first order b' +
        'y dat desc) ans'
      'from syn_quest_data_n where person_id=:id'
      'group by spr_question_id'
      'union all'
      
        'select spr_question_id, max(ans_v) keep(dense_rank first order b' +
        'y dat desc) ans'
      'from syn_quest_data_v where person_id=:id'
      'group by spr_question_id')
    Left = 228
    Top = 80
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'id'
      end>
  end
end
