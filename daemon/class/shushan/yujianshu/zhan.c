// 斩龙诀
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	int damage,p;
	string msg,*msgs,succ_msg;
	
	if( me->query_level()<30 )
    		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="蜀山派"
    	&& me->query("chushi/chushi_shushan")!="yes")
		return notify_fail("你不能使用这项技能！\n");
	if((int)me->query_skill("yujianshu",1) < 300
	 || me->query_skill_mapped("sword") != "yujianshu" )
        	return notify_fail("你的『御剑术』还不纯熟！\n");
	if((int)me->query("force") < 800 )
        	return notify_fail("你体内的内力不足。\n");
	if((int)me->query_skill("zuixian-wangyue",1) < 300)
        	return notify_fail("你的『醉仙望月步』还不纯熟！\n");
        if( time()<me->query_temp("shushan_zhanlong")+5 )
        	return notify_fail("绝招用多就不灵了。\n");	
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招『斩龙诀』？\n");
	
	p = me->query_skill("dodge")/10;
	me->add("force",-200);
	me->set_temp("shushan_zhanlong",time());
	damage = me->query_skill("sword");
        if( damage<2500 )
                damage  = 2500;
	msg = HIC"\n$N"HIC"默念御剑剑诀，手中$w"HIC"临空飞起，在半空化作一把丈许宽的巨剑，带起一路风卷残云，朝着$n"HIC"$l刺去！此式名为「"HIR"斩龙"HIC"」，确是气势非凡。\n"NOR;
	succ_msg = HIR"$n"HIR"一声惨叫，$l出现一处深可见骨的伤痕，顿时整个人萎靡不振。\n"NOR;
	me->set_temp("pfm_msg",1);
	me->set_temp("perform_YJS",5);
	me->add_temp("apply/attack",p);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,damage,"both");
	me->delete_temp("perform_YJS");
	me->add_temp("apply/attack",-p);
	me->delete_temp("pfm_msg");
	if( damage<1 )
	{
		message_combatd(HIY"$n"HIY"不慌不忙，向旁一闪，正好避了开来。\n"NOR,me,target);
		me->add_temp("shushan_zhanlong",3);
		return 1;
	}
	else
	{
		if( me && target && me->is_fighting(target)
		 && COMBAT_D->query_message_type(me,target)==2 )
			message_vision("结果对$N造成了"HIR+damage+NOR"点气血损伤、"HIR+damage+NOR"点精神损伤。\n",target);
		target->receive_wound("kee",damage,me,TYPE_PERFORM);
		target->receive_wound("sen",damage,me,TYPE_PERFORM);
		COMBAT_D->report_status(target,1);
	}
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：斩龙诀
        外功所属：御剑术
        外功效果：以气驭剑，对敌进行带固定伤害的全方面攻击
		  冷却时间5秒，不中则增加3秒
        外功条件：
        	  人物等级30级	
                  内力800点，消耗200点
                  御剑术400级并激发
                  醉仙望月步400级
LONG;
me->start_more(str);
return 1;
} 
