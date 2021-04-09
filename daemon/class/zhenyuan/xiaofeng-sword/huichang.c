//by fly 6-6-2000
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon;
        int damage, p,b;
        string msg, succ_msg;

	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name") != "五庄观"
	 && me->query("chushi/chushi_wzg")!="yes" )
		return notify_fail("「荡气回肠」是五庄观不传之密！\n");
        if( time()-(int)me->query_temp("wzg_huichang") < 4 )
                return notify_fail("绝招用多就不灵了！\n");
        if( (int)me->query_skill("xiaofeng-sword", 1) < 80 )
                return notify_fail("你的晓风残月剑法还不够熟练，不能使用"+HIR"荡气回肠"NOR+"对敌！\n");
        if( (int)me->query_skill("sword", 1) < 80 )
                return notify_fail("你的剑法不够娴熟，使不出"+HIR"荡气回肠"NOR+"！\n");
	if( me->query_skill_mapped("sword") != "xiaofeng-sword" 
	|| me->query_skill_mapped("parry") != "xiaofeng-sword")
                return notify_fail("你的剑法招架激发不够准确,使不出"+HIR"荡气回肠"NOR+"！\n");
	weapon = me->query_temp("weapon");                
	if( !weapon 
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") )
		return notify_fail("你没有剑，如何能发出「荡气回肠」？\n");
        if( (int)me->query("force") < 600 )
                return notify_fail("你现在内力不足，使不出"+HIR"荡气回肠"NOR+"！\n");     
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("["+HIR"荡气回肠"NOR+"]只能对战斗中的对手使用。\n");

	msg = HIC"$N"HIC"一声朗笑,手中$w"HIC"斜指向天,剑尖吐出一团尺余的银芒,似有灵性般吞缩不定！突然之间，$N"HIC"剑交右手，寒光一闪，剑拉弧形，阵阵森森剑气直逼向$n"HIC"$l！\n"NOR;
	succ_msg = HIR"$n"HIR"大吃一惊，变招不及，$w"HIR"已在$p的$l对穿而出，鲜血溅了一地！\n"NOR;
	me->add("force",-80);
	me->set_temp("wzg_huichang",time());
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
	{
		me->add_temp("wzg_huichang",2);
		message_combatd(HIY"$n"HIY"却识得那团剑芒的厉害，早已远远避在一边。\n" NOR,me,target);
	}
			
	if( me->query_skill("xiaofeng-sword",1)<120 || me->query("force")<300 )
		return 1;
	
        msg = HIG "\n紧跟着，$N"HIG"随式一转，右跨一步，$w"HIG"蓦地抖了几抖，剑势似是千变万化，剑气万重。\n"NOR;
	succ_msg = HIR"只听$n"HIR"一声惨嚎,剑气从$l掠过，$p顿时觉得浑身气血无法凝聚。\n"NOR;
	me->add("force",-50);
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/5);
	me->set_temp("pfm_msg",0);	
	if( damage<1 )
	{
		me->add_temp("wzg_huichang",2);
		message_combatd(HIY"$n"HIY"身随敌动，轻轻一带，竟然躲过$N"HIY"的攻击。\n" NOR,me,target);
	}
	
	if( me->query_skill("xiaofeng-sword",1)<150 || me->query("force")<300 )
		return 1;	
                
       	msg = HIW "\n紧接着，$N"HIW"飞身向前，身剑合一，所幻的光圈一圈一圈，$n"HIW"全身已被套其中\n"NOR;
       	succ_msg = HIR"$w"HIR"顿时刺穿$n"HIR"的$l，鲜血染红了$p的半边身子！\n"NOR;
	me->add("force",-30);
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/5);
	me->set_temp("pfm_msg",0);
	if( damage<1 )
	{
		me->add_temp("wzg_huichang",2);
		message_combatd(HIY"$n"HIY"却识得此间厉害，看破八卦方位，中宫直入，自生门而出，躲开了此招。\n" NOR,me,target);
	}
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：荡气回肠
        外功所属：晓风残月剑
        外功效果：对敌攻击，最多攻击三次，后两次带固定伤害
                  冷却时间4秒，未命中，则增加2秒每次
        外功条件：
        	  五庄观(出师)弟子
        	  人物等级8级	
        	  剑法激发晓风残月剑
        	  招架激发晓风残月剑
                  内力600点，消耗80点，第二击消耗50点，第三击消耗30点
                  晓风残月剑 80 级
                  基本剑法 80 级
                  
STR;
        me->start_more(str);
        return 1;
}