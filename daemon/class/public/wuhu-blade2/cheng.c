#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int damage;
        object weapon;
        
        if( me->query_level()<15 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("wuhu-blade",1)<150
         || me->query_skill("blade",1)<150 )
		return notify_fail("你的刀法太差。\n");
	if( me->query_skill_mapped("blade")!="wuhu-blade" )
		return notify_fail("你必须使用五虎断门刀。\n");
        if( me->query_skill("force",1)<150 )
		return notify_fail("你的内功太差。\n");
        if( me->query_skill("dodge",1)<150 )
		return notify_fail("你的轻功太差。\n");

	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出「三人成虎」？\n");	
	if( me->query("force")<200 )
		return notify_fail("你的内力不足。\n");
	
	if( !target ) target = offensive_target(me);

	if( !target
	||  !target->is_character()
	||  target->is_corpse()
	||  target==me
	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展「三人成虎」？\n");
      
	damage = me->query_skill("blade");
	if( damage>1800 )
		damage = 1800;
	me->set_temp("pfm_color","HIY");
	me->set_temp("PERFORM_WUHU",2);
	me->add("force",-100);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,0,0,damage/2);
	me->delete_temp("PERFORM_WUHU");
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,"\n紧跟着",0,0,damage);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,"\n最后一招，",0,0,damage*3/2);
	me->delete_temp("pfm_color");
	me->start_busy(3);
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：三人成虎
              外功所属：五虎断门刀  
              外功效果：带固定伤害连续攻击对方三次
              		自身busy 3 秒
              外功条件：
              		人物等级15级
              		基本内功150级
              		基本刀法150级
                        五虎断门刀150级
                        基本轻功150级
                        内力200点，消耗100点
LONG; 
me->start_more(str); 
return 1; 
} 
