inherited EditorGrid: TEditorGrid
  inherited EditText: TEdit
    OnChange = EditTextChange
  end
  object Grid: TStringGrid
    Left = 0
    Top = 120
    Width = 320
    Height = 120
    TabStop = False
    ColCount = 1
    DefaultColWidth = 256
    DefaultRowHeight = 16
    DefaultDrawing = False
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goColSizing, goRowSelect]
    TabOrder = 2
    OnDblClick = GridDblClick
    OnDrawCell = GridDrawCell
    OnKeyDown = GridKeyDown
  end
end
