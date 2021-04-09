// fu by yushu 2000.11
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int cast(object me, object target)
{
	object seal;
	string msg,succ_msg;
        int t,succ,pp;
	
	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n");      
	if(me->query("family/family_name")!="蜀山派")
        	return notify_fail("你不是蜀山弟子，不能使用这项技能！\n");
        if((int)me->query("mana") < 300 )
                return notify_fail("你的法力不够！\n");
        if((int)me->query("sen") < 100 )
                return notify_fail("你无法集中精力！\n");
	if((int)me->query_skill("tianshi-fufa", 1) <200)
		return notify_fail("你的天师符法不够娴熟。\n");
	if( time()<me->query_temp("shushan_ding")+6 )
		return notify_fail("你不能频繁使用「束身定」。\n");
			
	seal = present("paper seal",me);
	if( !seal || base_name(seal)!="/obj/paper_seal" )
		return notify_fail("你身上没有桃符纸，如何施「束身定」？\n");		
        if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) ) 
                return notify_fail("你要对谁施「束身定」？\n");
	if( target->is_busy() )
		return notify_fail("对方已经动弹不得了。\n");
		
        me->receive_damage("sen", 80);
        if( random(me->query_maxmana()) < 50 ) {
                write("你一着急竟然忘了咒语。\n");
                return 1;
        }
        if( seal->query_amount()<1 )
        	destruct(seal);
        else	seal->add_amount(-1);	
        
        t = me->query_skill("spells")/150+1;
        if( t<3 ) t = 3;
	//符水	符类法术伤害+5%
	if( me->query_skill("fushui",2)>100 )
		t+= (me->query_skill("fushui",1)-100)/150+1;
        pp = me->query_skill("spells")/150;
        me->add_temp("apply/attack",pp);
        succ = COMBAT_D->attack_percent(me,target,TYPE_CAST);

        me->add_temp("apply/attack",-pp);
        
        msg = HIC "\n$N"HIC"一脸肃杀之气，抬手仍出一张天师符「呼」地一下飞到半空，射向$n"HIC"！\n" NOR;
	succ_msg = HIB "$n"HIB"被光影罩住，顿时动弹不得！\n"NOR;
	message_vision(msg,me,target);
	me->set_temp("shushan_ding",time());
	me->add("mana",-150);
	me->receive_damage("sen",50,me);
	if( succ>0 )
	{
		message_combatd(succ_msg,me,target);
		target->start_busy(t);
	}	
	else
	{
		message_combatd(HIR"但是$n"HIR"伸指一弹，红光一暗，结果扑！地一声天师符凭空化去！\n"NOR,me,target);
		me->add_temp("shushan_ding",t/2+2);
	}
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：束身定
        法术所属：天师符法
        法术效果：祭天师符使对方至少busy 3 秒
                  冷却时间 6 秒，失败则增加冷却时间为效果时间的一半
                  不可对busy状态下的对象使用
        法术条件：
                  蜀山派弟子
        	  人物等级20级
        	  需要桃符纸
                  法力300点，消耗150点
                  精神100点，消耗80点
                  天师符法200级
STR;
        me->start_more(str);
        return 1;
}
