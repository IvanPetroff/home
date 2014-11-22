inherited FraTankGasolineList: TFraTankGasolineList
  Width = 200
  Height = 144
  OnMouseWheel = FrameMouseWheel
  object CB: TComboBox
    Left = 16
    Top = 8
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object Query: TOraQuery
    SQL.Strings = (
      
        'select distinct '#39'π '#39'||nvl(o.mestoh,'#39'<???>'#39')||'#39'; / '#39'||'#39' ['#39'||s.m_k' +
        'od||'#39'] '#39'||s.naim||'#39' '#39'||s.marka||'#39' '#39'||s.prim txt, o.mestoh, s.m_k' +
        'od '
      
        'from asu_ost_mat o, (select m_kod,naim,marka,prim from asu_slo_m' +
        't where naim like '#39'%¡≈Õ«»Õ%'#39' or naim like '#39'%“ŒœÀ»¬Œ%'#39') s '
      'where o.skl=:skl and o.m_kod=s.m_kod')
    Left = 68
    Top = 112
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'skl'
      end>
  end
end
