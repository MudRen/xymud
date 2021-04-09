//破釜沉舟
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
object weapon;
string msg;
int skill,extra,ap,dp,damage;
	
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");
	if((int)me->query("force")<1500 )
        	return notify_fail("你体内的内力不足。\n");           
	if((int)me->query_skill("changquan",1)<300)
        	return notify_fail("你的『长拳』等级不够！\n");
	if( me->query("kee")<500 )
        	return notify_fail("你的状态不佳，使不出『破釜沉舟』。\n");
	weapon = me->query_temp("weapon");
	if( weapon )
	{
		if( weapon->query("skill_type")!="unarmed" && weapon->query("use_apply_skill")!="unarmed" )
			return notify_fail("这是拳法的绝技。\n");
	}		
	if((string)me->query_skill_mapped("unarmed")!="changquan")
		return notify_fail("这是拳法的绝技。\n");

	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招『破釜沉舟』？\n");

	if( !(__DIR__"hengsao.c")->perform(me,target) )
        	return 0;
        if( !me || !living(me) )
        	return 0;
        if( me->query("force")<500 || me->query("kee")<500 )
        {
        	message_combatd("$N内力不继，停住了攻击。\n",me);
        	return 1;
        }
        if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )
        {
        	message_combatd("$N难觅敌手，停住了攻击。\n",me);
        	return 1;
        }
  	
	me->stop_busy();
	me->reset_action();
	me->receive_damage("kee",100,me);
	me->add("force",-100);

	msg = HIR"$N"HIR"一轮攻击之后，但觉血气上冲，手下并不停止攻击，又使出『破釜沉舟』！\n"NOR;
	msg+= CYN"$N"CYN"收拳为肘，整个人狠狠撞向$n"CYN"！\n"NOR;
	me->add_temp("apply/attck",30);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	me->add_temp("apply/attck",-30);	
	if( me->query("force")<200 || me->query_skill("changquan",1)<500 )
	{
		me->start_busy(3);
		return 1;
	}
	 
	me->add("force",-100); 
	msg = CYN"$N并不停止攻击，顺势扣住$n"CYN"的手腕，往外一摔！\n"NOR;
	me->add_temp("apply/attck",50);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("unarmed"));
	me->add_temp("apply/attck",-50);
	me->start_busy(3);
	return 1;
}               

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：破釜沉舟
        外功所属：长拳
        外功效果：发挥长拳的真谛，对敌进行横扫千军，并发出后续攻击
                  使后自身busy 3 秒
        外功条件：
                  内力修为十六年
                  内力1000点，消耗400-600点
                  气血500点，消耗100点
                  长拳350级
LONG;
me->start_more(str);
return 1;
}  

