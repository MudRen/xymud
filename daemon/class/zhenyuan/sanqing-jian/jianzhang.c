//「剑中出掌」
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int enhance,damage;
        string str;
	
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") 
	 || me->query_skill_mapped("sword")!="sanqing-jian" ) 
		return notify_fail("你没有剑，如何能发出「剑中出掌」？\n");	 	
        if( time()-(int)me->query_temp("wzg_jianzhang") < 5 )
                return notify_fail("绝招用多就不灵了！\n");
        if(me->query_skill("sanqing-jian",1)<80)
                return notify_fail("你的三清剑法太差，还不会出「剑中出掌」。\n");
        if(me->query_skill("wuxing-quan",1)<80) 
                return notify_fail("你的五行拳太差，还不会出「剑中出掌」。\n");
        if(me->query_skill("zhenyuan-force",1)<80)
                return notify_fail("你的镇元神功修为不够，还不会出「剑中出掌」。\n");
        if(me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("「剑中出掌」必须配合镇元神功才能使用。\n");
        if(me->query_skill_mapped("unarmed")!="wuxing-quan")
                return notify_fail("「剑中出掌」必须配合五行拳才能使用。\n");
        if(me->query("force")<300)
                return notify_fail("你内力不继，难以出招。\n");
	
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要攻击谁？\n");
        
        me->add("force", -50);
        me->set_temp("wzg_jianzhang",time());
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
	weapon = me->query_temp("weapon");
	weapon->set("use_apply_skill","unarmed");
	me->reset_action();        
   	message_combatd(HIC"\n$N"HIC"运起镇元神功，没等招式用老，脚踏八卦，身形一下转过一边，紧接着收剑出掌。\n"NOR,me);
   	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
   	weapon->delete("use_apply_skill");
   	me->reset_action();
   	
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：剑中出掌
        外功所属：三清剑法
        外功效果：以三清剑法与五行拳各攻击对方一次
                  冷却时间5秒
        外功条件：
        	  人物等级8级	
        	  内功激发镇元神功
        	  拳法激发五行拳
        	  剑法激发三清剑法
                  内力300点，消耗50点
                  三清剑法 80 级
                  五行拳 80 级
                  镇元神功 80 级
STR;
        me->start_more(str);
        return 1;
}