// 雪风刀波 daobo.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	int damage,base_damage;
	string msg,succ_msg;
	object weapon;

	if( me->query_level()<15 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name") != "大雪山" 
	 && me->query("chushi/chushi_xueshan")!="yes" )
        	return notify_fail("你是哪儿偷学来的武功！\n");
	if( (int)me->query_skill("ningxie-force", 1) < 150 )
		return notify_fail("你的冰谷凝血功不够级别，无法发出刀波。\n");
	if( (int)me->query_skill("dodge", 1) < 150 )
		return notify_fail("你的轻功身法不够灵活，无法控制身法发出刀波。\n");
	if( me->query_skill("bingpo-blade",1)<150 )
		return notify_fail("你的冰魄寒刀等级不够。\n");
	if( me->query_skill("blade",1)<150 )
		return notify_fail("你的刀法基础太差。\n");		
	if( (int)me->query("force", 1) < 500 )
		return notify_fail("你现在内力太弱，无法发出刀波。\n");
	//if( me->query_temp("ningxie") || me->query_temp("pfm_action") ) 
	//	return notify_fail("「雪风刀波」与「冰谷凝血」搭配有违天和！\n");
				
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
		return notify_fail("你没有刀，如何能发出刀波？\n");	  
		
        if( !target ) 
        	target = offensive_target(me);
         if( !target || !target->is_character()
          || target==me || target->is_corpse() 
	  || !me->is_fighting(target) )
		return notify_fail("「雪风刀波」只能对战斗中的对手使用。\n");	


	msg = HIW"$N"HIW"斜身飞起，刀光如匹练般卷向$n"HIW"，$n"HIW"急忙拆招！$N"HIW"身行蓦然回飞，刀光一闪！\n"NOR;
	message_combatd(msg,me,target);
	me->add("force",-100);
	
	succ_msg = HIW "$n"HIW"不知不觉中，只觉$l一寒，已中无形刀波一击，虽不觉怎么疼痛，一口气却上不来了！\n"NOR;
	msg = HIW "$N"HIW"手中$w"HIW"连闪卷起的无数刀波却无形中如闪电般劈向$n"HIW"$l！\n"NOR;
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",5);
	base_damage = (me->query("family/xueshan_daobo")+1)*50;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,base_damage);
	me->set_temp("pfm_msg",0);
	me->add_temp("apply/attack",-5);
	if( damage<1 )
	{
		message_combatd(HIC"$n"HIC"身随风行，将这一招化的无影无踪。\n"NOR,me,target);
		me->add("force",-50);
		if( me->query("force")<0 )
			me->set("force",0);
		me->start_busy(1);
		return 1;
	}	
	if( me->query("force")<300 || me->query_skill("bingpo-blade",1)<180 )
	{
		me->start_busy(1);
		return 1;
	}	
	
	msg = HIW"\n刀光再闪！\n$N"HIW"手中$w"HIW"卷着无数雪花和寒气如闪电般劈向$n！\n"NOR;		
	succ_msg = HIW "$n"HIW"顿时大吃一惊，惊慌失措中已被雪花和寒气所伤！\n"NOR;
	me->add("force",-50);
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",10);
        if( base_damage>2500 ) base_damage = 2500;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,base_damage);
	me->set_temp("pfm_msg",0);
	me->add_temp("apply/attack",-10);
	if( damage<1 )
	{
		message_combatd(HIC"$n"HIC"身随风行，将这一招化的无影无踪。\n"NOR,me,target);
		me->add("force",-50);
		me->start_busy(2);
		return 1;
	}	
	if( me->query("force")<300 || me->query_skill("bingpo-blade",1)<250 )
	{
		me->start_busy(2);
		return 1;
	}
	
	msg = HIW"\n刀光又是一闪！\n$N"HIW"手中$w"HIW"所化无数刀波鬼神莫测般从$n"HIW"身后席卷而来！\n"NOR;
	succ_msg = HIR"$n"HIR"迫不及防，顿时被无穷刀波割得遍体鳞伤！\n"NOR;
	me->add("force",-50);
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",15);
	base_damage = (me->query("family/xueshan_daobo")+3)*80;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,base_damage);
	me->set_temp("pfm_msg",0);
	me->add_temp("apply/attack",-15);
	if( damage<1 )
	{
		message_combatd(HIC"$n"HIC"身随风行，将这一招化的无影无踪。\n"NOR,me,target);
		me->add("force",-50);
	}		
	me->start_busy(2);
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：雪风刀波  
              外功所属：冰魄寒刀  
              外功效果：用武器斩出刀波攻击敌人，当解出刀波的秘密后，固定伤害倍增
              		最多三击
              		当攻击一次时，自身busy 1 秒
              		当攻击多次时，自身busy 2 秒 	
              外功条件：
              		雪山(出师)弟子
              		人物等级15级
              		内力500点，消耗100点，每当增加攻击或不命中时，消耗增加50点
              		冰谷凝血功150级
                        基本轻功150级
                        冰魄寒刀150级
                        基本刀法150级
LONG; 
me->start_more(str); 
return 1; 
} 


