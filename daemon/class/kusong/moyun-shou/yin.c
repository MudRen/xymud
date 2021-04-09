#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int succ,k,t,p;
	string msg,succ_msg,name,long;
	
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name")!="火云洞"
	 && me->query("chushi/chushi_kusong")!="yes" )
        	return notify_fail("「五岳镇印」只有火云洞门人才可以用！\n");		
	if( time()-(int)me->query_temp("kusong_yin")<7 )
       		return notify_fail("绝招用多就不灵了！\n"); 
        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");
	if( me->query("kee")<300 )
		return notify_fail("你现在状态不佳。\n");                
        if((int)me->query_skill("moyun-shou", 1) < 100)
                return notify_fail("你的摩云手级别还不够，使用这一招会有困难！\n");
	weapon = me->query_temp("weapon");
	if( weapon )
	{
		if( weapon->query("skill_type")!="unarmed" && weapon->query("use_apply_skill")!="unarmed" ) 
			return notify_fail("你的摩云手级别还不够，使用这一招会有困难！\n");
	}
	                
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要对谁施展「五岳镇印」？\n");
	
	if( target->is_blind() )
		return notify_fail("对方已经那样了，不需你镇压了。\n");
	
	k = me->query_skill("moyun-shou",1);
	t = me->query_skill("spells")/100;
	p = me->query_skill("unarmed")/10;
	
	me->add_temp("apply/attack",p);
	
	if( k<120 )
	{
		name = "嵩山";
		long = "山势挺拔，层峦叠嶂";
		t+= 1;
	}
	else if( k<180 )
	{
		name = "恒山";
		long = "沟谷深邃，峰起谷落";
		t+= 1;
	}
	else if( k<240 )
	{
		name = "衡山";
		long = "古木参天，景深幽秀";
		t+= 1;
	}	
	else if( k<320 )
	{
		name = "华山";
		long = "奇拔俊秀，陡直险峻";
		t+= 1;
	}	
	else
	{
		name = "泰山";
		long = "巍峨陡峻，气势磅礴";
		t+= 1;
	}		
	 	
	msg = HIR"$N"HIR"大喝一声，双掌血筋虬结，腾起半丈高的血雾，夹带着远古妖脉在半空中结起一个巨大的印咒！\n"NOR;
	message_vision(msg,me);
	me->receive_damage("kee", 100);
	me->add("force",-200);

	msg = HIG"$N"HIG"背后现出十万大山的异象，随着$P双掌舞动，一座"+long+"的"+name+"呼啸而出，宛如实体，带着千钧风雷之声压向$n"HIG"！\n"NOR;
	message_combatd(msg,me,target);
	
	succ_msg = HIY"“轰隆”一声巨响，惊彻天地，$n"HIY"被整个的镇压住，动弹不得。\n"NOR;
	
	me->add_temp("apply/attack",p);
	succ = COMBAT_D->attack_percent(me,target,TYPE_PERFORM);
	
	if( succ>0 )
	{
		message_combatd(succ_msg,me,target);
		target->start_blind(t,HIY"你被"+me->name()+HIY"用「"+name+"印」镇压住了。\n"NOR);
	}	
	else	message_vision(HIC"$n"HIC"窥破虚空，将"+name+"虚像击了个粉碎！\n"NOR,me,target);
	me->start_busy(2);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：五岳镇印
        外功所属：摩云手
        外功效果：以远古妖脉将对手一定时间内镇压当场(陷入静默状态)
                  自身busy 2 秒
        外功条件：
        	  火云洞(出师)弟子
        	  人物等级10级	
        	  内力500点，消耗200点
        	  气血300点，小号100点
                  摩云手 100 级
STR;
        me->start_more(str);
        return 1;
}