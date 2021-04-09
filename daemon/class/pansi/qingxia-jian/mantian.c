// mantian.c 青霞漫天
#include <ansi.h>
#include <combat.h> 
inherit SSERVER;

int perform(object me,object target)
{
        string msg,succ_msg,tmp;
        int skill, damage;
	
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name")!="盘丝洞")
        	return notify_fail("你从哪里偷来的功夫？\n"); 
        if( (int)me->query("force") < 300 )
                return notify_fail("你现在的内力不足！\n");
	if( me->query_skill("sword")<150
	 || me->query_skill_mapped("sword") != "qingxia-jian" )
	 	return notify_fail("你青霞剑法的修为不够，不能使用「青霞漫天」! \n");
	if( me->query_skill("force")<150
	|| me->query_skill_mapped("force") != "jiuyin-xinjing" ) 
		return notify_fail("你九阴心经的修为不够，不能使用「青霞漫天」! \n");
	if( time()<me->query_temp("shushan_mantian")+6 )
		return notify_fail("绝招用多就不灵了。\n");
				
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("「青霞漫天」只能在战斗中使用。\n");

	me->set_temp("shushan_mantian",time());
	if( me->query_skill("qingxia-jian")>=350 )
		tmp = "星点剑影";
	else	tmp = "丝丝剑气";	
        msg = HIG "$N"HIG"忽然向后疾退两步，气沉丹田，力贯剑身，霎时$w"HIG"崩出"+tmp+"！\n"HIM"★★★★★"HIC"青霞漫天"HIM"★★★★★\n"HIG"－－无数剑片铺天盖地向$n"HIG"飞射而去。\n"NOR;
	me->add("force",-200);
	skill = me->query_skill("sword")/5;
	skill = skill/2+random(skill/2);
	if( me->query_skill("qingxia-jian")>=350 )
		tmp = "剑影";
	else	tmp = "剑气";	
	succ_msg =  HIW"$n"HIW"面前仿佛涌起万丈青色霞光，惊愕之下，"+chinese_number(skill)+"道"+tmp+"已然嵌在了自己身上，$n"HIW"惨叫一声，脸上露出极为痛苦的表情。\n"NOR;
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
	{
		me->add_temp("shushan_mantian",3);
		message_combatd(HIC"只见$n"HIC"不敢怠慢，脚一点地疾飞冲天，堪堪躲过了这满天的剑片。\n"NOR,me,target);
		return 1;
	}
	damage = damage/3+1;
	target->receive_wound("kee",damage,me,TYPE_PERFORM);
	COMBAT_D->report_status(target,1);
        if( me->query_skill("qingxia-jian",1)<240 || me->query("force")<200 )
        	return 1;
        me->add("force",-200);	
	msg = HIW"\n$N"HIW"突然向后疾退两步，力惯$w"HIW"，三寸剑芒吞吐，手腕一振，竟然使出了青霞剑法密传绝技！\n"HIM"★★★★★"HIC"青霞剑芒"HIM"★★★★★\n"HIC"万点剑芒云起风涌，如清风拂铃，如靡音过耳罩向$n"HIC"。\n" NOR;
	succ_msg = HIR"$n"HIR"对付这招显然束手无策，万道剑芒打在了身上，惨叫一声，脸上露出极为痛苦的表情。\n"NOR;
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",30);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,damage*2);
	me->add_temp("apply/attack",-30);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIC"只见$n"HIC"显然老练至极，脚一点地疾飞冲天，堪堪躲过了这满天的剑芒。\n"NOR,me,target);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：青霞漫天
        外功所属：青霞剑法
        外功效果：打击对方气血后限
                  青霞剑法240级后追加一击，内力消耗增加200
                  冷却时间6秒，如第一击不中，冷却时间增加3秒
        外功条件：
                  盘丝洞弟子
        	  人物等级10级
                  内力300点，消耗200点
                  基本剑术有效等级150，并激发青霞剑法
                  基本内功有效等级150，并激发九阴心经
STR;
        me->start_more(str);
        return 1;
}	