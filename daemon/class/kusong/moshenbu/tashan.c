#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object *enemy;
        int t,i,succ;
	string msg;
	
	if( me->query_level()<15 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="火云洞")
        	return notify_fail("「踏山裂石」只有火云洞门人才可以用！\n");		
        if((int)me->query("force") < 300 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("kee") < 200 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if((int)me->query_skill("moshenbu", 1) < 150)
                return notify_fail("你的魔神步法级别还不够，使用这一招会有困难！\n");
        if((int)me->query_skill("dali-bang", 1) < 150)
                return notify_fail("你的大力棒级别还不够，使用这一招会有困难！\n");
	if( time()<me->query_temp("kusong_tashan")+8 )
		return notify_fail("你刚刚使过，还是歇歇再说。\n");
                
	me->clean_up_enemy();                   
	if( !me->is_fighting() )
		return notify_fail("你不在战斗中，如何使用此招？\n");
	enemy = me->query_enemy();
	if( !intp(i=sizeof(enemy)) 
	 || i<1 )
	        return notify_fail("你要对谁施展这一招「踏山裂石」？\n");
	        
	msg = HIB"$N"HIB"吞吐妖族精血，足下暗含周天星斗奥妙，顿时背后现出十万大山幻象，一头巨大的铁背青牛隐现其中！\n"NOR;
	msg+= HIR"$N"HIR"扬天怒吼一声，震天动地，背后巨牛幻象也身随其状，狠狠一顿脚，顿时一声振聋发聩的巨响响彻天地！\n"NOR;
	message_vision(msg,me,target);
	me->add("force",-160);
	me->receive_damage("kee",100,me);
	me->set_temp("kusong_tashan",time());
	
	me->add_temp("apply/attack",50);
	
	t = me->query_skill("dali-bang",1)/100;
	t+= me->query_skill("moshenbu",1)/100;
	msg = HIB"一道肉眼可见的波纹朝$n"HIB"直冲而去！\n"HIR"$n"HIR"顿时给震的两耳轰鸣，脚下踉跄不行！\n"NOR;
	for(i=0;i<sizeof(enemy);i++)
	{
		if( !enemy[i] || !living(enemy[i])
		 || !me->is_fighting(enemy[i])
		 || enemy[i]->is_busy()
		 || enemy[i]==me 
		 || !living(me) )
			continue;
		succ = COMBAT_D->attack_percent(me,enemy[i],TYPE_PERFORM);
		if( succ>0 )
		{
			message_vision(msg,me,enemy[i]);
			enemy[i]->start_busy(t);
		}
		else	me->add_temp("kusong_tashan",1);	
	}
	
	me->add_temp("apply/attack",-50);
	return 1;	 
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：踏山裂石 
        外功所属：魔神步法 
        外功效果：使在场与自己战斗的对象均陷入僵直状态
        	  冷却时间8秒
        	  每不中一个，冷却时间增加1秒
        外功条件：
        	  火云洞弟子
        	  人物等级15级	
        	  内力300点，消耗160点
        	  气血200点，消耗100点
                  魔神步法 150 级
                  大力棒 150 级
STR;
        me->start_more(str);
        return 1;
}