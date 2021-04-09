// bighammer.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int cast(object me, object target)
{
	int damage,p;
	string msg,succ_msg;
	
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name") != "南海普陀山" 
	 && me->query("chushi/chushi_putuo")!="yes" )
		return notify_fail("你不能使用这项技能！\n");
	if( time()<me->query_temp("putuo_bighammer")+7 )
		return notify_fail("你刚刚祭过降魔杵，还是休息休息。\n");		
	if( !target ) target = offensive_target(me);		
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me)
		return notify_fail("你要用大力降魔杵打谁？\n");

	if((int)me->query("mana") < 2000 )
    		return notify_fail("你的法力不够！\n");
	if((int)me->query("sen") < 100 )
    		return notify_fail("你无法集中精力，别砸中自己了！\n");
	if( me->query_skill("buddhism",1)<240 )
		return notify_fail("你的大乘佛法不够精深。\n");

	p = me->query_skill("spells")/150+1;
	me->add_temp("apply/attack",p);
	me->set_temp("putuo_bighammer",time());
	me->add("mana", -200);
	me->receive_damage("sen",50,me);
		
	msg = HIC "$N"HIC"口中念了几句咒文，半空中现出阿傩，迦叶二尊者，各人手执一根巨大无比的降魔杵，呼！地一声向$n"HIC"当头砸下！\n" NOR;
	succ_msg = HIC "结果砸个正着，差点没把$n"HIC"砸扁！\n" NOR;
	me->set_temp("pfm_msg",1);
	damage = me->query_skill("buddhism",1)/2;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_CAST,msg,succ_msg,"头部",damage,"both");
	me->set_temp("pfm_msg",0);
        me->add_temp("apply/attack",-p); 

	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        法术名称：大力降魔杵
        法术所属：大乘佛法
        法术效果：召唤降魔杵，对敌精神气血进行打击
                  冷却 7 秒，失败则增加3秒并自身busy 1-2 秒
        法术条件：
                  普陀(出师)弟子
                  人物等级30级
                  法力2000点，消耗200点
                  精神100点，消耗50点
                  大乘佛法240级
LONG;
me->start_more(str);
return 1;
}


