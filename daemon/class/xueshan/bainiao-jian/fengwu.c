// fengwu.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
	object weapon;
	string msg,succ_msg;
	int skill,damage,p,pp;
        
        if( me->query_level()<30 )
        	return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="大雪山") 
		return notify_fail("雪山绝技你怎么会！\n");
	if((int)me->query("force") < 1000 )
        	return notify_fail("你体内的内力不足！\n");
	if((int)me->query("sen") < 300 )
        	return notify_fail("你的精神不足！\n");
        if( me->query_skill("throwing",1)<300 )
        	return notify_fail("你的暗器使用等级不够。\n");
        if( me->query_skill("sword",1)<300 )
        	return notify_fail("你的剑法底子太差。\n");
        if( me->query_skill("bainiao-jian",1)<300 )
        	return notify_fail("你的百鸟剑法等级不够。\n");
	if((int)me->query_skill("xiaoyaoyou",1) < 300) 
        	return notify_fail("你的『逍遥游』等级不够！\n");        	
	if((int)me->query_skill("ningxie-force",1) < 300) 
        	return notify_fail("你的『冰谷凝血功』等级不够！\n");        	
        weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") 
	 || me->query_skill_mapped("sword")!="bainiao-jian" ) 
		return notify_fail("你没有剑，如何能发出『凤舞九天』？\n");	  
        
	if( !target ) target = offensive_target(me);
	if( !target
  	  ||!target->is_character()
  	  || target->is_corpse()
  	  || target==me 
  	  || !me->is_fighting(target) )
		return notify_fail("你要对谁施展这一招『凤舞九天』？\n");

	p = me->query_skill("dodge")/10;
	pp = me->query_skill("sword")/3;

	succ_msg = HIR"\n                         ▁▃\n"
"                   ▂▅▇▄▁▃\n"
"                      "HBRED HIR"▆▄ "NOR HIR"◣  ▄▆▆▅▅▄▃▂▁\n"NOR
"                           "HIR"◥◣ ◥▉"HBRED HIR"≡ ==—￣ ▁ "NOR HIR"▆▄▂\n"NOR
RED"                 ▁▂       ◥"HBRED" "NOR RED"◣"HBRED HIR"▉═￣     ▁▄\n"NOR
HIR"              ◢"HBRED"◤◥"NOR HIR"█▆▅▆▇"HBRED"▆  ＼   ▇▄\n"NOR
"              "HBRED HIR"▍     ◥◥◥ ◥◥▊  "NOR HIR"◣\n"NOR
"              "HBRED HIR"▎   ﹨  ◥◥ ＼＼ ＼    "NOR HIR"▃\n"NOR
"              "HBRED HIR"▏｜  ﹨   ＼ ＼ ▄"NOR" "BLK HBRED"▆▃     "NOR RED"▃▂▃▁\n"NOR
"              "HBRED HIR"▏∥         ▄"NOR"              "RED"◥▄  ▂"BLK HBRED"▇▅▄\n"NOR
"              "HBRED HIR"   │     "NOR HIR"◥                     "BLK HBRED"▅▃▅▃  ▅"NOR RED"▃\n"NOR
"              "HBRED HIR"   ║   "NOR HIR"▊▏                         "HBRED"▄"NOR HIR"◣ "HBRED"▅"NOR HIR"▃ ◥▃\n"NOR
"               "HBRED HIR"       "NOR HIR"▎                              ◥    ◥▃ ◥▃\n"NOR
"               "HBRED HIR"     "NOR HIR"▉▏                             __ ▍     ▌   ◥\n"NOR
"               "HBRED HIR"▎  "NOR HIR"▊▎                            ▕凤▏▍     ◥\n"NOR
"                "HBRED HIR"     "NOR HIR"∥                            ▕凰▏▎       ▍\n"NOR
"                  "HBRED HIR" ∣"NOR HIR"                                ￣  ▍        ▍\n"NOR
HIR"                   ◥                                   ▍          ▎\n"NOR
HIR"                                                  ▁▂◤             ▏\n"NOR
HIR"                                                                    ▏\n\n"NOR;
        if( !me->query("env/brief_message") )  message_combatd(succ_msg,me);
	msg = HIW "\n$N"HIW"使出百鸟剑法的奥秘 [凤舞九天]，身子如陀螺般急旋十多个圈，化为一只"HIG"七"HIR"彩"HIC"凤"HIY"凰"HIW"冲天而起！\n"NOR;
	succ_msg = HIR"火红的凤凰在空中飞舞，顷刻间烈焰漫天，飞沙走石，日月无光。"NOR;
	me->add("force",-300);
	me->add_temp("apply/attack",p);
	me->add_temp("apply/combat_damage",pp);
	me->set_temp("pfm_msg",1);
	me->set_temp("fengwu",1);
	me->reset_action();
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,pp);
	me->add_temp("apply/attack",-p);
	me->add_temp("apply/combat_damage",-pp);
	me->set_temp("pfm_msg",0);
	me->delete_temp("fengwu");
	me->reset_action();
	
	if( damage<1 )
	{
		message_combatd(HIY"可是$n"HIY"发现情况不对，施展本门的轻功避了开，$N"HIY"的攻击扑了个空。\n"NOR, me, target);
		if( me->query("force")>200 )
			me->add("force",-200);
		else	me->set("force",0);	
		me->start_busy(2);
	}	
	else	me->start_busy(1);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：凤舞九天
        外功所属：百鸟剑法
        外功效果：对敌进行带高固定伤害的攻击
                  不中则自身busy 2 秒，内力消耗增加200点
                  否则自身busy 1 秒
        外功条件：
                  雪山弟子
        	  人物等级 30 级
                  内力1000点，消耗300点
                  百鸟剑法 300 级
                  冰谷凝血功 300 级
                  基本剑术 300 级
                  逍遥游 300 级
                  暗器使用 300 级
STR;
        me->start_more(str);
        return 1;
}

