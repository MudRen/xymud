#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        string str;
        int wp,i;
        
        if( me->query_level()<15 )
        	return notify_fail("你的人物等级不够。\n");
	if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("sanqing-jian", 1) < 100)
                return notify_fail("你的三清剑法级别还不够，使用这一招会有困难！\n");
        if (me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("「三清绝剑」必须配合镇元神功才能使用。\n");
	if(me->query("family/family_name") != "五庄观")
		return notify_fail("「三清绝剑」是五庄观不传之密！\n");   
	if( time()<me->query_temp("wzg_juejian")+4 )
		return notify_fail("你不能频繁使用。\n");                                             	
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要对谁施展这一招「三清绝剑」？\n");

        message_vision(HIC"$N"HIC"深深吸了一口真气，足尖轻轻点地，身形腾空而起，凌空向$n"HIC"使出了「三清绝剑」！\n"NOR,me,target);
        me->add("force", -100);
        me->receive_damage("sen", 50,me);
        me->set_temp("SQJ_perform", 7);
	me->reset_action();
	        
        wp = me->query_skill("sanqing-jian",1)/5;
        target->add_temp("apply/dodge",-wp);
        target->add_temp("apply/parry",-wp);
        me->add_temp("apply/attack",wp);
        me->add_temp("apply/combat_damage",wp);
        
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM);
        me->delete_temp("SQJ_perform");
        me->reset_action();
        me->add_temp("apply/attack",-wp);
        me->add_temp("apply/combat_damage",-wp);
        if( target )
        {
                target->add_temp("apply/parry",wp);
                target->add_temp("apply/dodge",wp);
        }
	me->start_busy(1+random(2));
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：三清绝剑
        外功所属：三清剑法
        外功效果：短时间内提高自身的命中和伤害，并降低对方的闪避与招架，进行物理攻击
                  冷却4秒
        外功条件：
        	  五庄观弟子	
        	  人物等级15级	
        	  内功激发镇元神功
                  内力500点，消耗100点
                  精神100点，消耗50点
                  三清剑法 100 级
STR;
        me->start_more(str);
        return 1;
}