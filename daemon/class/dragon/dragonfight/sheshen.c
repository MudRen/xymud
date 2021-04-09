// sheshen.c            舍身技
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        int damage,p,t;
        object weapon;

	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
	weapon = me->query_temp("weapon");
	if( weapon )
	{
		if( weapon->query("skill_type")!="unarmed"
		 && weapon->query("use_apply_skill")!="unarmed" )
		 	return notify_fail("『舍身技』是拳脚上的功夫。\n");
	}
	if( me->query_skill_mapped("unarmed")!="dragonfight" )
		return notify_fail("『舍身技』需要龙形搏击的支持。\n");
	if( me->query_skill("dragonfight",1)<100 
	 || me->query_skill("unarmed",1)<100 )
	 	return notify_fail("你的掌上功夫太差了！\n");
	if( me->query_skill_mapped("force")!="dragonforce" 
	 || me->query_skill("force",1)<100
	 || me->query_skill("dragonforce",1)<100 )
	 	return notify_fail("你的内功太差了！\n");
	if( me->query("force")<300 )
		return notify_fail("你内力不足。\n");
	if( me->query("kee")<200 )
		return notify_fail("你现在状态不佳。\n");
	if( time()<me->query_temp("sea_sheshen")+5 )
		return notify_fail("这招不能频繁使用。\n");
			
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招『舍身技』？\n");

        me->set_temp("sea_sheshen",time());
        me->add("force", -150);
        me->receive_damage("kee",100,me);
        
        msg = CYN "$N"CYN"右掌挥出，斩向$n"CYN"的左肩，";
        succ_msg = CYN"$n"CYN"挥手想挡开，不料却被$N"CYN"一把抓住，顺势上步，使出了"HIC"『舍身技』"NOR CYN"！\n"NOR;
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
        me->set_temp("pfm_msg",0);
        
        msg = CYN "$N"CYN"左脚铲向$n"CYN"右腿膝盖，"NOR;
        succ_msg = CYN"结果正铲在$n的小腿上。\n" NOR;
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,({"左腿","右腿"})[random(2)],me->query_skill("unarmed"));
        me->set_temp("pfm_msg",0);

        msg = CYN"紧跟着$N"CYN"收左脚，提左膝撞向$n"CYN"的软肋，同时右手曲肘撞向$p的面门，"NOR;
        succ_msg = CYN"结果正中$n"CYN"。\n" NOR;
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"头部",me->query_skill("unarmed"));
        me->set_temp("pfm_msg",0);

        msg = CYN"$N"CYN"顺势用右手抓住$n"CYN"右臂，半转身将$n"CYN"摔了出去，"NOR;
        succ_msg = CYN"结果$n"CYN"一个踉跄，虽没摔倒，却也狼狈不堪。\n"NOR;
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("unarmed"));
        me->set_temp("pfm_msg",0);
        
        return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：舍身技
        外功所属：龙形搏击
        外功效果：以龙形搏击对敌进行连续带固定伤害的攻击
                  使用后冷却5秒
        外功条件：
        	  龙宫弟子
        	  人物等级10级
                  内力300点，消耗150点
                  气血200点，消耗100点
                  龙形搏击100级
                  龙神心法100级
                  扑击格斗100级
                  内功心法100级
LONG;
me->start_more(str);
return 1;
}