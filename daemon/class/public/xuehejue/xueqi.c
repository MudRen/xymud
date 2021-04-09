// Xueqi.c 血气惊天
// Cracked by 凌惊雪 1-17-2003
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
	string msg;
	int skill,extra;

	if( me->query_skill("pingfeng",2)>=1 )
		return notify_fail("你既然已经学了屏风四扇门，就不能三心二意。\n");
		    
	skill=(int)me->query_skill("xuehejue",1);
	if( !target ) 
		target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || !me->is_fighting(target) )
		return notify_fail("「血气惊天」只能在战斗中使用。\n");
	if( (int)me->query("force") < 600 )
        	return notify_fail("你的真气不够！\n");
	if( time()-(int)me->query_temp("pfm_xuehejue") < 5 )
        	return notify_fail("绝招用多就不灵了！\n");                
	if( (int)me->query_skill("xuehejue",1) < 150 )
        	return notify_fail("你的血河诀火候不够，无法使用「血气惊天」！\n");
	if( (int)me->query_skill("force",1) < 150 )
        	return notify_fail("你的内功修为不够，无法使用「血气惊天」！\n");

	msg = HIR "$N"HIR"身行突变，使出血河诀的绝技"RED"血气惊天"NOR HIR"！\n"NOR;
	message_vision(msg, me);
	me->set_temp("pfm_xuehejue",time());
	me->add("force",-100);
	
    	extra=(int)me->query_skill("xuehejue",1)/2;
	if(extra >500) extra =500;
	me->add_temp("apply/attack",extra);
	me->add_temp("apply/combat_damage",extra);

	msg = HIR"          血河倒泻！\n"NOR;
	me->set("XHJ", 1);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_QUICK,msg);
	msg = HIY"          血气弥漫！\n"NOR;
	me->set("XHJ", 2);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_QUICK,msg);
	msg = HIC"          血雾纷飞！\n"NOR;
	me->set("XHJ", 3);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	msg = HIW"          血气惊天！\n"NOR;
	me->set("XHJ", 4);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);	
	
	me->add_temp("apply/attack",-extra);
	me->add_temp("apply/combat_damage",-extra);        
	me->delete_temp("XHJ");          
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：血气惊天
        外功所属：血河诀
        外功效果：对敌连续攻击四次，冷却5秒
        外功条件：
                  内力600点，消耗100点
                  内功心法 150 级
                  血河诀 150 级
STR;
        me->start_more(str);
        return 1;
}