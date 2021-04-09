// bugong.c 霸王枪法之不攻
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string succ_msg,msg,tmp,skill;
	object weapon,weapon2;
	int i ,b_time, mkee,damage;
        
        if( me->query_level()<15 )
        	return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name") != "将军府" )
        	return notify_fail("你是哪儿偷学来的武功，也想用不攻！\n");
	if( (int)me->query_skill("lengquan-force", 1) < 150 )
        	return notify_fail("你的冷泉心法还差些火候。\n");
	if( (int)me->query_skill("yanxing-steps", 1) < 150 )
        	return notify_fail("你的雁行步法无法配合不攻。\n");
	if( (int)me->query_skill("bawang-qiang", 1) < 150 )
        	return notify_fail("你的霸王枪法不够娴熟，不能采用不攻。\n");
	if( time()<me->query_temp("jjf_bugong")+6 )
		return notify_fail("你还是休息休息再用。\n");
	weapon=me->query_temp("weapon");
	if( !weapon
	 || ( weapon->query("skill_type")!="spear"
	   && weapon->query("use_apply_skill")!="spear" ) )
        	return notify_fail("你没用枪，怎么使出不攻！\n");
	if(me->query("force") < 200) 
		return notify_fail("你的内力太少。\n");
	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) ) 
		return notify_fail("不攻只能对战斗中的对手使用。\n");
	if( target->is_busy() )
        	return notify_fail(target->name() + "还在犹豫不决，放胆攻击吧。\n");
        	
	b_time = (int)me->query_skill("bawang-qiang") / 40 + (int)me->query_skill("yanxing-steps") / 40;
	if(b_time < 3) b_time = 3;
	if(b_time > 8) b_time = 8; 
	
	msg = HIC"$N"HIC"手中$w"HIC"猛抖，脚踏奇步，登时涌起凛冽杀气，遥罩$n"HIC"，似攻非攻，似守非守!"HIR"不攻"HIC"一出，$n"HIC"立时感到若不主动进攻，将陷於被动挨打的劣势。\n"NOR;
	succ_msg = HIR"$n"HIR"连忙上前猛攻,但是却无从着手，不由陷入了两难的境地。\n"NOR;
	me->set("actions",([
		"damage": 135,
        	"dodge" : -20,
		"parry" : -25,
		"damage_type":  "刺伤",
        ]));
        me->add("force",-200);
        me->set_temp("jjf_bugong",time());
        me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
	me->set_temp("pfm_msg",0);
	me->reset_action();
	if( damage>0 ) 
        	target->start_busy(b_time);
	else    
	{
        	msg = HIM"可是$n"HIM"也并不着急,反而收起兵刃急退数步。\n" NOR;
        	message_combatd(msg,me,target);
        }
	if( me->query_skill("spear",1)>400 
  	 && me->query("force")>300 )
	{
		me->add("force",-200);
        	msg = CYN"\n$N"CYN"见机紧握$w"CYN"，顺势上枪直刺$n"CYN"$l！\n"NOR;
        	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
        	if( damage>0 )
        	{
        		msg = CYN"\n$N"CYN"见一枪命中，双手一攥，$w"CYN"抖出碗大的一个枪花，直扑$n"CYN"$l！\n"NOR;
        		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("spear")/10);
        	}
	}
	return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：不攻有悔
        外功所属：霸王枪法
        外功效果：以缜密的枪法迷惑对手，使之busy3-8秒
                  冷却 6 秒 
                  霸王枪法修为够高后会追击2击，内力消耗增加200点
                  内功，法术和外功
        外功条件：
        	  将军府弟子
        	  人物等级15级
                  内力200点，消耗200点
                  霸王枪法150级
                  冷泉心法150级
                  雁行步法150级
LONG;
me->start_more(str);
return 1;
}

