//Cracked by Roath
// sheqi.c 摄气，摄取阳气。weiqi...
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int exert(object me, object target)
{
	int damage;
	string msg,succ_msg; 

	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name") != "阎罗地府")
        	return notify_fail(HIG"「摄气诀」"+NOR"是地府不传之密！\n");	
        	
	if( !target ) target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me
 	 || !me->is_fighting(target) )
    		return notify_fail("你要对谁使用摄气诀？\n");
	if(target->query_temp("netdead")) 
        	return notify_fail("趁火打劫，不太像话吧？\n");
	if( (int)me->query_skill("tonsillit", 1) <250 )
        	return notify_fail("你的摄气诀修为太低，不能摄取阳气。\n");
	if( (int)me->query("kee")>me->query("eff_kee") )
        	return notify_fail("你现在气太过充盈，再吸就要爆炸了。\n");
        if( me->query("force")<100 )
        	return notify_fail("你内力不足。\n");
        if( target->query("kee")<50 )		
        	return notify_fail("对方马上就要断气，没有什么好榨的了。\n");
        	
        msg = HIR"$N"HIR"面带狞笑，露出白森森的牙齿往$n"HIR"的鼻孔凑了过去，张嘴就是一吸！\n"NOR;
        succ_msg = HIR "结果$p头皮一麻，只觉得体内阳气源源不断地流了出去！\n" NOR;
	me->set_temp("pfm_msg",1);
	me->add("force",-30);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_CAST,msg,succ_msg);
        me->set_temp("pfm_msg",0);        
        if( damage<1 )
        	message_combatd(HIR "结果$p一扭头，避了开去！\n" NOR,me,target);
        else
        	me->receive_curing("kee",damage/2+1);
	me->start_busy(2);
	return 1;
}

int help(object me)
{
string str;
if ( !me )      return 0;
str = @LONG
        内功名称：摄气诀
        内功所属：摄 气 诀
        内功效果：将对对方伤害的50%转化为自身的气血
                  自身busy 2 秒
        内功条件：
        	  地府弟子
        	  人物等级30级	
                  内力100点，消耗30点
                  气血200点
                  摄气诀250级
LONG;
me->start_more(str);
return 1;
}

