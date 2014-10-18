object EditorBase: TEditorBase
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  TabOrder = 0
  OnExit = FrameExit
  OnMouseWheel = FrameMouseWheel
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
  object Grid: TStringGrid
    Left = 0
    Top = 56
    Width = 320
    Height = 120
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 2
  end
end
