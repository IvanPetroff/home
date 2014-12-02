declare 
procedure chk(b boolean) is
    begin
      if (b = false) then
        raise_application_error(-20001,'!');
      end if;
    end;

procedure test1 is
    obj test_tSklDok_core:= test_tSklDok_core(null,null, null, null);
    s varchar2(100);
    begin
      s := '<doc><zag></zag><sod></sod></doc>';
    
      obj.setxml(XMLtype(s));
      chk( obj.xml.getstringval() = obj.xml.getstringval());
      chk( obj.xml.getstringval() = XMLtype(s).getstringval());
    end;

procedure test2 is
    obj test_tSklDok_core:= test_tSklDok_core(null,null,null,null);
    s varchar2(100);
    begin
      s := '<doc><zag></zag><sod></sod></doc>';
    
      obj.setxml(XMLtype(s));
      chk( obj.xml.getstringval() = obj.xml.getstringval());
      chk( obj.xml.getstringval() = XMLtype(s).getstringval());
      chk( '<zag/>'||chr(10) = obj.xmlZag.getstringval());
      chk( '<sod/>'||chr(10) = obj.xmlSod.getstringval());
    end;

procedure test_new_dok is
    obj test_tSklDok_core:= test_tSklDok_core(null,null,null,null);
    s varchar2(100);
    begin
      s := '<doc><zag></zag><sod></sod></doc>';
    obj := test_tSklDok_core(null,null,null,null);
    
      obj.newDok(XMLtype(s));
      chk( obj.xml.getstringval() = XMLtype(s).getstringval());
    end;

procedure test_extract_nz_dok is
    obj test_tSklDok_core:= test_tSklDok_core(null,null,null,null);
    s varchar2(100);
    begin
      s := '<doc nz="123"><zag></zag><sod></sod></doc>';
      obj := test_tSklDok_core(null,null,null,null);
    
      chk( obj.getDokNZ(XMLtype(s)) = 123);
    end;

begin
  test1;
  test2;
  test_new_dok;
  test_extract_nz_dok;
null;
end;
