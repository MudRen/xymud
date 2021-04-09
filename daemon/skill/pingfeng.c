// Pingfeng.c 屏风四扇门
// Cracked by 凌惊雪 1-17-2003
inherit SKILL;
#include <ansi.h>
#include <combat.h>

int valid_enable(string usage) 
{ 
	return 	usage=="unarmed" ||usage=="parry" ||usage=="force";
}

mapping *action = ({
        ([      
        	"action": "$N使出一招「屏风一扇门」，左手聚出一团真气击向$n的$l。\n",
                "dodge":                -5,
                "parry":                -5,
                "force":                40,
                "weapon":               "左手",
                "damage_type":  "瘀伤",
                "parry_msg":    "只听见「锵」一声，被$n用全身化作的真气所阻。\n",
        ]),
        ([      "action": "$N使出一招「屏风两扇门」，右手聚出一团真气击向$n的$l。\n",
                "dodge":                -5,
                "parry":                -5,
                "force":                45,
                "weapon":               "右手",
                "damage_type":  "瘀伤",
                "parry_msg":    "$n长袖一甩，一股大力将$N送出丈外。\n",
        ]),
	([ 	"action": "$N使出一招「屏风三扇门」，双手聚出一团真气击向$n的$l。\n",
                "dodge":                -15,
                "parry":                -15,
                "force":                50,
                "weapon":               "双手",
                "damage_type":  "瘀伤",
                "parry_msg":    "$n衣衫澎湃，内力汩汩，$N根本不可近身。\n",
        ]),
	([	"action":"$N使出一招「屏风四扇门」，全身腾空而起，全身化作一团真气击向$n的$l。\n",
                "dodge":                -15,
                "parry":                -15,
                "weapon":               "全身",
                "force":                45,
                "damage_type":  "瘀伤",
                "parry_msg":    "$n施展出「屏风四扇门」，轻描淡写的化解了$N的攻势。\n",
        ]),
	([	"action": "$N使出「屏风大法」，全身腾空而起，全身化作一团真气击向$n的$l。\n",
                "dodge":                -20,
                "parry":                -20,
                "weapon":               "全身",
                "force":                50,
                "damage_type":  "瘀伤",
                "parry_msg":    "$n施展出「屏风大法」，轻描淡写的化解了$N的攻势。\n",
        ]),
	([	"action": "$N使出「屏风大法」，全身腾空而起，全身化作一团真气击向$n的$l。\n",
                "dodge":                -25,
                "parry":                -25,
                "weapon":               "全身",
                "force":                55,
                "damage_type":  "瘀伤",
                "parry_msg":    "$n施展出「屏风大法」，轻描淡写的化解了$N的攻势。\n",
        ]),
	([	"action": "$N使出「屏风大法」，全身腾空而起，全身化作一团真气击向$n的$l。\n",
                "dodge":                -30,
                "parry":                -30,
                "weapon":               "全身",
                "force":                55,
                "damage_type":  "瘀伤",
                "parry_msg":    "$n施展出「屏风大法」，轻描淡写的化解了$N的攻势。\n",
        ]),
});

mapping query_action(object me, object weapon)
{
	int i = (int)me->query_skill("pingfeng", 1);
	i = i/100;
	if(i>7) i=7;
        return action[random(i)];
}

string query_parry_msg(object me,object target)
{
	return query_action(me,me->query_temp("weapon"))["parry_msg"];
}

int valid_learn(object me)
{
	int i = (int)me->query_skill("pingfeng",2);
	int j = (int)me->query_skill("force",2);
	int k = (int)me->query("mark/luoyang_pingfeng");

	if( me->query("public_skill/pingfeng_abandon") )
		return notify_fail("你曾经放弃学习过屏风四扇门，现在再也不能学习了。\n");
	
	if( me->query_skill("xuehejue",2)>=1 )
		return notify_fail("你既然已经学了血河诀，就不能三心二意。\n");
	if( me->query("killerside") != "officer")
		return notify_fail("你不是神侯府的门下，难以领会屏风四扇门的精髓。\n");
	if( j<300 )
		return notify_fail("你的内功修为太低，强学这门功夫没用的，小心走火入魔。\n");
	if( i>=k*10 )
		return notify_fail("你的实战能力不够，需要更多的「"HIY"屏风四扇门"NOR"」学习点数。\n");
	return 1;
}

varargs int practice_skill(object me,int flag)
{
	if( (int)me->query("kee") < 80 || (int)me->query("force") < 50 )
		return notify_fail("你的内力或气不够，没有办法练习屏风四扇门。\n");
 	me->receive_damage("kee", 30);
 	me->add("force", -50);
	if( flag )  
		write("你按着所学练了一遍屏风四扇门。\n");
 	return 1;
}

string exert_function_file(string func)
{
        return CLASS_D("public") + "/pingfeng/force/" + func;
}

string perform_action_file(string action)
{
	return CLASS_D("public") + "/pingfeng/unarmed/" + action;
}

varargs mixed hit_ob(object me, object victim, int damage_bonus,int factor)
{
        if( !me || !victim || !me->is_killing(victim->query("id")) 
         || random(damage_bonus)< 50 ) 
		return 0;
	if( me->query_skill("xuehejue",2)>=1 )
		return 0;
	if( me->query_skill("pingfeng",2)<200 )
		return 0;
			
	if( random(damage_bonus/2) > victim->query_str()/10) 
	{
		if(me->query_skill_mapped("unarmed")=="pingfeng")
		{
        		damage_bonus = victim->receive_wound("kee", damage_bonus /3,me,TYPE_PERFORM );
                	switch(random(4)) 
                	{
                        	case 0: return HIY"只听到「喀啦」一声轻响，竟似是$n"HIY"$l骨碎的声音，被真气正中！\n"NOR;
                        	case 1: return HIY"$N"HIY"劲力一吐，$n"HIY"的$l发出「喀」地一声断裂爆响，被掌风拂中！\n"NOR;
                        	case 2: return HIY"$N"HIY"劲力一吐，$n"HIY"的$l发出「喀」地一声断裂爆响，被劲气所伤！\n"NOR;
                        	default: return HIY"只听见$n"HIY"的$l「喀」地一声 ，被掌力震伤\n"NOR;
                        }
		}        		
        	else if(me->query_skill_mapped("unarmed")=="force")
        	{
        		damage_bonus = victim->receive_wound("kee", damage_bonus /5,me,TYPE_PERFORM );	
			switch(random(5)) 
                	{
                        	case 0: return HIW"$N"HIW"劲力一吐，$n"HIW"的$l发出「喀」地一声断裂爆响，被掌风拂中！\n"NOR;
                        	case 1: return HIW"$N"HIW"劲力一吐，$n"HIW"的$l发出「喀」地一声断裂爆响，被掌风拂中！\n"NOR;
                        	case 2: return HIW"$N"HIW"劲力一吐，$n"HIW"的$l发出「喀」地一声断裂爆响，被劲气撞个正着！\n"NOR;
                        	case 3: return HIW"$N"HIW"劲力一吐，$n"HIW"的$l发出「喀」地一声断裂爆响，被真气撞个正着！\n"NOR;
                        	default: return HIW"$N"HIW"听到「喀啦」一声轻响，竟似是$n"HIW"$l骨碎的声音，被真气震伤！\n"NOR;
                        }	
                }
        }
        return 0;
}

void skill_improved(object me)
{
	me->delete("mark/luoyang_pingfeng");
}

string query_type(){ return "public";}