#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object who)
{
	if( who )
	{
		who->delete_temp("bhg_mingyu");
		who->delete_temp("no_condition");
		who->set_temp("bhg_mingyu",time());
		message_vision(HIG"\n$N"HIG"撤去明玉神功，周身颜色渐渐恢复了正常。\n"NOR,who);
	}
}

int exert(object me, object target, int amount)
{
        int force, lvl;
	if( !target ) target = me;        
        if( me->query_level()<15 )
        	return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name") != "百花谷" )
    		return notify_fail("你是哪儿偷学来的武功！\n"); 
    	if( me->query("force")<500 )
    		return notify_fail("你的内力不足。\n");
    	if( me->query_skill("brightjade-force",1)<150 )
    		return notify_fail("你的明玉神功不够纯熟。\n");
        if( time()<me->query_temp("bhg_mingyu")+60 )
    		return notify_fail("你不能频繁使用此招。\n");
    	if( me->query("kee")<300 )
    		return notify_fail("你体力不支。\n");
    	if( me->query_temp("bhg_mingyu") )
    		return notify_fail("你已经是施展了明玉诀了。\n");
    						
    	message_vision(HIG"\n$N"HIG"黙运神功，周身碧玉剔透，宛如明玉，一切邪法不能近身。\n"NOR,me);
    	me->add("force",300);
    	me->receive_damage("kee",200);
    	me->set_temp("no_condition",HIG"\n$N"HIG"周身碧玉剔透，宛如明玉，一切邪法不能近身。\n"NOR);
    	me->set_temp("bhg_mingyu",1);
    	if( me->is_fighting() )
    		me->start_busy(3);
    	me->start_call_out( (: call_other, __FILE__, "remove_effect", me:),me->query_skill("force")/20);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        内功名称：明玉诀
        内功所属：明玉心法
        内功效果：使自身一定时间内毒攻击免疫
                  状态结束后冷却一分钟
        内功条件：
        	  人物等级 15 级
                  内力500点，消耗300点
                  气血300点，消耗200点
                  明玉神功150级
STR;
        me->start_more(str);
        return 1;
}

void remove()
{
	int i;
	object who,*usr = users();
	remove_call_out("remove_effect");
	if( i=sizeof(usr)>0 )
	{
		while(i--)
		{
			if( !usr[i] || !environment(usr[i])
			 || !objectp(usr[i]) )
				continue;
			if( usr[i]->query_temp("bhg_mingyu") )
			{
				who = usr[i];
				who->delete_temp("bhg_mingyu");
				who->delete_temp("no_condition");
				who->set_temp("bhg_mingyu",time());
				message_vision(HIG"\n$N"HIG"撤去明玉神功，周身颜色渐渐恢复了正常。\n"NOR,who);
			}
		}
	}
} 
