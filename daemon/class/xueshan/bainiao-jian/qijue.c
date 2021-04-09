// qijue.c
// Modify by Jingxue for XYCQ 2.19.2004
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

string name()
{
	return "『凤凰七绝』";
}

int perform(object me, object target)
{
	object weapon;
    	string msg;
    	int attack,damage,force;
    	
    	if( me->query_level()<60 )
    		return notify_fail("你的人物等级不够。\n");
    	
    	if( !target ) target = offensive_target(me);        
    	if( !target        
     	 || !target->is_character()
     	 || target->is_corpse() 
     	 || target==me 
     	 || !me->is_fighting(target) )                
     		return notify_fail("你要对谁施展这一招『凤凰七绝』？\n");
	     	
	if( me->query_skill_mapped("force")!="ningxie-force" )
        	return notify_fail(name()+"必须配合冰谷凝血功才能使用。\n");
        if( me->query_skill_mapped("dodge")!="xiaoyaoyou" )
        	return notify_fail(name()+"必须配合逍遥游才能使用。\n");
        if( me->query_skill_mapped("sword")!="bainiao-jian" )
        	return notify_fail(name()+"乃是百鸟剑法的绝技。\n");
	damage = 50;
	attack = 5;
	force = 200;
	if( me->query("family/master_name")=="大鹏明王" )
	{
		damage = me->query_skill("bainiao-jian",1)/2;
		attack = me->query_skill("xiaoyaoyou",1)/5;
		force = 300;
	}
	if((int)me->query("force") < 300 )                     
		return notify_fail("你体内的内力不足300点！\n");
	if((int)me->query_skill("bainiao-jian",1) < 550)              
		return notify_fail("你的『百鸟剑法』等级需要550级！\n");
	if((int)me->query_skill("ningxie-force",1) < 550)      
		return notify_fail("你的『冰谷凝血功』等级需要550级！\n");
	if((int)me->query_skill("xiaoyaoyou",1) < 550)      
		return notify_fail("你的『逍遥游』等级需要550级！\n");
	weapon = me->query_temp("weapon");
	message_vision(HIW"\n$N"HIW"飘然而进，手中"+weapon->query("name")+HIW"微微震颤，刹那间连出七剑，分刺$n"HIW"全身七个部位，正是"HIR"『--凤--凰--七--绝--』\n"NOR, me, target);
	me->add("force", -force);
	me->add_temp("apply/attack",attack);
    	me->add_temp("apply/combat_damage",damage);
    
    	if( random(me->query("force_factor"))>50 )
    		me->set_temp("fengwu",1);
    
    	msg = HIY"【"HIR"七绝"HIW"寒杀"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = "\n"HIY"【"HIR"七绝"HIY"夺命"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = "\n"HIY"【"HIR"七绝"HIW"冰封"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = "\n"HIY"【"HIR"七绝"HIM"斩魂"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = "\n"HIY"【"HIR"七绝"HIC"鸿飞"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = "\n"HIY"【"HIR"七绝"NOR RED"神屠"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = "\n"HIY"【"HIR"七绝"HIB"魔"HIY"解"NOR HIY"】"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);

	me->add_temp("apply/attack",-attack);
    	me->add_temp("apply/combat_damage",-damage);
    	me->delete_temp("fengwu");
    	me->start_busy(2);
    	return 1;
}

int help(object me)
{ 
	string str; 
	if ( !me )      return 0; 
	str = @LONG 
              外功名称：凤凰七绝  
              外功所属：百鸟剑法  
              外功效果：七剑绝杀，用手中武器对敌人造成连续性的七次伤害 
              		自身busy 2 秒 
              外功条件：
              		人物等级60级
              		百鸟剑法550级以上
                        冰谷凝血功550级以上
                        内力300点，消耗250-300点
                        内功激发冰谷凝血功
                        轻功激发逍遥游
                        剑法激发百鸟剑法
                        
LONG; 
	me->start_more(str); 
	return 1; 
} 

