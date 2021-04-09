// 万剑诀
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void wanjian(object me,object target,object weapon)
{
	int k,damage;
	string msg,succ_msg;
	if( !me || !living(me) )
		return;
	if( !target || !me->is_fighting(target) )
	{
		message_combatd("$N见已无敌手，收起了「万剑诀」。\n",me);
		return;
	}		
	if( !weapon || weapon!=me->query_temp("weapon") )
	{
		message_combatd("$N收起了「万剑诀」。\n",me);
		return;
	}
	msg = HIC"一刹那间千万剑光从半空云霞中破空而来，劈头盖面的罩向$n"HIC"！\n"NOR;
	succ_msg = HIR"$n"HIR"一个不慎，$l已插了一把光彩逼人的化形小剑！\n"NOR;
	me->set_temp("pfm_msg",1);
	for(k=0;k<3;k++)
	{
		damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
		if( damage<1 )
			message_combatd(HIY"\n$n"HIY"左跳右闪，好不容易避开了一轮剑雨。\n"NOR,me,target);
	}
	me->delete_temp("pfm_msg");	
}

int perform(object me, object target)
{
	object weapon;
	
	if( me->query_level()<40 )
    		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="蜀山派")
		return notify_fail("你不能使用这项技能！\n");
	if((int)me->query_skill("yujianshu",1) < 400
	 || me->query_skill_mapped("sword") != "yujianshu" )
        	return notify_fail("你的「御剑术」还不纯熟！\n");
	if((int)me->query("force") < 800 )
        	return notify_fail("你体内的内力不足。\n");
        if( time()<me->query_temp("shushan_wanjian")+5 )
        	return notify_fail("绝招用多就不灵了。\n");	
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="sword" && weapon->query("use_apply_skill")!="sword" ) )
		return notify_fail("你的剑呢？\n");        	
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招「万剑诀」？\n");
	me->add("force",-300);
	me->set_temp("shushan_wanjian",time());
	message_vision(HIC"\n$N"HIC"默念剑诀，手中"+weapon->name()+HIC"射出一道霞光，在半空化作方圆半亩的云霞，不时闪烁着明锐光华！\n"NOR,me,target);
	call_out("wanjian",0,me,target,weapon);
	if( (int)me->query_skill("yujianshu",1) >=600 )
		call_out("wanjian",1,me,target,weapon);
	if( (int)me->query_skill("yujianshu",1) >=900 )
		call_out("wanjian",2,me,target,weapon);
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：万剑诀
        外功所属：御剑术
        外功效果：以气驭剑，剑化万剑，对敌进行多次打击
		  冷却时间5秒
        外功条件：
        	  人物等级40级	
                  内力800点，消耗300点
                  御剑术400级并激发
LONG;
me->start_more(str);
return 1;
} 
