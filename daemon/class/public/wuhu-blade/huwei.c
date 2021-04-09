#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int succ;
        object weapon;
        
        if( me->query_level()<11 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("wuhu-blade",1)<110
         || me->query_skill("blade",1)<110 )
		return notify_fail("你的刀法太差。\n");
	if( me->query_skill_mapped("blade")!="wuhu-blade" )
		return notify_fail("你必须使用五虎断门刀。\n");
        if( me->query_skill("force",1)<110 )
		return notify_fail("你的内功太差。\n");
        if( me->query_skill("dodge",1)<110 )
		return notify_fail("你的轻功太差。\n");
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出「狐假虎威」？\n");	
	if( me->query("force")<100 )
		return notify_fail("你的内力不足。\n");
	if( !target ) target = offensive_target(me);

	if( !target
	||  !target->is_character()
	||  target->is_corpse()
	||  target==me
	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展「狐假虎威」？\n");
	if( target->is_busy() )
		return notify_fail("对方已经自顾不暇了。\n");
		
	msg = HIR"\n$N"HIR"一声巨吼，却原来是五虎断门刀中的杀手招「狐假虎威」！\n"NOR;
	message_vision(msg,me,target);
	me->add("force",-80);
	succ = COMBAT_D->attack_percent(me,target,TYPE_PERFORM);
	if( succ>0 )
	{
		message_combatd(HIC"$N"HIC"猛地一惊，顿时给吓得六神无主。\n"NOR,target);
		target->start_busy(5);
	}
	else
	{
		message_combatd(HIC"$N"HIC"熟视无睹，并不受影响。\n"NOR,target);
		me->start_busy(2);
	}
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：狐假虎威
              外功所属：五虎断门刀  
              外功效果：使对方busy 5 秒，失败则自身busy 2 秒
              外功条件：
              		人物等级11级
              		基本内功110级
              		基本刀法110级
                        五虎断门刀110级
                        基本轻功110级
                        内力100点，消耗80点
LONG; 
me->start_more(str); 
return 1; 
} 
