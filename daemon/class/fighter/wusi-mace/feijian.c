//撒手锏
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg,succ_msg;
	
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	if( time()<me->query_temp("jjf_feijian")+5 )
	        return notify_fail("你现在状态不济，使不出『撒手锏』。\n");
	if( me->query("family/family_name")!="将军府" 
 	&& me->query("chushi/chushi_jjf")!="yes")
        	return notify_fail("你不能使用这项技能！\n"); 	
        if((int)me->query_skill("wusi-mace",1)<80 )
        	return notify_fail("你的『无私锏法』等级不够！\n");
        if( me->query_skill_mapped("dodge")!= "yanxing-steps" )
		return notify_fail("『撒手锏』需要雁行步法的配合！\n");
	if((int)me->query_skill("yanxing-steps",1)<80 )
        	return notify_fail("你的『雁行步法』等级不够！\n");
	if( me->query("force")<800 )
		return notify_fail("你的内力不足。\n");
	weapon = me->query_temp("weapon");
	if( !weapon
	 || ( weapon->query("skill_type")!="mace"
	   && weapon->query("use_apply_skill")!="mace" ) )
		return notify_fail("你手里又没有锏！\n");	
	
	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )                
		return notify_fail("你要对谁施展这一招『撒手锏』？\n");        

	me->add("force", -200);
	me->set_temp("jjf_feijian",time());
	msg = HIC"$N"HIC"突然大喝一声“撒手锏”！掌中$w"+HIC"脱手飞出！在空中划出一道弧形，风驰电掣般砸向$n"HIC"的$l！\n"NOR;
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("wusi-mace",1)/5);
	message_combatd(HIC+weapon->name()+HIC"在半空打了转倒飞出去，被$N"HIC"顺势抓住。\n"NOR,me);
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：撒手锏
        外功所属：无私锏法
        外功效果：乃是将军府鞭系亲兵的绝招，传自开国元勋秦琼。
                  冷却时间5秒
        外功条件：
        	  将军府(出师)弟子
        	  人物等级8级
        	  内力800点，消耗200点
                  无私锏法80级
                  雁行步法80级并激发
LONG;
me->start_more(str);
return 1;
}

