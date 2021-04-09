// 清歌妙舞 Dance.c
// Cracked by 凌惊雪 12-15-2002
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int valid_perform(object me)
{
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");	
	if(me->query("family/family_name")!="月宫"
    	&& me->query("chushi/chushi_moon")!="yes")
		return notify_fail("你不能使用这项技能！\n");
    	if(me->query_skill("snowsword",1)/10+me->query_skill("moondance",1)/10<20) 
    		return notify_fail("你的风回雪舞剑与冷月凝香舞还不够纯熟，怕是无法起舞！\n");
    	if(me->query_per()<30 )
        	return notify_fail("你的舞姿这么难看，也好意思起舞。\n");
    	if((string)me->query_skill_mapped("force")!="moonforce")
        	return notify_fail("［清歌妙舞］必须以圆月心法为底子。\n");
    	if(me->query("max_force")<1000)
        	return notify_fail("你的内力不足，难以起舞。\n");
	return 1;	
}

int perform(object me, object target)
{
	string msg,str;
    	int extra,i,damage;
    	object weapon;
	
	if( !valid_perform(me) )
		return 0;
    	extra = me->query_skill("snowsword",1)/10+me->query_skill("moondance",1)/10;
    	if((int)me->query("force")<500 )
        	return notify_fail("你的内力不足！\n");
        	
    	if( !target ) target = offensive_target(me);
    	if( !target
    	 || !target->is_character()
    	 || !me->is_fighting(target) )
		return notify_fail("［清歌妙舞］只能对战斗中的对手使用。\n");

	extra += (int)me->query_per()/10;
    	
	message_vision(HIM  "$N"HIM"仰天长叹：蒹霞苍苍，白露为霜，所谓伊人，在水一方。随着歌声$N"HIM"翩翩起舞。\n" NOR,me,target);
	if( random(me->query_per()+target->query("per"))>=target->query("per") )
		message_combatd(HIM "$n"HIM"听着$N"HIM"凄婉的歌声，看着醉人的舞步，全然忘了自己在战斗中。\n" NOR, me, target);
	else	message_combatd(HIM "$n"HIM"虽不为所动，却也不由自主的放缓了攻击。\n" NOR, me, target);	
    	me->add_temp("apply/attack",extra);
	me->add("force",-50);
	
	msg = HIC"$N"HIC"身如飘萍随风舞，剑若流星破长空。手中的$w"+HIC"闪电般向$n"HIC"攻出！\n"NOR;
    	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	msg =  HIG "\n------天仙降临------\n"NOR;
    	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/10);
    	msg =  HIR "\n------天各一方------\n"NOR;
    	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/8);
    	
    	if( me->query_skill("snowsword",1)>=120 && me->query("force")>50 )
    	{
    		me->add("force",-50);
    		msg =  HIB "\n------峰回路转------\n"NOR;
    		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/5);
    		msg =  HIC "\n------闭月羞花------\n"NOR;
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/3);
	}    	
    	if( time()-(int)me->query_temp("wuxue_end") > 5
	 && me->query_skill("snowsword",1)>=240 && me->query("force")>50 )
    	{
		msg =  MAG "\n------绝世之容------\n"NOR;
		me->set_temp("WX_perform",10);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,"头部",extra/2);
		//////////如果和PerFORM Tian或者PerFORM Flower连用则没有此招
    		if( time()-(int)me->query_temp("wuxue_end") > 5 )
    		{
     			msg =  HIW "\n***万仙临界の天人合一*** \n"NOR;
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,"头部",extra);
		}    
	}	
    	msg =  HIM "\n$n皤然醒悟，发现自己迷恋$N的歌声和舞姿而忘了攻击。\n"NOR;
    	message_combatd(msg, me, target);
    	me->add_temp("apply/attack",-extra);
    	me->delete_temp("WX_perform");    
	me->start_busy(2);
    	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：清歌妙舞
        外功所属：回风雪舞剑
        外功效果：对敌连续进行三次攻击，如上一击未命中则下一击伤害叠加。
        	  回风雪舞剑达120级增加2次攻击，内力消耗增加50点
        	  回风雪舞剑达240级增加2次要害攻击，内力消耗增加50点
        	  使用过漫天飞雪或天女散花后，最多只会5次连击
                  使用后自身busy2秒
        外功条件：
        	  月宫(出师)弟子	
        	  人物等级10级
        	  内力修为100年
                  内力500点，消耗50点
                  内功激发圆月心法
                  后天魅力大于30
                  风回雪舞剑与冷月凝香舞之和达到200级
                  
STR;
        me->start_more(str);
        return 1;
}
