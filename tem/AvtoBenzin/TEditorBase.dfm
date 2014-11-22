object EditorBase: TEditorBase
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  TabOrder = 0
  Visible = False
  OnExit = FrameExit
  OnMouseWheel = FrameMouseWheel
  object EditText: TEdit
    Left = 0
    Top = 0
    Width = 121
    Height = 21
    TabStop = False
    AutoSize = False
    BorderStyle = bsNone
    Color = clYellow
    TabOrder = 0
    Visible = False
    OnKeyDown = EditTextKeyDown
    OnKeyPress = EditTextKeyPress
  end
  object ViewText: TStaticText
    Left = 0
    Top = 0
    Width = 58
    Height = 17
    AutoSize = False
    Color = clBtnFace
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = ViewTextClick
  end
  object TabInterceptor: TEdit
    Left = 40
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'TabInterceptor'
    OnEnter = TabInterceptorEnter
  end
end
