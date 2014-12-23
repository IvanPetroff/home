select (select naim from asu_slo_mt where m_kod=s.kod), kod, r_sort, kol*t.prc/100, (select pzak||' / '||izd from asu_zagzak where unizak=t.unizak), t.uch
--select sum(kol*t.prc/100)
from (
select sum(s.kol*s.kol_mat) kol, s.kod, s.r_sort, m.val_txt uch
from asu_spis_dok s, asu_more_attr m 
where s.id=m.key and m.cat='SPIS_DOK' and m.name_attr='SPREAD' and s.skl like '8.%' /*and d_ceh>='01-11-2014' and d_ceh<='30-11-2014'*/
group by kod, r_sort, m.val_txt 
) s, (select dce0 uch, dce1 xxx, na_se unizak, na_izd prc from table( admdba.get_prc_trud_for_unz( '8', '01-11-2014', '30-11-2014', 'N'))) t
where s.uch=t.uch
