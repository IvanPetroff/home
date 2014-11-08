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
    ColCount = 2
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
    ColWidths = (
      132
      121)
  end
  object MemTableEh1: TMemTableEh
    Params = <>
    Left = 112
    Top = 56
  end
end
