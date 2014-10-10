inherited myInplaceEditor: TmyInplaceEditor
  Height = 328
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 478
    Height = 45
    Align = alTop
    Caption = 'Panel1'
    TabOrder = 0
    object E_Cell: TEdit
      Tag = 1
      Left = 0
      Top = 0
      Width = 121
      Height = 45
      Anchors = [akLeft, akTop, akBottom]
      BorderStyle = bsNone
      TabOrder = 0
      Text = 'E_Cell'
      OnKeyDown = E_CellKeyDown
    end
  end
end
