#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit SSERVER;

int cast(object me, object target)
{
	string msg,succ_msg;
	int damage, howlong,succ,p;

	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n");
	if((int)me->query("mana") < 500 )
        	return notify_fail("你的法力不够！\n");
	if((int)me->query("sen") < 100 )
        	return notify_fail("你无法集中精力！\n");
	if(me->query("family/family_name")!="东海龙宫") 
        	return notify_fail("非龙宫弟子不能用这招！\n");
	if( me->query_skill("seashentong",1)<200 )
		return notify_fail("你的碧海神通不够熟练。\n");
	if( !target ) target = offensive_target(me);	
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me 
 	 || !me->is_fighting(target) )
        	return notify_fail("你想把谁定住？\n");
	if( !valid_move(target) )
        	return notify_fail(target->name()+"已经动弹不得了！\n");

	me->add("mana", -200);
	me->receive_damage("sen",50,me);
	p = 0;
	if( me->query_skill("qiyu",2)>100 )
		p = (me->query_skill("qiyu",1)-100)/250+5;
	msg = HIC"$N"HIC"在手中划了个咒，望天一指，只见顿时天上雪舞风刮，大大小小的雪片冰雹向$n"HIC"飘了过去。\n"NOR;
	message_vision(msg,me,target);
	 me->add_temp("apply/spells_succ",p);
	succ = COMBAT_D->attack_percent(me,target,TYPE_CAST);
	if( succ>0 )
	{
		succ_msg = HIR "结果$n"HIR"手足被冻的僵硬，动弹不得。\n" NOR;
		howlong = (int)me->is_knowing("sea_freez")+1;
		howlong+= me->query_skill("spells")/60;
		target->start_busy(howlong);
		target->start_no_move((howlong/2+1),"你被"+me->name()+"召唤的风雪冻住了手脚。\n");
	}
	else
	{
		message_vision(HIR"$N"HIR"将手一指，”赦“的一声，满天风雪顿时化作虚影。\n"NOR,target);
		me->start_busy(1+random(2));
	}
	 me->add_temp("apply/spells_succ",-p);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：雪舞风灵
        法术所属：碧海神通
        法术效果：召唤风雪使对方限于僵直与捆缚的状态
        	  对此状态下的对象不能使用
		  如失败，则自身busy 1-2 秒
        法术条件：
                  龙宫弟子
        	  人物等级20级
                  法力500点，消耗200点
                  精神100点，消耗50点
                  碧海神通 200 级
                  
STR;
        me->start_more(str);
        return 1;
}