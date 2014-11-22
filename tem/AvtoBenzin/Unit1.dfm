object Form1: TForm1
  Left = 365
  Top = 163
  Width = 777
  Height = 555
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
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 769
    Height = 527
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 0
    object TabSheet3: TTabSheet
      Caption = 'Колонка1'
      ImageIndex = 2
      inline FraGasPoint1: TFraGasPoint
        Width = 761
        Height = 499
        Align = alClient
        inherited Panel4: TPanel
          Width = 761
        end
        inherited GroupBox3: TGroupBox
          Width = 761
          Height = 458
          inherited DBG_Sod: TDBGridEh
            Width = 757
            Height = 441
          end
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Колонка2'
      ImageIndex = 1
    end
  end
  object db: TOraSession
    Options.Direct = True
    Left = 628
    Top = 24
  end
end
