#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg,succ_msg;
    	int damage;
    	
    	if( me->query_level()<15 )
    		return notify_fail("你的人物等级不够。\n");
    	if(me->query("family/family_name")!="陷空山无底洞")
    		return notify_fail("“这招只有无底洞门人才可以用！\n"); 
	if((int)me->query("force") < 500 )
		return notify_fail("你的内力不足！\n");
	if((int)me->query_skill("qixiu-jian", 1) < 150)
		return notify_fail("你的七修剑等级还不够!!\n");
	if( time()<me->query_temp("wdd_yaowu")+5 )
		return notify_fail("绝招用多就不灵了。\n");
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
		return notify_fail("你要对谁施展这一招「妖雾冲天」?\n");

	me->add("force",-150);
	me->set_temp("wdd_yaowu",time());
	msg = MAG"$N"MAG"阴阴一笑,手中的$w"MAG"轻轻一挥,登时飞沙走石,妖雾直冲$n"MAG"$l！\n"NOR;
	me->set_temp("PERFORM_QXJ",7);
	me->set_temp("pfm_color",MAG);
	me->set_temp("pfm_msg",1);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("weapon")/5);
	me->delete_temp("pfm_msg");
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,0,0,me->query_skill("weapon")/2);
	me->delete_temp("pfm_color");	
	me->delete_temp("PERFORM_QXJ");
	return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
              外功名称：妖雾冲天
              外功所属：七修剑法 
              外功效果：对敌连续两次带固定伤害的物理攻击
                        冷却5秒
              外功条件：
              		无底洞弟子
              		人物等级15级
              		内力500点，消耗150点
              		七修剑150级
LONG;
me->start_more(str);
return 1;
}

