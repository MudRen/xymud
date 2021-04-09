//剑神
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	object weapon;
	int skill;
	if( me->query_level()<60 )
    		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="蜀山派")
		return notify_fail("你不能使用这项技能！\n");
	if((int)me->query_skill("yujianshu",1) < 600
	 || me->query_skill_mapped("sword") != "yujianshu" )
        	return notify_fail("你的「御剑术」还不纯熟！\n");
	if((int)me->query("force") < 800 )
        	return notify_fail("你体内的内力不足。\n");
        if( me->query_temp("shushan_jianshen")>0 )
        	return notify_fail("你已经施展了「剑神」了。\n");
	if( time()<me->query_temp("shushan_jianshen_end")+6 )
		return notify_fail("你不能频繁施展「剑神」。\n");

	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="sword" && weapon->query("use_apply_skill")!="sword" ) )
		return notify_fail("你的剑呢？\n");         	
	skill = me->query_skill("sword")/60;
	message_vision(HIW"\n$N"HIW+weapon->name()+HIW"上冲出一道霞光，在半空凝成一尊白发老者虚像。老者眸光冷如剑锋，冷冷俯瞰众生！\n"NOR,me);
	message_combatd(WHT"只见那老者默念剑诀，手中长剑射出一道霞光，在半空化作方圆半亩的云霞，不时闪烁着明锐光华！\n"NOR,me);
	me->add("force",-300);
	me->set_temp("shushan_jianshen",skill);
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：剑神
        外功所属：御剑术
        外功效果：召唤一个剑神虚像，在战斗中能对敌
        	  施展「万剑诀」
        外功条件：
        	  人物等级60级	
                  内力800点，消耗300点
                  御剑术600级并激发
LONG;
me->start_more(str);
return 1;
} 
