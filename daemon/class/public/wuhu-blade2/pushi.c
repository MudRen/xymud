#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int damage;
        object weapon;
        
        if( me->query_level()<20 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("wuhu-blade",1)<200
         || me->query_skill("blade",1)<200 )
		return notify_fail("你的刀法太差。\n");
	if( me->query_skill_mapped("blade")!="wuhu-blade" )
		return notify_fail("你必须使用五虎断门刀。\n");
        if( me->query_skill("force",1)<200 )
		return notify_fail("你的内功太差。\n");
        if( me->query_skill("dodge",1)<200 )
		return notify_fail("你的轻功太差。\n");
	if( time()<me->query_temp("wuhu_pushi")+5 )
	        return notify_fail("绝招用多就不灵了。\n");        
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出「饿虎扑食」？\n");	
	if( me->query("force")<100 )
		return notify_fail("你的内力不足。\n");
	
	if( !target ) target = offensive_target(me);

	if( !target
	||  !target->is_character()
	||  target->is_corpse()
	||  target==me
	|| !me->is_fighting(target) )
		return notify_fail("你要对谁施展「饿虎扑食」？\n");
      
	damage = me->query_skill("blade");
	if( damage>2000 )
		damage = 2000;
	me->set_temp("pfm_color","HIR");
	me->set_temp("wuhu_pushi",time());
	me->set_temp("PERFORM_WUHU",1);
	me->add("force",-50);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,"\n",0,0,damage);
	me->delete_temp("PERFORM_WUHU");
	me->delete_temp("pfm_color");
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：饿虎扑食
              外功所属：五虎断门刀  
              外功效果：带固定伤害攻击对方
              		冷却时间 5 秒
              外功条件：
              		人物等级20级
              		基本内功200级
              		基本刀法200级
                        五虎断门刀200级
                        基本轻功200级
                        内力100点，消耗50点
LONG; 
me->start_more(str); 
return 1; 
} 
