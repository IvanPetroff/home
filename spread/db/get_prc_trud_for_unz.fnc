create or replace function admdba.get_prc_trud_for_unz(p_ceh varchar2, p_d0 date, p_d1 date,
    p_schema varchar2, p_last_id number default 99999999) return tab_tmp_conf is
--Расчет процентов распределения наряд-сдаточных по изделиям
--Автор Засыпкин А.В.
  res tab_tmp_conf;
  r0 tab_tmp_conf;
  u varchar2(10);
  n_beg binary_integer;
  n_end binary_integer;
  sm real;
  kf real;
  r_beg binary_integer;
  
  MIN_PRC real := 15; --мин. порог значимости
  MAX_PRC real := 60;--порог суммы
begin

  if instr( p_schema, 'R') > 0 then --запуск распределения
    --расчет первичного распределения СПК на КПГ
    close_kpg.close_kpg_dce(pp_type => 'Т',
                          pp_dce => '%',
                          pp_unz => '%',
                          pp_prot => '-', 
                          pp_deb => false, 
                          p_deb_dce => '-', 
                          pp_spk_id => null, 
                          pp_sql => 'select distinct n.spk_id
from asu_sde n where n.type=''Д'' and nvl(n.spk_id,0)>0 and n.id<'''||p_last_id||''' and
nvl(n.kol,0)>0 and pri in (''0'',''1'',''4'') and izg='''||p_ceh||''' and
n.dat_izg>=to_date('''||to_char(p_d0,'dd-mm-yyyy')||''',''dd-mm-yyyy'') and 
n.dat_izg<=to_date('''||to_char(p_d1,'dd-mm-yyyy')||''',''dd-mm-yyyy'')
order by 1');
  end if;

  res := tab_tmp_conf();

  if instr( p_schema, 'N') > 0 then --расчет для нормы
    select str_tmp_conf( uch, null, unz, prc) bulk collect into r0
      from (select unz,trim(uch) uch, 
          trunc(tr/SUM(tr) OVER (PARTITION BY uch ORDER BY unz RANGE between UNBOUNDED PRECEDING and 
            UNBOUNDED following),4) * 100 prc
        from (select r.dce1 unz, trim(substr(n.stat,14,5)) uch,
            sum(r.na_izd*(nvl(n.t_pz,0)+nvl(n.t_st*n.kol,0))/nvl(n.c_st,1))  tr
          from table( close_kpg.get_saved_rasp(0)) r, sde n
          where r.dce1>'0' and r.na_se=n.spk_id and n.type='Д' and n.id<p_last_id and
          nvl(n.kol,0)>0 and pri in ('0','1','4') and izg=p_ceh  and 
          n.dat_izg>=p_d0 and n.dat_izg<=p_d1
          --and substr(n.stat,14,5)='234  '
          group by r.dce1, substr(n.stat,14,5)
        )
      ) --where prc>10
      order by uch,prc desc;
  end if;

  n_beg := r0.first; n_end := n_beg;
  while n_beg <= r0.last loop

    --расчет интервала участка
    u := r0(n_beg).dce0;
    n_end := null;
    for n in n_beg..r0.last loop
      if u != r0(n).dce0 then 
        n_end := n - 1;
        exit;
      end if;
    end loop;
    n_end := nvl( n_end, r0.last);
--dbms_output.put_line( n_beg||':'||n_end);

    if r0(n_beg).na_izd < MIN_PRC then --схема 3, max % меньше значимого
      --добираем до MAX_PRC
      r_beg := null;
      sm := 0;
      for n in n_beg..n_end loop
        res.Extend;
        if r_beg is null then
          r_beg := res.last;
        end if;
        res(res.last) := r0(n);
        res(res.last).dce1 := '3';
        sm := sm + r0(n).na_izd;
        exit when sm >= MAX_PRC;
      end loop;
    else
      --посмотрим, есть ли < MIN_PRC
      sm := null;
      for n in n_beg..n_end loop
        if r0(n).na_izd < MIN_PRC then
          sm := 1;
          exit;
        end if;
      end loop;
      
      if sm is null then --нет записей < MIN_PRC, схема1
        --берем все в лоб
        r_beg := null;
        sm := 0;
        for n in n_beg..n_end loop
          res.Extend;
          if r_beg is null then
            r_beg := res.last;
          end if;
          res(res.last) := r0(n);
          res(res.last).dce1 := '1';
          sm := sm + r0(n).na_izd;
        end loop;
      else --схема 2
        --добираем до MAX_PRC
        r_beg := null;
        sm := 0;
        for n in n_beg..n_end loop
          res.Extend;
          if r_beg is null then
            r_beg := res.last;
          end if;
          res(res.last) := r0(n);
          res(res.last).dce1 := '2';
          sm := sm + r0(n).na_izd;
          exit when sm >= MAX_PRC;
        end loop;
      end if;

    end if;
    
    --поднятие до 100%
    kf := 100 / sm; sm := 0;
    for n in r_beg..res.last-1 loop
      res(n).na_izd := trunc( res(n).na_izd * kf, 2);
      sm := sm + res(n).na_izd;
    end loop;
    --дополнение посл. строки до 100%
    res(res.last).na_izd := 100-sm;

    n_beg := n_end + 1;
  end loop;
    
--  res := r0;
  return( res);
end get_prc_trud_for_unz;
/
