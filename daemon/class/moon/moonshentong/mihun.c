// mihun.c 迷魂咒
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int cast(object me, object target)
{
        string msg;
        int success,howlong;

	if(me->query("family/family_name") != "月宫")
		return notify_fail("「迷魂咒」是月宫不传之密！\n");
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");
        if((int)me->query("mana") < 500 )
                return notify_fail("你的法力不够！\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("你无法集中精力！\n");
        if((int)me->query_skill("spells") < 400 )
                return notify_fail("你的法术修为太差。\n");
	
        if( !target ) target = offensive_target(me);

        if( !target
	 || !target->is_character()
	 || target->is_corpse()
	 || target==me
	 || !me->is_fighting(target) )
		return notify_fail("你想迷谁的魂？\n");  

        if( target->is_no_move() || target->is_busy() )
        	return notify_fail(target->query("name")+"已经魂不守舍，呆若木鸡了！\n");  

        me->add("mana", -200);
        me->receive_damage("sen", 50);

        msg = HIC"\n$N"HIC"低头轻声念了句咒文，又抬起头来朝$n"HIC"妩媚地一笑！\n"NOR;
	message_vision(msg,me,target);
	if( COMBAT_D->attack_percent(me,target,TYPE_CAST)>0 
	 || (me->query_temp("moon_huashen")=="hu"&&COMBAT_D->check_level(me,target)!=-1) )
        {
                msg =  HIR "$n"HIR"神不守舍地看着$N"HIR"，怜香惜玉之心由然而起，竟然忘了自己在战斗之中。\n" NOR;
                howlong = random((me->query_skill("spells") -100));
                if(howlong>60) howlong=60;
                if(howlong<10) howlong=10;
                target->set_temp("no_move",([
                        "start" : time(),
                        "time"  : howlong,
                ]));
                target->start_busy( howlong/5+1 );   
        }           
        else 
        {
        	msg +=  HIR "$n鄙夷地看了$N一眼，毫不为所动！\n" NOR;   
                me->start_busy(1);        
                if( living(target) && !target->is_killing(me->query("id")) )
                	target->kill_ob(me);
        } 
        message_vision(msg, me, target);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：迷魂咒
        法术所属：月宫仙法
        法术效果：使对方10-60秒内不能离开当前区域
        	  使对方 busy 3-15秒
        	  不命中则自身busy 1 秒
        	  不能对上述两种异常状态中的对象使用
        	  化狐状态下对同阶对手100%命中
        法术条件：
                  月宫弟子
        	  人物等级30级
                  法力500点，消耗200点
                  精神100点，消耗50点
                  有效法术 400 级
                  
STR;
        me->start_more(str);
        return 1;
}