// Hanyulingfeng.c 寒玉灵风
// Cracked by 凌惊雪 4-1-2003
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int exert(object me, object target)
{
        int damage,attack;
        string msg,succ_msg;

	if( me->query_level()<20 )
        	return notify_fail("你的人物等级不够。\n");
	if( userp(me) && !wizardp(me) )
	{
		if( !me->is_knowing("bhg_feng") )                
                	return notify_fail("你还没有领悟「寒玉灵风」这一招的用法！\n");
	}                	
        if( me->query("family/family_name")!="百花谷" )
                return notify_fail("非百花谷弟子不能用「寒玉灵风」！\n");
	if( me->query_skill("brightjade-force",1)<200 )
		return notify_fail("你的内功太差了。\n");                
        if( (int)me->query("force") < 500 )
                return notify_fail("你的内力不够。\n");
	if( time()<me->query_temp("bhg_feng")+6 )
		return notify_fail("你现在后力难以为继。\n");
		                
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) ) 
                return notify_fail("你要对谁施展这一招「寒玉灵风」？\n");
	if( target->is_busy() )
		return notify_fail("对方状态不佳，放胆攻击吧。\n");
	
	me->add("force", -150);
	me->set_temp("bhg_feng",time());
	
	msg = HIW"\n$N"HIW"运起明玉神功，吸天地之灵气为己所用，顿时神清气明，通体透明如玉！一缕无形的气劲向$n"HIW"袭出！\n"NOR;
	succ_msg = HIW "$n"HIW"只觉微风拂面，被无形气劲击中，面色苍白，眼前一阵黑！\n"NOR;
	attack = me->query_skill("force")/50;
	me->add_temp("apply/attack",attack);
	me->set_temp("pfm_msg",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->is_knowing("bhg_feng")*50);
	me->set_temp("pfm_msg",0);
	me->add_temp("apply/attack",-attack);
        
        if( damage<1 )
        {
        	message_combatd(HIW "$n"HIW"只觉微风拂面，被无形气劲击中，面色一变，但很快就恢复了过来。\n"NOR, me,target);
        	me->add_temp("bhg_feng",3);
        	return 1;
        }
        target->start_busy(3);
        return 1;
}

int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        内功名称：寒玉灵风
        内功所属：明玉神功
        内功效果：将天地灵气化作无形气劲对敌人进行气血伤害
                  并有一定的几率使对手busy 3 秒
                  冷却时间6秒，不中则增加3秒
                  需领悟，领悟越高伤害越高
        内功条件：百花谷传人
        	  人物等级20级
        	  内力500点,消耗150点
                  明玉神功200级
                  
LONG;
me->start_more(str);
return 1;
}       

