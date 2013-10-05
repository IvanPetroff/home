object Form1: TForm1
  Left = 228
  Top = 138
  BorderStyle = bsDialog
  Caption = 'Быстрый счёт'
  ClientHeight = 597
  ClientWidth = 256
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 256
    Height = 578
    ActivePage = TS_Game
    Align = alClient
    TabOrder = 0
    OnChanging = PageControl1Changing
    object TS_Game: TTabSheet
      Caption = 'Игра'
      object PB: TPaintBox
        Left = 64
        Top = 140
        Width = 128
        Height = 69
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -37
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        OnPaint = PBPaint
      end
      object GB_Info: TGroupBox
        Left = 0
        Top = 81
        Width = 248
        Height = 57
        Align = alTop
        Caption = 'Очки'
        TabOrder = 0
        object L_Count: TLabel
          Left = 8
          Top = 24
          Width = 13
          Height = 23
          Caption = '0'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object L_Add: TLabel
          Left = 176
          Top = 16
          Width = 39
          Height = 23
          Caption = '+10'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 248
        Height = 81
        Align = alTop
        TabOrder = 1
        object SB_Start: TSpeedButton
          Left = 8
          Top = 16
          Width = 81
          Height = 22
          Caption = 'Старт'
          OnClick = SB_StartClick
        end
        object SB_Stop: TSpeedButton
          Left = 96
          Top = 16
          Width = 81
          Height = 22
          Caption = 'Стоп'
          Enabled = False
          OnClick = SB_StopClick
        end
        object Label1: TLabel
          Left = 8
          Top = 52
          Width = 31
          Height = 13
          Caption = 'Игрок'
        end
        object CB_Name: TComboBox
          Left = 48
          Top = 48
          Width = 185
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 0
        end
      end
      object GB_Answer: TGroupBox
        Left = 0
        Top = 494
        Width = 248
        Height = 56
        Align = alBottom
        Caption = 'Ответ'
        TabOrder = 2
        object E_Answer: TEdit
          Left = 8
          Top = 16
          Width = 233
          Height = 31
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnKeyDown = E_AnswerKeyDown
        end
      end
    end
    object TS_Log: TTabSheet
      Caption = 'Рекорды'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 248
        Height = 550
        Align = alClient
        ColCount = 3
        RowCount = 2
        TabOrder = 0
        ColWidths = (
          20
          134
          64)
      end
    end
  end
  object msg: TStatusBar
    Left = 0
    Top = 578
    Width = 256
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer1Timer
    Left = 64
    Top = 152
  end
end
