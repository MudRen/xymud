// 御剑飞行术
#include <ansi.h>

int perform(object me, object target)
{
	object weapon;
	int p;
	if( me->query_level()<40 )
    		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="蜀山派")
		return notify_fail("你不能使用这项技能！\n");
	if((int)me->query_skill("yujianshu",1) < 400
	 || me->query_skill_mapped("sword") != "yujianshu" )
        	return notify_fail("你的「御剑术」还不纯熟！\n");
	if((int)me->query("force") < 100 )
        	return notify_fail("你体内的内力不足。\n");
	if((int)me->query_skill("zuixian-wangyue",1) < 400)
        	return notify_fail("你的「醉仙望月步」还不纯熟！\n");
	if( me->query_temp("shushan_fly") )
		return notify_fail("你目前已经在施展「御剑飞行术」了。\n");

	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="sword" && weapon->query("use_apply_skill")!="sword" ) )
		return notify_fail("你的剑呢？\n");        	

	p = me->query_skill("sword")/50;
	me->add("force",-50);
	me->set_temp("shushan_fly",p);
	me->set_temp("shushan_fly_msg",weapon->name());
	message_vision(HIC"\n$N"HIC"默念御剑诀，手中"+weapon->name()+HIC"脱手飞出，迎风转了几转，平稳的贴在$N"HIC"脚下，顿时整个人凌空而立，好不潇洒。\n"NOR,me);
	tell_object(me,HIY"【系统】你处于「"HIG"御剑飞行术"HIY"」状态下，可以使用 "HIR"fly"HIY" 命令了。"NOR"\n");
	me->add_temp("apply/dodge",p);
	me->add_temp("apply/attack",p);
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：御剑飞行术
        外功所属：御剑术
        外功效果：御剑飞行
                  并增加人物的命中与有效身法
                  若飞行(fly)，则增益取消
        外功条件：
        	  蜀山弟子
        	  人物等级40级	
                  内力100点，消耗50点
                  御剑术400级并激发
                  醉仙望月步400级
LONG;
me->start_more(str);
return 1;
} 
