#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int damage,dodge;
        object weapon;
        
        if( me->query_level()<14 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("wuhu-blade",1)<140
         || me->query_skill("blade",1)<140 )
		return notify_fail("你的刀法太差。\n");
	if( me->query_skill_mapped("blade")!="wuhu-blade" )
		return notify_fail("你必须使用五虎断门刀。\n");
        if( me->query_skill("force",1)<140 )
		return notify_fail("你的内功太差。\n");
        if( me->query_skill("dodge",1)<140 )
		return notify_fail("你的轻功太差。\n");
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出「虎落平阳」？\n");	
	if( me->query("force")<240 )
		return notify_fail("你的内力不足。\n");
	
	if( !target ) target = offensive_target(me);

	if( !target
	||  !target->is_character()
	||  target->is_corpse()
	||  target==me
	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展「虎落平阳食」？\n");
      
	damage = me->query_skill("blade");
	dodge = me->query_skill("dodge");
	me->set_temp("pfm_color","HIR");
	me->set_temp("wuhu_pushi",time());
	me->set_temp("PERFORM_WUHU",4);
	me->add_temp("apply/attack",dodge);
	me->add("force",-150);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,"\n",0,0,damage);
	me->delete_temp("PERFORM_WUHU");
	me->add_temp("apply/attack",-dodge);
	me->delete_temp("pfm_color");
	me->start_busy(2);
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：虎落平阳
              外功所属：五虎断门刀  
              外功效果：带固定伤害攻击对方
              		自身busy 2 秒
              外功条件：
              		人物等级14级
              		基本内功140级
              		基本刀法140级
                        五虎断门刀140级
                        基本轻功140级
                        内力240点，消耗150点
LONG; 
me->start_more(str); 
return 1; 
} 
