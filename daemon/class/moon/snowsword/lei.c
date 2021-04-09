//风月凝泪
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon;
        int i,j;
	string msg;                
	
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");
	if((int)me->query("force") <500 )
		return notify_fail("你的内力不够！\n");
        if((int)me->query_skill("snowsword", 1) < 300)
		return notify_fail("你的风回雪舞剑级别还不够，无法使用「风月凝泪」！\n");
	if( (int)me->query_skill("moondance", 1) < 300)
		return notify_fail("你的冷月凝香舞级别还不够，无法使用「风月凝泪」！\n");
	if( time()<me->query_temp("moon_lei")+6 )
		return notify_fail("绝招用多就不灵了。\n");
	
	if( !target ) target = offensive_target(me);
    	if( !target
     	 || !target->is_character()
     	 || !me->is_fighting(target)
     	 || target->is_corpse() || target->is_ghost()
	 || target==me )
		return notify_fail("你要对谁施展这一招「风月凝泪」？\n");

	if( !objectp(weapon=me->query_temp("weapon"))
	 || weapon->query("skill_type")!="sword" )
		return notify_fail("你的剑呢？\n");
			 
	me->add("force", -200);
	me->set_temp("moon_lei",time());
	j = me->query_skill("sword")/10;
	me->add_temp("apply/attack",j);
        me->set_temp("MOON_perform",1);
        
        msg = HIW"$N"HIW"剑势越舞越快，剑气四射，寒光逼人，突然一声长啸，剑光如滑落的泪滴般洒下来，在天际中划出一道优美的弧线，思念了眼！\n"NOR;
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg);
        
	msg = HIC"\n☆既不回头，何必不忘☆\n"NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg);
		
 	msg = HIC"\n☆既然无缘，何需誓言☆\n"NOR;
 	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg);
 		
        msg = HIC"\n☆今日种种，似水无痕☆\n"NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        
        msg = HIC"\n☆明夕何夕，君已陌路☆\n"NOR;
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));         

        me->add_temp("apply/attack",-j);
        me->delete_temp("MOON_perform");
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：风月凝泪
        外功所属：回风雪舞剑
        外功效果：连续四次攻击对方
                  冷却6秒
        外功条件：
        	  人物等级30级
                  内力500点，消耗200点
                  风回雪舞剑 300 级
                  冷月凝香舞 300 级
                  
STR;
        me->start_more(str);
        return 1;
}
