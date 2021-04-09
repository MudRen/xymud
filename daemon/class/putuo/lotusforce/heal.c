//moonforce--heal.c
#include <ansi.h>
inherit F_CLEAN_UP;

void do_heal(object who,int t);

int valid_exert(object me)
{
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");
        if( (int)me->query("force") < 500 )
                return notify_fail("你的真气不够。\n");
	if( me->query_skill("lotusforce",1)/5<=0 )
		return notify_fail("你的莲台心法级别还不够！\n");                
	return 1;
}

int exert(object me, object target)
{
	int t;
	if( !valid_exert(me) )
		return 0;	
        if( me->is_fighting() )
                return notify_fail("战斗中运功疗伤？找死吗？\n");
        if( (int)me->query("eff_kee") < (int)me->query_maxkee() /4 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");
	if( time()<me->query_temp("putuo_heal")+15 )
		return notify_fail("绝招用多就不灵了。\n");
	if( me->query_temp("heal") )
		return notify_fail("你目前已经在疗伤状态了。\n");
	t = me->query_skill("lotusforce",1)/5;		
	if( t>45 )
		t = 45;	
	message_vision(HIY"$N"HIY"运转「莲台心法」，背后隐现金莲异象，随着阵阵梵呗之音，一股股浓郁的念力笼罩$N"HIY"全身。\n"NOR,me);
	me->add("force",-100);
	me->set_temp("heal",1);
	me->set("force_factor", 0);
	call_out("do_heal",0,me,t);
        return 1;
}

void remove_eff(object who)
{
	if( !who )
		return;
	message_vision(HIY"$N"HIY"背后的金莲异象渐渐淡出。。。。\n"NOR,who);
	who->set_temp("moon_heal",time());
	who->delete_temp("heal");
}			

void do_heal(object who,int t)
{
	int p;
	if( !who )
		return;
	if( t<=0 || who->query("force")<10 || !living(who) )
	{
		remove_eff(who);
		return;
	}
	who->add("force",-10);
	message_combatd(HIY"$N"HIY"背后金莲一开一合间隐含天道，道道金光将其笼罩住。。。。\n"NOR,who);
	p = who->query_spi()+who->query_str();
	if( p>110 )
		p = 110;
	p = p/2+random(p);
	p+= p*(int)who->query_temp("apply/receive_curing_kee")/100;
	who->receive_curing("kee", p+1);
	if( p/10>0 )
		who->receive_heal("kee",p/10);
	t--;
	call_out("do_heal",0,who,t);
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        内功名称：疗伤诀
        内功所属：莲台心法
        内功效果：运转莲台心法，利用佛光一定时间内持续治疗和恢复自身气血
                  使用后冷却15秒
        内功条件：
        	  人物等级 5 级
        	  内力500点，消耗100点，恢复期间每恢复一次，消耗10点
        	  莲台心法 25 级
STR;
        me->start_more(str);
        return 1;
}
