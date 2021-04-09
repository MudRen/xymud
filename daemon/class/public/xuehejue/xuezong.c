// Xuezong.c 血踪万里
// Cracked by 凌惊雪 1-17-2003
// last modify by oukaya 03-10-27 13:45
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
	object weapon;
	string msg;
	int skill,extra,ap,dp,damage;
  
  	if( me->query_skill("pingfeng",2)>=1 )
		return notify_fail("你既然已经学了屏风四扇门，就不能三心二意。\n");
	
	skill=(int)me->query_skill("xuehejue",1);
  
	if( !target ) 
		target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || !me->is_fighting(target) )
		return notify_fail("「血踪万里」只能在战斗中使用。\n");
	if( (int)me->query("force") < 600 )
		return notify_fail("你的真气不够！\n");
	if( (int)me->query_skill("xuehejue",1) < 300 )
        	return notify_fail("你的血河诀火候不够，无法使用「血踪万里」！\n");
	if( (int)me->query_skill("force",1) < 300 )
        	return notify_fail("你的内功修为不够，无法使用「血踪万里」！\n");
	if( time()<me->query_temp("pfm_xuezong")+6 )
		return notify_fail("你不能频繁使用此招。\n");
	
	msg = HIR"$N"HIR"突然迎风起，御风飞，使出金衣楼血河诀的杀手究级技"HIR"血踪万里！\n"NOR;
	message_vision(msg, me);
 	me->add("force",-200);
 	me->set_temp("pfm_xuezong",time());
	extra=(int)me->query_skill("xuehejue",1)/2;
	if(extra >800) extra =800;

	weapon = me->query_temp("weapon");
	me->add_temp("apply/attack",extra/10);
	me->add_temp("apply/combat_damage",extra);
	msg = HBRED+HIW"                          血冻冰川                          "NOR"\n";
	me->set_temp("XHJ", 7);
	damage = COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);

	msg = BRED+HIR"                          血满江红                          "NOR"\n";
	me->set_temp("XHJ", 8);
	damage+= COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = BRED+HIY"                          血气冲天                          "NOR"\n";
	me->set_temp("XHJ", 9);
	damage+= COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	
	msg = HBRED+HIC"                          血踪万里                          "NOR"\n";
	me->set_temp("XHJ", 10);
	damage+= COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	me->delete_temp("XHJ");
	       
	me->add_temp("apply/attack",-extra/10);
	me->add_temp("apply/combat_damage",-extra);        
	
	if( damage>0 && !target->is_busy() )
	{
        	message_combatd(HIR"转眼不见了$N"HIR"的身行，$n"HIR"只觉眼前全是鲜血，顿时不知所措！\n"NOR,me,target);
       		target->start_busy(3);
	}
	else	message_combatd(HIR"不料确被$N"HIR"看破，结果$N"HIR"并不慌张！\n"NOR,target,me);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：血踪万里
        外功所属：血河诀
        外功效果：对敌连续攻击四次，
        	  若成功击中一次，则使非busy中的对方busy 3 秒，
        	  冷却 6 秒
        外功条件：
                  内力600点，消耗200点
                  内功心法 300 级
                  血河诀 300 级
STR;
        me->start_more(str);
        return 1;
}