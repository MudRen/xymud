#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	mapping act;
        int damage;
	string msg,*l1,*l2,limb,succ_msg;
	
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="火云洞")
        	return notify_fail("「摇头摆尾」只有火云洞门人才可以用！\n");		
        if((int)me->query("force") < 200 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query_skill("moshenbu", 1) < 100)
                return notify_fail("你的魔神步法级别还不够，使用这一招会有困难！\n");
        if((int)me->query_skill("dali-bang", 1) < 100)
                return notify_fail("你的大力棒级别还不够，使用这一招会有困难！\n");
                
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要对谁施展这一招？\n");

	l1 = ({ "头部", "颈部", "胸口", "后心", "左肩", "右肩", });
	l2 = ({ "小腹", "左腿", "右腿","左脚", "右脚" });

	me->add("force",-50);

	msg = HIB"$N"HIB"吞吐妖族精血，足下暗含周天星斗奥妙，顿时背后隐露十万大山幻象！\n"NOR;
	msg+= HIB"$N"HIB"脚下猝停，背后幻象中顿时冲出一头妖气滔天的巨牛，巨大的牛角摧枯拉朽般直冲$n"HIB"上路$l！\n"NOR;
	succ_msg = HIR"$n"HIR"来不及闪避，被撞了正着！“轰隆”一声，地动山摇一般,$n"HIR"顿时倒飞出数丈远，一路上鲜血淋漓！\n"NOR;
	
	act = ([  "action": "\n",
     		"dodge" : -10,
     		"parry" : -80,
     		"force" : 250,
     		"damage_type" :  "撞伤"
   	]);
   	limb = l1[random(sizeof(l1))];
   	me->set("actions",act);
   	me->set_temp("pfm_msg",1);
   	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,limb);
   	me->set_temp("pfm_msg",0);
   	me->reset_action();
	
	if( damage<1 )
		message_combatd(YEL"$n"YEL"临危不惧，纵身跃起，将巨牛远远抛在身后。\n"NOR,me,target);
		
	if( me->query_skill("moshenbu",1)<300 
	 || me->query_skill("dali-bang",1)<300 	
	 || me->query("force")<100 
	 || !living(me) || !target || !me->is_fighting(target) )
	{
		me->start_busy(2);
		return 1;
	}
	
	me->add("force",-50);
	me->add_temp("apply/attack",15);
	msg = HIR"\n巨牛冲过之后，巨大的身子一摇，牛尾雷霆万钧般狠狠抽向$n"HIR"下半路的$l！\n"NOR;
	succ_msg = RED"结果「啪」地一声爆响，只抽得$n"RED"皮开肉绽，血花飞溅！\n"NOR;
	act = ([  "action": "\n",
     		"dodge" : -5,
     		"parry" : -60,
     		"force" : 350,
     		"damage_type" :  "抽伤"
   	]);
   	limb = l2[random(sizeof(l2))];
   	me->set("actions",act);
   	me->set_temp("pfm_msg",1);
   	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,limb);
   	me->set_temp("pfm_msg",0);
   	me->reset_action();
	if( damage<1 )
		message_combatd(YEL"$n"YEL"临危不惧，再度纵身跃起，闪不过了这一击。\n"NOR,me,target);	 
	me->start_busy(2);
	me->add_temp("apply/attack",-15);
	return 1;	 
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：摇头摆尾 
        外功所属：魔神步法 
        外功效果：对敌上盘部位进行伤害气血后限的物理攻击
                  当技能等级300后，继续对敌下盘部位进行
                  伤害气血后限的物理攻击
                  自身busy 2 秒
        外功条件：
        	  火云洞弟子
        	  人物等级10级	
        	  内力200点，消耗50点，「摆尾」增加消耗50点
                  魔神步法 100 级
                  大力棒 100 级
STR;
        me->start_more(str);
        return 1;
}