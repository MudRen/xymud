#include <ansi.h>
#include <combat.h>
inherit SSERVER;

string time_wuxing()
{
	string shi,*sym_dee = ({ "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" });
	int t = ((time()-1000000000)*60);
	mixed *local = localtime(t);
	shi = sym_dee[(local[2]%24)/2];
	switch(shi)
	{
		case "子" : return "水";
		case "丑" : return "土";
		case "寅" : return "木";
		case "卯" : return "木";
		case "辰" : return "土";
		case "巳" : return "火";
		case "午" : return "火";
		case "未" : return "土";
		case "申" : return "金";
		case "酉" : return "金";
		case "戌" : return "土";
		case "亥" : return "水";
		default   : return "NONE";
	}
}

string name(){return "「相生相克」";}

int valid_perform(object me)
{
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query_skill("wuxing-quan", 1)<50 )
        	return notify_fail("你的"+to_chinese("wuxing-quan")+"等级不足。\n");
	if( me->query("force")<100 )
        	return notify_fail("你的真气不足。\n");
	if( me->query("kee")<50 )
        	return notify_fail("你的气血不足。\n");
	return 1;
}

int check_wx(object me,object who)
{
	string wx1,wx2;
	int i;
	if( !who || !me->is_fighting(who) )
		return 0;
	i = 0;
	wx1 = FAMILY_D->family_wuxing(me);
	wx2 = time_wuxing();
	i+= SPELL_D->wuxing_xs(wx1,wx2);
	wx2 = FAMILY_D->family_wuxing(who);
	i+= SPELL_D->wuxing_xs(wx1,wx2);
	return i;
}

int perform(object me, object target)
{
	int damage,p;
	string msg;

	if( !valid_perform(me) )
        	return 0;
	if( !target )
        	target = offensive_target(me);
	if( !target
  	 || !target->is_character()
  	 || target->is_corpse()
  	 || me==target
  	 || !me->is_fighting(target) )
		return notify_fail(name()+"只能在战斗中使用。\n");

	me->add("force", -50);
	me->receive_damage("kee",10,me);

	msg = HIC"$N"HIC"单手掐咒道：金、木、水、火、土，速速归位！只见空气中突然暴开五色光球急速向$n"HIC"飞去！\n"NOR;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	if( damage>0 )
	{
		p = check_wx(me,target);
		damage = damage/5+1;
		if( p>3 )
		{
			message_combatd(HIG"$N"HIG"吸气收势，顿时觉得浑身充满了力量。\n"NOR,me);
			me->receive_curing("kee",damage);
			me->receive_heal("kee",damage);
		}
		else if( p>1 )
			COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,0,0,damage);
	}
	me->start_busy(1);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：相生相克
        外功所属：五行拳
        外功效果：对敌一击，根据双方、时辰五行相生相克不同带不同的附加效果
                  自身busy 1 秒
        外功条件：
                  人物等级 5 级
                  内力100点，消耗50点
		  气血50点，消耗10点
                  五行拳 50 级
STR;
        me->start_more(str);
        return 1;
}
