#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	int succ,p,t;
	string msg,succ_msg;

	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="东海龙宫")
        	return notify_fail("非龙宫弟子不能用「风波」！\n");
	if( (int)me->query_skill("fengbo-cha", 1) <80 ) 
        	return notify_fail("你的修为不够深，还使不出这一招！\n");
	if(me->query("force")<300 )
        	return notify_fail("你的内力不足了。\n");
		
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("「无尽风波」只有在战斗中才能使用。\n");

	if( target->is_busy() )
        	return notify_fail(target->name()+"已经够忙了，你使的再漂亮也不会注意到。\n");
        
	msg = HIC"$N"HIC"挥展开来，左一叉，右一叉，幻出无数大小光环向$n"HIC"绕去。虽看起来柔弱无力，却宛若秋波般连绵不绝，实是暗藏杀机！\n"NOR;
	succ_msg = HIR"$n"HIR"果然被这光环套住，当时目瞪口呆，不知所措！\n"NOR;
	message_vision(msg,me,target);	
	me->add("force",-150);
	p = me->query_skill("fork");
	me->add_temp("apply/attack",p);
	succ = COMBAT_D->attack_percent(me,target,TYPE_PERFORM);
	me->add_temp("apply/attack",-p);
	if( succ>0 )
	{
		message_vision(succ_msg,me,target);
		t = me->query_skill("fengbo-cha",1)/49+2;
		if( t>10 )
			t = 10;
		t+= ((int)me->is_konwing("sea_fengbo")+1);
		target->start_busy(t);
	}
	else
	{
		message_vision(HIR"不料却被$N"HIR"看破，攻其不备，$n"NOR"反被打了个措手不及！\n"NOR,target,me);
		me->start_busy(1);
	}
        return 1;
}

int help(object me)
{
string str;
if ( !me )      return 0;
str = @LONG
        外功名称：无尽风波
        外功所属：风波十二叉
        外功效果：以风波叉攻击对方并使其陷入僵直状态至少3秒
        	  失败自身 busy 1 秒
        	  可通过提高技能以及领悟来提高效果时间
        	  对busy中的对象无法使用
        外功条件：
        	  龙宫弟子
        	  人物等级8级	
                  内力300点，消耗150点
                  风波十二叉80级
LONG;
me->start_more(str);
return 1;
}

