//门派auto_pfm
#include <ansi.h>

void attack_action(object me,object victim,object weapon,int damage)
{
	if( !me || !victim || !me->is_killing(victim->query("id")) )
		return;
	if( me->query("force")<80 )
		return;
	if( !me->query_temp("pfm_action") )
		return;	
	switch(me->query_temp("pfm_action"))
	{
		case "lg_dhwl"       : ("/daemon/class/dragon/fengbo-cha/dhwl.c")->dhwl(me,victim,weapon,damage);break;
		case "lg_fan"     : ("/daemon/class/dragon/huntian-hammer/fan.c")->fan(me,victim,weapon,damage);break;
		case "xs_ningxie" : ("/daemon/class/xueshan/bingpo-blade/ningxie.c")->ningxie_result(me,victim,weapon,damage);break;
		case "wdd_zxzx"   : ("/daemon/class/wdd/qixiu-jian/zxzx.c")->zxzx(me,victim,weapon,damage);break;
		case "hyd_fire"   : ("/daemon/class/kusong/huoyun-qiang/ji.c")->fire(me,victim,weapon,damage);break;
		case "psd_wang"   : ("/daemon/class/pansi/yinsuo-jinling/wang.c")->wang(me,victim,weapon,damage);break;
		case "puti_stlb"  : ("/daemon/class/puti/dao/stlb.c")->stlb(me,victim,weapon,damage);break;
		case "wzg_lpf"    : ("/daemon/class/zhenyuan/fumo-zhang/luan.c")->luanpifeng(me,victim,weapon,damage);break;
		default : return;
	}		
}