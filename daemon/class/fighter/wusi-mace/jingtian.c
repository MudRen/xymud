#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg,succ_msg;
        
	if( me->query_level()<15 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name") != "将军府" )
        	return notify_fail("你是哪儿偷学来的武功，也想用「惊天吼地」?\n");
	if( (int)me->query_skill("wusi-mace",1)<150)
        	return notify_fail("你的无私锏法不够娴熟，不会使用「惊天吼地」。\n");
	if( (int)me->query_skill("lengquan-force",1)<150)
        	return notify_fail("你的冷泉神功不够深厚，不会使用「惊天吼地」。\n");
        if( me->query_skill("yanxing-steps",1)<150 )
        	return notify_fail("你轻功还不够高明。\n");
     	if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("kee") < 300 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
	if( time()<me->query_temp("jjf_jingtian")+8 )
		return notify_fail("你现在嗓子有些肿痛。\n");
		        		
	weapon = me->query_temp("weapon");
	if( !weapon
	 || ( weapon->query("skill_type")!="mace"
	   && weapon->query("use_apply_skill")!="mace" ) )
		return notify_fail("你手里又没有锏！\n");
	if( me->query_skill_mapped("mace") != "wusi-mace" )
		return notify_fail("你的无私锏法不够娴熟，不会使用「惊天吼地」。\n");
	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展这一招「惊天吼地」？\n");

	msg = HIB"$N"HIB"运足内力一声巨吼，半空中忽然打了道利闪！$n"HIB"有些惊愕，$N"HIB"趁此良机，挥起$w"HIB"猛砸$p的$l！\n"NOR;
	succ_msg = HIR"$n"HIR"躲闪不及，被击个正着！狂雷夹带着火光，向$n"HIR"呼啸不止，结果$n"HIR"被雷火击中，一身焦黑！\n" NOR;
	me->add("force",-300);
	me->receive_damage("kee",150,me);
	me->set_temp("jjf_jingtian",time());
	
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,150);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIC"却被$n"HIC"躲开了！\n"NOR,me, target);
	else
	{
		target->receive_wound("sen",damage/2+1,me,TYPE_PERFORM);
		COMBAT_D->report_sen_status(target);
	}	
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：惊天吼地
        外功所属：无私锏法
        外功效果：给予对方带精神损失附加的攻击
        	  物理固定伤害150
                  使用后冷却时间 8 秒
        外功条件：
        	  将军府弟子
        	  人物等级15级	
                  内力500点，消耗300点
                  气血300点，消耗150点
                  无私锏法150级
                  冷泉神功150级
                 
LONG;
me->start_more(str);
return 1;
}
