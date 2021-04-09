//snowtu
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void postfeijian(object,object,object,int);

string name()  
{
	return "「"HIC"飞鸟投林"NOR"」";  
}

int valid_perform(object me)
{
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不足。\n");
	if( me->query("family/family_name") != "大雪山" )
        	return notify_fail("只有大雪山弟子才配使用"+name()+"！\n"); 
	if (me->query_skill_mapped("force")!="ningxie-force")
        	return notify_fail(name()+"必须配合冰谷凝血功才能使用。\n");
	if(me->query_skill("bainiao-jian", 1) < 60) 
        	return notify_fail("你的百鸟剑法修为太差，难以施展"+name()+"！\n"); 
	if(me->query_skill("ningxie-force", 1) < 60) 
        	return notify_fail("你的冰谷凝血功修为太差，难以施展"+name()+"！\n"); 
	if(me->query_skill("sword", 1) < 60) 
        	return notify_fail("你的基本剑术根基太差，难以施展"+name()+"！\n"); 
	if(me->query_skill("throwing", 1) < 60) 
        	return notify_fail("你的暗器使用根基太差，难以施展"+name()+"！\n"); 
	if((int)me->query("force") < 150 ) 
        	return notify_fail("你内力不继，难以"+name()+"。\n");
	if( time()-(int)me->query_temp("feijian_busy") < 4 ) 
        	return notify_fail("你现在状态不佳，不能使用"+name()+"。\n"); 
	return 1;  
}

int perform(object me, object target)
{
	int attack,pp;
	mapping feijian= ([
        	"damage": 380,
	        "dodge" : -30,
        	"parry" : -30,
        	"force" : 100,
	        "damage_type" : "刺伤",
        	"action" :  "\n",
	        "post_action" : (: postfeijian :)
	]);
	string str,msg;
	object weapon = me->query_temp("weapon");
	if( !valid_perform(me) )
    		return 0;
	if( !target ) target = offensive_target(me); 
	if( !target 
	 || !target->is_character() 
	 || target->is_corpse() 
	 || target==me
	 || !me->is_fighting(target) )
		return notify_fail("你要对谁施展"+name()+"？\n"); 
    
	me->add("force", -80);
	me->set("actions",feijian);
	me->set_temp("feijian_busy", time());
	msg = HIW"$N"HIW"突然清啸一声，掌中$w"HIW"脱手而出，化做一道长虹，脱手飞去！$w"HIW"在空中幻出道道剑光，飞鸟投林般，向$n"HIW"的$l扑去！\n"NOR;
	attack = me->query_temp("apply/attack");
	me->add_temp("apply/attack",attack);
	me->set_temp("pfm_msg",1);	
	COMBAT_D->do_attack(me, target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	me->add_temp("apply/attack",-attack);	
	me->set_temp("pfm_msg",0);
	me->reset_action();
	return 1;
}

void postfeijian(object me,object victim,object weapon, int damage) 
{
	if( !me || !victim || !weapon || !me->is_fighting(victim) 
	 || weapon!=me->query_temp("weapon") )
		return;
	if( damage>0 )
    	{                
    		damage = weapon->query("weapon_prop/damage");
    		if( weapon->query("anqi/now")>0 )
    			damage+= 20*(int)weapon->query("anqi/now");
        	damage-= victim->query_combat_def();
        	if( victim->query("family/family_name")!="大雪山"
		&& (me->query_skill("throwing",1)>100 || wizardp(me)) )
			damage+= me->query_skill("ningxie-force",1)/5;
		damage+= me->query("family/xueshan_feijian");
		if( damage>0 )
        	{
        		message_combatd(HIW"结果$n"HIW"被"+weapon->name()+HIW"上的寒意给冻得打了个冷战，只觉气血难以凝聚。\n"NOR,me,victim);
			victim->receive_wound("kee",damage,me,TYPE_PERFORM);
			COMBAT_D->report_status(victim,1);
		}
	}
    	message_combatd(HIW""+weapon->query("name")+HIW"在空中打了个转，又飞回到$N"HIW"手中。\n"NOR,me);               
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：飞鸟投林
        外功所属：百鸟剑法
        外功效果：对敌进行攻击，并投掷武器以伤害对方
        	  可以通过五仙汤增加追加伤害
                  冷却时间 4 秒
        外功条件：
                  雪山弟子
        	  人物等级 6 级
                  内力150点，消耗80点
                  百鸟剑法 60 级
                  冰谷凝血功 60 级
                  基本剑术 60 级
                  暗器使用 60 级
STR;
        me->start_more(str);
        return 1;
}