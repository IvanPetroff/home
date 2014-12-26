inherited FraSZ: TFraSZ
  inherited DS: TOraQuery
    SQL.Strings = (
      'select '
      '  t.kod, '
      '  (select naim from asu_slo_mt where m_kod=t.kod) naim,'
      '  t.r_sort, '
      '  t.unizak, '
      '  (select pzak from asu_zagzak where unizak=t.unizak) pzak, '
      '  (select izd from asu_zagzak where unizak=t.unizak) izd, '
      '  sum(t.kol) kol, '
      '  sum(t.kol)*t.cena kol_cena'
      'from ('
      
        'select s.kod, s.r_sort, m2.unizak unizak, s.kol*s.kol_mat*m2.prc' +
        '/100 kol, s.cena'
      
        'from asu_more_attr m1, (select extractvalue(column_value,'#39'/ROW/U' +
        'CH'#39') uch'
      '      ,extractvalue(column_value,'#39'/ROW/UNIZAK'#39') unizak'
      '      ,extractvalue(column_value,'#39'/ROW/PRC'#39') prc'
      'from table(xmlsequence(xmltype(:x).extract('#39'/ROWSET/ROW'#39')))'
      ') m2, asu_spis_dok s'
      'where s.id=m1.key'
      
        'and m1.cat='#39'SPIS_DOK'#39' and m1.name_attr='#39'SPREAD'#39' and m1.val_num=:' +
        '1'
      'and nvl(m1.val_txt,'#39'-'#39')=nvl(m2.uch,'#39'-'#39')'
      ') t'
      'group by kod,unizak, cena, r_sort')
    ParamData = <
      item
        DataType = ftString
        Name = 'x'
        Value = ''
      end
      item
        DataType = ftUnknown
        Name = '1'
      end>
  end
end
