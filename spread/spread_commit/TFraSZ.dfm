inherited FraSZ: TFraSZ
  inherited DS: TOraQuery
    SQL.Strings = (
      'select extractvalue(column_value,'#39'/ROW/KOD'#39') kod'
      '      ,extractvalue(column_value,'#39'/ROW/NAIM'#39') naim'
      '      ,extractvalue(column_value,'#39'/ROW/R_SORT'#39') r_sort'
      '      ,extractvalue(column_value,'#39'/ROW/UNIZAK'#39') unizak'
      '      ,extractvalue(column_value,'#39'/ROW/PZAK'#39') pzak'
      '      ,extractvalue(column_value,'#39'/ROW/IZD'#39') izd'
      '      ,extractvalue(column_value,'#39'/ROW/KOL'#39') kol'
      '      ,extractvalue(column_value,'#39'/ROW/KOL_CENA'#39') kol_cena'
      
        'from table(xmlsequence( class_spreadlist(:1).getSpreadList(xmlty' +
        'pe(:x)).extract('#39'/ROWSET/ROW'#39')))')
    ParamData = <
      item
        DataType = ftUnknown
        Name = '1'
      end
      item
        DataType = ftString
        Name = 'x'
        Value = ''
      end>
  end
end
