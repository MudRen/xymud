#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
	object weapon;
	string msg ,succ_msg;
	int skill,b_time,damage;
        
        if( me->query_level()<25 )
        	return notify_fail("你的人物等级不够。\n");
	if( me->query_skill_mapped("dodge")!= "yanxing-steps" )
        	return notify_fail("『锁梦缠魂』需要雁行步法的配合！\n");
	if((int)me->query_skill("wusi-mace",1)<250 
	 || me->query_skill_mapped("mace")!= "wusi-mace" 
	 ||(int)me->query_skill("wusi-mace",1)<250 )           
        	return notify_fail("你的锏法不够精深！\n");
	if((int)me->query_skill("yanxing-steps",1) < 250)
        	return notify_fail("你的『雁行步法』等级不够！\n");
	if((int)me->query("force") < 500 )              
        	return notify_fail("你体内的内力不足！\n");
        weapon = me->query_temp("weapon");
        if( !weapon
	 || ( weapon->query("skill_type")!="mace"
	   && weapon->query("use_apply_skill")!="mace" ) )
		return notify_fail("你需要一把锏！\n");	
        
	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )                
        	return notify_fail("你要对谁施展这一招『锁梦缠魂』？\n");        
	if(target->is_busy())
        	return notify_fail(target->name()+"已经手忙脚乱了！\n"); 

	skill = (int)me->query_skill("wusi-mace",1);
        	b_time = 3+skill/100;
	if(b_time > 9)
        	b_time = 9;

	msg = HIW"$N"HIW"使出无私锏法中的绝技「"HIM"锁"HIG"梦"HIB"缠"HIR"魂"HIW"」"HIW"，手中$w"HIW"如鬼似魅般缠向$n"HIW"！\n"NOR;
	succ_msg = HIC"$N"HIC"手中$w"HIC"如影随行，似灵蛇般锁住$n"HIC"的$W"HIC"！\n"NOR;
	me->add("force", -200);
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);	
	me->set_temp("pfm_msg",0);

	if( damage<1 )
	{
		message_combatd(HIY "结果被$n"HIY"奋力招架住了！\n"NOR, me,target);
		me->start_busy(1);
	}
	else	target->start_busy(b_time);	
	return 1;
}

int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        外功名称：锁梦缠魂
        外功所属：无私锏法
        外功效果：锁住对方的攻势
                  使用后自身busy 1 秒
        外功条件：
                  内力500点，消耗200点
                  无私锏法200级
                  雁行步法200级
                 
LONG;
me->start_more(str);
return 1;
}
