inherited F_SprQuestion: TF_SprQuestion
  Left = 497
  Top = 170
  Caption = 'F_SprQuestion'
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridEh1: TDBGridEh
    Left = 0
    Top = 0
    Width = 504
    Height = 242
    Align = alClient
    DataSource = OraDataSource1
    Flat = True
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'NAME'
        Footers = <>
        Title.Caption = 'Имя параметра'
        Width = 161
      end
      item
        EditButtons = <>
        FieldName = 'LABEL'
        Footers = <>
        Title.Caption = 'Название на экране'
        Width = 157
      end
      item
        EditButtons = <>
        FieldName = 'ORD'
        Footers = <>
        Title.Caption = 'Порядок'
      end
      item
        EditButtons = <>
        FieldName = 'ID'
        Footers = <>
      end
      item
        EditButtons = <>
        FieldName = 'USR'
        Footers = <>
        Width = 71
      end
      item
        EditButtons = <>
        FieldName = 'DAT'
        Footers = <>
        Width = 98
      end>
  end
  object OraDataSource1: TOraDataSource
    DataSet = OraQuery1
    Left = 80
    Top = 16
  end
  object OraQuery1: TOraQuery
    SQLInsert.Strings = (
      'begin'
      
        '  insert into asu_spr_question(name,label,ord) values(:name,:lab' +
        'el,:ord) returning name,label,ord,id,usr,dat into :name, :label,' +
        ' :ord, :id, :usr, :dat;'
      'end;')
    SQLDelete.Strings = (
      'begin'
      '  delete asu_spr_question where id=:old_id;'
      'end;')
    SQLUpdate.Strings = (
      'begin'
      '  update asu_spr_question set name=:name, label=:label, ord=:ord'
      '  where id=:old_id'
      
        '  returning name,label,ord,id,usr,dat into :name, :label, :ord, ' +
        ':id, :usr, :dat;'
      'end;')
    SQL.Strings = (
      'select * from asu_spr_question')
    Options.ReturnParams = True
    Active = True
    Left = 40
    Top = 16
  end
end
