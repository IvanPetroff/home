inherited FraFactNew: TFraFactNew
  inherited DS: TOraQuery
    SQL.Strings = (
      'select extractvalue(column_value,'#39'/ROW/UCH'#39') uch'
      '      ,extractvalue(column_value,'#39'/ROW/UNIZAK'#39') unizak'
      '      ,extractvalue(column_value,'#39'/ROW/PRC'#39') prc'
      
        'from table(xmlsequence(class_spreadlist.get_prc_trud#('#39'F'#39', :ceh,' +
        ' :d_beg, :d_end).extract('#39'/ROWSET/ROW'#39')))')
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'ceh'
      end
      item
        DataType = ftUnknown
        Name = 'd_beg'
      end
      item
        DataType = ftUnknown
        Name = 'd_end'
      end>
  end
end
