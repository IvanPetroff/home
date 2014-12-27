inherited FraPrcFact: TFraPrcFact
  inherited DBGridEh1: TDBGridEh
    FooterRowCount = 1
    SumList.Active = True
  end
  inherited DS: TOraQuery
    SQL.Strings = (
      'select '
      '  m.uch, '
      '  m.unizak, '
      '  (select pzak from asu_zagzak where unizak=m.unizak) pzak,'
      '  (select izd from asu_zagzak where unizak=m.unizak) izd, '
      '  to_number(m.prc) prc from  '
      '('
      'select extractvalue(column_value,'#39'/ROW/UCH'#39') uch'
      '      ,extractvalue(column_value,'#39'/ROW/UNIZAK'#39') unizak'
      '      ,extractvalue(column_value,'#39'/ROW/PRC'#39') prc'
      'from table(xmlsequence(xmltype(:x).extract('#39'/ROWSET/ROW'#39')))'
      ') m')
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'x'
      end>
  end
end
