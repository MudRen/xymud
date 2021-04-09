// Move.c 星移斗转
// Cracked by 凌惊雪 5-17-2003
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
	int i,k;
	string msg;
	object weapon;
	
	mapping *style= ({
        	([
        		"action": HIY"$N"HIY"使出一招"YELCYN"「天枢剔斗」"NOR HIY"，剑光闪烁不定，若有若无地刺向$n"HIY"$l！\n"NOR,
        		"dodge"	: -30,
        		"parry"	: -30,
        		"damage": 100,                           
        		"force"	: 20,
        		"damage_type":       "刺伤"          
        ]),
        ([                                 
        		"action": HIC"$N"HIC"脚下踏了个七星步，一招"YELCYN"「天璇射月」"NOR HIC"手中$w"HIC"势若飞瀑向$n"HIC"拦腰一斩！\n"NOR,
        		"dodge"	: -30,
        		"parry"	: -30,
        		"damage": 100,
        		"force"	: 20,
        		"damage_type":       "刺伤"
        ]),
        ([
        		"action": HIY"$N"HIY"轻轻一跃，使了个"YELCYN"「天机开展」"NOR HIY"，却在转身之际对准$n"HIY"$l斜斜挥出一剑！\n"NOR,
        		"dodge"	: -30,
        		"parry"	: -30,
        		"damage": 60,                           
        		"force"	: 10,
        		"damage_type":       "刺伤"
        ]),
        ([
        		"action": HIG"$N"HIG"神态悠闲，手中$w"HIG"凭空一指，一招"YELCYN"「天权银河」"NOR HIG"轻妙地划向$n"HIG"的$l！\n"NOR,
        		"dodge"	: -30,
        		"parry"	: -30,
        		"damage": 60,
        		"force"	: 10,
        		"damage_type":          "刺伤"
        ]),
        ([                      
        		"action": HIM"$N"HIM"手中$w"HIM"向外一分，使一招"YELCYN"「玉衡百里」"NOR HIM"反手对准$n"HIM"$l一剑刺去！\n"NOR,
        		"dodge"	: -30,
        		"parry"	: -30,
        		"damage": 100,
        		"force" : 20,
        		"damage_type":       "刺伤"
        ]),
        ([              
        		"action": HIR"$N"HIR"身形转个不停，突然一招"YELCYN"「开阳星流」"NOR HIR"使出，手中$w"HIR"划出一道银弧，径刺$n"HIR"$l！\n"NOR,
        		"dodge"	: -30,
        		"parry"	: -30,
        		"damage": 100,
        		"force"	: 20,
        		"damage_type":       "刺伤"
        ]),
        ([
			"action": HIW"$N"HIW"手中$w"HIW"平平一挥，平平无奇的点向$n"HIW"的$l，剑尖已经涌射出无限剑气，正是五庄剑法之极致"HIC"「万流归宗」"NOR HIW"！\n"NOR,
			"dodge"	: -50,
			"parry"	: -30,
			"damage": 150,
			"force"	: 50,
			"damage_type":          "刺伤"
        ]),
});
	mapping *style1= ({
        	([
        		"action": HIY"$N"HIY"使出一招"YELCYN"「天枢剔斗」"NOR HIY"，剑光闪烁不定，若有若无地刺向$n"HIY"$l！\n"NOR,
        		"damage": 100,                           
        		"damage_type":       "刺伤"          
        ]),
        ([                                 
        		"action": HIC"$N"HIC"脚下踏了个七星步，一招"YELCYN"「天璇射月」"NOR HIC"手中$w"HIC"势若飞瀑向$n"HIC"拦腰一斩！\n"NOR,
        		"damage": 100,
        		"damage_type":       "刺伤"
        ]),
        ([
        		"action": HIY"$N"HIY"轻轻一跃，使了个"YELCYN"「天机开展」"NOR HIY"，却在转身之际对准$n"HIY"$l斜斜挥出一剑！\n"NOR,
        		"damage": 60,                           
        		"damage_type":       "刺伤"
        ]),
        ([
        		"action": HIG"$N"HIG"神态悠闲，手中$w"HIG"凭空一指，一招"YELCYN"「天权银河」"NOR HIG"轻妙地划向$n"HIG"的$l！\n"NOR,
        		"damage": 60,
        		"damage_type":          "刺伤"
        ]),
        ([                      
        		"action": HIM"$N"HIM"手中$w"HIM"向外一分，使一招"YELCYN"「玉衡百里」"NOR HIM"反手对准$n"HIM"$l一剑刺去！\n"NOR,
        		"damage": 100,
        		"damage_type":       "刺伤"
        ]),
        ([              
        		"action": HIR"$N"HIR"身形转个不停，突然一招"YELCYN"「开阳星流」"NOR HIR"使出，手中$w"HIR"划出一道银弧，径刺$n"HIR"$l！\n"NOR,
        		"damage": 100,
        		"damage_type":       "刺伤"
        ]),
        ([
			"action": HIW"$N"HIW"手中$w"HIW"平平一挥，平平无奇的点向$n"HIW"的$l，剑尖已经涌射出无限剑气，正是五庄剑法之极致"HIC"「万流归宗」"NOR HIW"！\n"NOR,
			"damage": 150,
			"damage_type":          "刺伤"
        ]),
});
	if( me->query_level()<25 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("force") < 1000 )
        	return notify_fail("你的内力不足1000点！\n");        
	if( me->query_skill("sanqing-jian", 1) < 250)
        	return notify_fail("你的三清剑法等级还不够！\n");
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") )
		return notify_fail("你的剑呢？\n");	  
			
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招「星移斗转」?\n");
	
	msg = HIG "$N"HIG"脚踩连环七星步，手中"HIG+weapon->name()+HIG"电光火石间闪出无数道剑气！$N"HIG"脚走北斗各位，口中念念有词，$n"HIG"周围寒光闪闪，斗转星移，顿时晕头转向，不知所挫！\n"NOR;
	message_vision(msg, me, target);
	me->add("force",-500);
	if(me->query("family/family_name")!="五庄观") 
		me->add("force",-300);
        k = 4;
        k+= (me->query_skill("sanqing-jian", 1)-200)/100;
        if(me->query("family/family_name")!="五庄观") 
        	k = k-1;
        if( k>sizeof(style) )
        	k = sizeof(style);
        for(i=0;i<k;i++)
        {
        	if( !me || !target || !me->is_fighting(target) 
        	 || !living(me) || me->query("force")<100 )
			break;
		if(me->query("family/family_name")!="五庄观") 
			me->set("actions",style1[i]);        
		else	me->set("actions",style[i]);      
		me->add("force",-30);  
 		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
        }
	me->reset_action();  
	me->start_busy(2);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：星移斗转
        外功所属：三清剑法
        外功效果：对敌进行最多7次的连续攻击
                  自身busy 2 秒
                  
        外功条件：
        	  人物等级25级	
                  内力1000点，消耗500点，每击消耗内力30点
                  三清剑法 250 级
STR;
        me->start_more(str);
        return 1;
}