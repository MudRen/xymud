#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
	string msg,str;
	
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="火云洞")
        	return notify_fail("“掌心雷”只有火云洞门人才可以用！\n");		
	if( time()-(int)me->query_temp("kusong_lei")<5 )
       		return notify_fail("绝招用多就不灵了！\n"); 
        if((int)me->query("force") < 200 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("kee") < 100 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if((int)me->query_skill("moyun-shou", 1) < 50)
                return notify_fail("你的摩云手级别还不够，使用这一招会有困难！\n");
	weapon = me->query_temp("weapon");
	if( weapon )
	{
		if( weapon->query("skill_type")!="unarmed" && weapon->query("use_apply_skill")!="unarmed" ) 
			return notify_fail("你的摩云手级别还不够，使用这一招会有困难！\n");
	}
	                
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要对谁施展这一招掌心雷？\n");

	message_vision("$N大喝一声“掌心雷”！\n", me);
	me->set_temp("kusong_lei",time());
        me->receive_damage("kee", 50);
        me->add("force", -50);
	me->set_temp("moyunshou_per",7);
	me->add_temp("apply/attack",15);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,0,0,0,me->query_skill("unarmed")/3);
	me->add_temp("apply/attack",-15);
	me->delete_temp("moyunshou_per");
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：掌心雷
        外功所属：摩云手
        外功效果：给予对方带固定伤害的一击
                  冷却时间5秒
        外功条件：
        	  火云洞弟子
        	  人物等级5级	
        	  内力200点，消耗50点
        	  气血100点，消耗50点
                  摩云手 50 级
STR;
        me->start_more(str);
        return 1;
}