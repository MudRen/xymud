#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int damage,dodge;
        object weapon;
        
        if( me->query_level()<18 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("wuhu-blade",1)<180
         || me->query_skill("blade",1)<180 )
		return notify_fail("你的刀法太差。\n");
	if( me->query_skill_mapped("blade")!="wuhu-blade" )
		return notify_fail("你必须使用五虎断门刀。\n");
        if( me->query_skill("force",1)<180 )
		return notify_fail("你的内功太差。\n");
        if( me->query_skill("dodge",1)<180 )
		return notify_fail("你的轻功太差。\n");
	if( time()<me->query_temp("wuhu_qihu")+6 )
	        return notify_fail("绝招用多就不灵了。\n");        
		
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出「骑虎难下」？\n");	
	if( me->query("force")<300 )
		return notify_fail("你的内力不足。\n");
	
	if( !target ) target = offensive_target(me);

	if( !target
	||  !target->is_character()
	||  target->is_corpse()
	||  target==me
	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展「骑虎难下」？\n");
      
	damage = me->query_skill("blade");
	dodge = me->query_skill("dodge");
	me->set_temp("pfm_color","HIR");
	me->set_temp("wuhu_pushi",time());
	me->set_temp("PERFORM_WUHU",4);
	me->add_temp("apply/attack",dodge);
	me->add("force",-150);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,"\n",0,0,damage);
	if( damage>0 )
	{
		message_combatd(RED"\n$N"NOR RED"刀尖滴血，恶狠狠朝$n"NOR RED"的狂笑：叫你看看某家的大杀器！\n"NOR,me,target);
		target->receive_wound("kee",damage,me,TYPE_PERFORM);
		COMBAT_D->report_status(target,1);
	}
	me->delete_temp("PERFORM_WUHU");
	me->add_temp("apply/attack",-dodge);
	me->delete_temp("pfm_color");
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：骑虎难下
              外功所属：五虎断门刀  
              外功效果：带固定伤害攻击对方
              		冷却时间6秒
              外功条件：
              		人物等级18级
              		基本内功180级
              		基本刀法180级
                        五虎断门刀180级
                        基本轻功180级
                        内力300点，消耗150点
LONG; 
me->start_more(str); 
return 1; 
} 
