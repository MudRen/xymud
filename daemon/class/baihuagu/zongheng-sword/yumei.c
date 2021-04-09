// yumei.c
// Modify by Jingxue for XYCQ 3.3.2004
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg,succ_msg;
	int damage,attack;
        
        if( me->query_level()<20 )
        	return notify_fail("你的人物等级不够。\n");
	if((int)me->query("force") < 800 )
        	return notify_fail("你内力不足！\n");        
	if( (int)me->query_skill("brightjade-force",1) < 200
	 || (string)me->query_skill_mapped("force")!="brightjade-force" )             
        	return notify_fail("你的『明玉神功』等级不够。\n");
	if( (int)me->query_skill("zongheng-sword",1) < 200
	 || (string)me->query_skill_mapped("sword")!="zongheng-sword" )             
        	return notify_fail("你的『纵横剑法』等级不够。\n");
	if( (int)me->query_skill("wuyou-steps",1) < 200
 	 || (string)me->query_skill_mapped("dodge")!="wuyou-steps" )             	         
		return notify_fail("你的『无忧步法』等级不够。\n");
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )              
    		return notify_fail("你要对谁施展『雨激梅花半瓣香』？\n");        

	damage = me->query_skill("sword")+me->query_skill("force");
	damage/= 2;
	attack = me->query_skill("dodge")/30;
	if( !me->query("family/family_name")
	 || me->query("family/family_name")!="百花谷" )
	{
		attack = 0;	 
		damage/= 2;
	}		
	
	me->add("foce",-100); 
	me->set_temp("bhg_yumei",time());	
	msg = HIM"\n$N手中$w"HIM"斜斜一带，施展出「"HIC"雨激梅花半瓣香"HIM"」，轻飘飘压向$n"HIM"！\n"NOR;
	msg+= HIM"一阵花香，$n"HIM"只觉得眼前烟雨朦胧，却不知是"HIW"梅"HIM"还是"HIC"雨"HIM"。梅花一闪，隐约一阵金铁之声，$N"HIM"手中$w"HIM"一振，梅花瓣瓣如烟如雨般击向$n"HIM"。\n"NOR;
	succ_msg = HIR"结果$n"HIR"促不及防，阵阵梅雨透体而穿，眼前一黑，再也提不起气！\n"NOR;
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",attack);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"小腹",damage);
	me->add_temp("apply/attack",-attack);
	me->set_temp("pfm_msg",0);
	me->start_busy(2);
	if( damage<1 )
		message_combatd(HIM"\n只见$n"HIM"不慌不忙，轻轻一闪，躲过了阵阵梅雨！\n"NOR, me,target);
	else if( damage>3 )
	{		
		if( COMBAT_D->query_message_type(me,target)==2 )
			message_vision(HIR"另外还造成了"+damage/3+"点气血损伤。\n"NOR,me,target);
		target->receive_wound("kee", damage/3, me,TYPE_PERFORM);
            	COMBAT_D->report_status(target,1);
	}	
	return 1;
}

int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        外功名称：雨激梅花半瓣香
        外功所属：纵横剑法
        外功效果：以内力使剑化梅花，对敌进行猛烈的一击
                  使用后自身busy 2 秒
        外功条件：
                  人物等级20级
                  内力800点，消耗100点
                  纵横剑法200级并激发
                  无忧步法200级并激发
                  明玉神功200级并激发
LONG;
me->start_more(str);
return 1;
}

