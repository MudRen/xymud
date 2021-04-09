// sanqing.c 一剑化三清
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int damage;
        
        if( me->query_level()<20 )
        	return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="五庄观" 
        && me->query("chushi/chushi_wzg")!="yes")
        	return notify_fail("这是五庄观绝学。\n");
        if( !me->is_knowing("wzg_sanqing") && userp(me) && !wizardp(me) )	
		return notify_fail("你不能使用这项技能！\n");
	weapon = me->query_temp("weapon");
        if( !weapon 
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") )
		return notify_fail("「一剑化三清」开始时必须拿着一把剑！\n");	  
	if( (int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");
        if( (int)me->query_skill("sanqing-jian",1) < 180 )
                return notify_fail("你的三清剑法还不到家，无法使用「一剑化三清」！\n");
       if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("「一剑化三清」只能在战斗中使用。\n");
        
        msg = YEL"$N"YEL"使出三清剑法的绝技「一剑化三清」，一招连环三剑，攻向$n"YEL"！\n" NOR;
        message_vision(msg, me,target);
        me->add("force", - 200);
	me->set_temp("pfm_msg",1);

	msg = HIY"\t混元初判道如先，常有常无得自然；紫气东来三万里，函关初度五千年。\n"NOR;
	damage = COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	if( damage>0 )
	{
		message_combatd(HIC"\n$N"HIC"背后隐现一尊头戴九云冠，穿大红白鹤绛绡衣，骑兽仗剑的道尊，随势朝$n"HIC"也刺一剑！\n"NOR,me,target);
		target->receive_damage("kee",damage/5+1,me,TYPE_PERFORM);
		COMBAT_D->report_status(target);
	}	
	
        
        msg =  HIY"\n\t函关初出至昆仑，一统华夷属道门；我体本同天地老，须弭山倒性还存。\n"NOR;
	damage = COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	if( damage>0 )
	{
		message_combatd(HIC"\n$N"HIC"背后隐现一尊头戴如意冠，身穿淡黄八卦衣，骑天马的道尊，随势将手中灵芝如意朝$n"HIC"一砸！\n"NOR,me,target);
		target->receive_wound("kee",damage/5+1,me,TYPE_PERFORM);
		COMBAT_D->report_status(target,1);
	}  
	      
       
        msg = HIY"\n\t混沌从来不计年，鸿蒙剖处我居先；叁同先天地玄黄理，任我傍门望眼穿。\n"NOR;
	damage = COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM,msg);
	if( damage>0 )
	{
		message_combatd(HIC"\n$N"HIC"背后隐现一尊头戴九霄冠，身穿八宝万寿紫霞衣，骑地狮的道尊，随势将左手龙须扇朝$n"HIC"一扇，又将右手三宝玉如意朝$p祭去！\n"NOR,me,target);
		target->receive_wound("kee",damage/5+1,me,TYPE_PERFORM);
		target->receive_damage("kee",damage/5+1,me,TYPE_PERFORM);
		COMBAT_D->report_status(target,1);
		COMBAT_D->report_status(target);
	} 
	me->set_temp("pfm_msg",0); 
        me->start_busy(1);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：一剑化三清
        外功所属：三清剑法
        外功效果：连续攻击对方三次，并以道器凝聚三清法身攻击对方
                  自身busy 1 秒
                  需领悟
        外功条件：
        	  五庄观(出师)弟子	
        	  人物等级20级	
                  内力500点，消耗200点
                  三清剑法 180 级
STR;
        me->start_more(str);
        return 1;
}