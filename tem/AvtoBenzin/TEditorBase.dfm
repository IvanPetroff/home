object EditorBase: TEditorBase
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  TabOrder = 0
  OnExit = FrameExit
  OnResize = FrameResize
  object Edit1: TEdit
    Left = 0
    Top = 0
    Width = 121
    Height = 21
    TabStop = False
    AutoSize = False
    BorderStyle = bsNone
    Color = clYellow
    TabOrder = 0
    Text = 'Edit1'
    Visible = False
    OnKeyDown = Edit1KeyDown
    OnKeyPress = Edit1KeyPress
  end
  object StaticText1: TStaticText
    Left = 0
    Top = 0
    Width = 58
    Height = 17
    AutoSize = False
    Caption = 'StaticText1'
    Color = clBtnFace
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = StaticText1Click
  end
  object DBGridEh1: TDBGridEh
    Left = 0
    Top = 40
    Width = 161
    Height = 65
    Flat = False
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Visible = False
  end
end
