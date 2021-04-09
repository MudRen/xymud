// dingshen.c 定身咒
#include <ansi.h>
#include "/cmds/std/valid_move.h"
inherit SSERVER;

int cast(object me, object target)
{
        string msg;
        int success, ap, dp, howlong;

	if( me->query_level()<40 )
		return notify_fail("你的人物等级不够。\n");
				
	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me 
 	|| !me->is_fighting(target) )
		return notify_fail("你想把谁定住？\n");
	if( userp(me) && !me->is_knowing("puti_dingshen") && !wizardp(me) )
		return notify_fail("你不能使用这项技能！\n"); 	
	if(me->query("family/family_name")!="方寸山三星洞" 
        && me->query("chushi/chushi_fangcun")!="yes" )
		return notify_fail("此乃方寸秘技！\n"); 
        if((int)me->query_skill("dao",1)<200)
		return notify_fail("你还没学会定身咒。。。\n");
        if( target->is_blind() )
                return notify_fail(target->query("name")+"已经动弹不得了！\n");
        if((int)me->query("mana") < 500 )
                return notify_fail("你的法力不够！\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("你无法集中精力！\n");
	if( time()<me->query_temp("puti_dingshen")+15 )
		return notify_fail("你刚刚念过咒。\n");
		
        me->add("mana", -200);
        me->receive_damage("sen",50);

        msg = HIC"$N"HIC"口中念了句咒文，朝$n一指，大喝一声：定！\n"NOR;

        success = 1;
        ap = me->query_skill("spells");
        if( ap>900 ) ap=900;
        ap+= me->query_level()*10;
        dp = target->query_skill("spells");
        dp+= target->query_level()*6;
        
        if( random(ap + dp) < dp ) success = 0;

        ap = (int)me->query_maxmana();
        dp = (int)target->query_maxmana();
        if( random(ap + dp) < dp/2 ) success = 0;

        ap = (int)me->query("mana");
        dp = (int)target->query("mana");
        if( random(ap + dp) < dp/3 ) success = 0;

        howlong = 0;        
        if(success == 1 )
        {
                msg +=  HIR "结果$n手足僵硬，果然动弹不得！\n" NOR;
                howlong = 8 + random((me->query_skill("spells") -200));
                if(howlong>15) howlong=15;
                target->start_blind(howlong,HIR"你被"+me->name()+HIR"用「定身咒」定住了！\n"NOR);
	}           
        else	msg +=  HIR "结果$n"HIR"被吓了一跳！\n" NOR; 
        message_vision(msg, me, target);
        if( living(target) && !target->is_killing(me->query("id")) )
        	target->kill_ob(me);
	if(success == 0) 
	{
		me->start_busy(1);
		return 1;
	}
        return 1;
}

int help(object me)
{
	string str;
	if( !me )      
		return 0;
str = @LONG
        法术名称：定身咒
        法术所属：道家仙法
        法术效果：使敌人静默至少8秒，静默期间无法发出任何动作
                  冷却时间15秒
                  需领悟
        法术条件：
          	  方寸(出师)弟子 
        	  人物等级40级
                  精神100点，消耗50点
                  法力500点，消耗200点 
                  道家仙法200级

LONG;
	me->start_more(str);
	return 1;
} 