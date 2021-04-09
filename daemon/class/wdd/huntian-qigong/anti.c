#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me,int lvl)
{
	if( me )
	{
		me->add_temp("apply/combat_def",-lvl);
		me->add_temp("apply/spells_def",-lvl);
		me->add_temp("apply/defense",lvl);
		me->add_temp("apply/spells_dodge",lvl);
		me->delete_temp("powerup");
		message_vision(YEL"$N"YEL"身上的厚土化作了粉末。\n"NOR,me);	
	}
}
int exert(object me, object target)
{
	int lvl;
        
        if( me->query_level()<20 )
        	return notify_fail("你的人物等级不够。\n");
        if( me->query_skill("huntian-qigong",1)<200 )
        	return notify_fail("你的混天气功不够娴熟。\n");
	if( me->query("family/family_name")!="陷空山无底洞"
         && me->query("chushi/chushi_wdd")!="yes" )
		return notify_fail("你不能使用这项技能！\n");
	if( me->query("force")<300 )
		return notify_fail("你的内力不够！\n");
	if( me->query_temp("powerup") )
		return notify_fail("你已经被祝福了，不能再施展「安体诀」了。\n");
	if( !target )
		target = me;		
        if( target != me ) 
        	return notify_fail("你只能对自己使用。\n");

	message_vision(YEL"$N"YEL"运起混天气功就地打了个滚，尘土飞扬之中，浑身顿时裹了一层硬土，好似穿上了一件盔甲。\n"NOR,me);
	me->add("force",-200);
	me->set_temp("powerup",1);
	lvl = me->query_skill("force")/60+me->query_level()/5;
	me->add_temp("apply/combat_def",lvl);
	me->add_temp("apply/spells_def",lvl);
	me->add_temp("apply/defense",-lvl);
	me->add_temp("apply/spells_dodge",-lvl);
	if( me->is_fighting() )
		me->start_busy(2);
        me->start_call_out( (: call_other, "/daemon/class/wdd/huntian-qigong/anti.c", "remove_effect", me, lvl:),me->query_skill("force")/10);
        return 1;
}
 
int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        内功名称：安体诀
        内功所属：混天气功
        内功效果：一定时间内降低自身的闪避同时加强自身的物理和法术防御
                  战斗中使用，自身busy 2 秒
        内功条件：
        	  无底洞(出师)弟子	
        	  人物等级 20 级
                  内力300点，消耗200点
                  混天气功 200 级
STR;
        me->start_more(str);
        return 1;
}