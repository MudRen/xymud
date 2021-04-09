#include <ansi.h>
#include <combat.h>
inherit SKILL;
mapping *action = ({
([      	"action" : "$N一招「盘蛇照路」，左掌叠于右掌之上，带着一股腥气劈向$n。\n",
                "dodge": -20,
                "parry": -20,
                "force": 35,
                "damage_type": "瘀伤",
                "weapon" :     "腥气",
                "parry_msg":    "只听见「锵」一声，被$n劈手一招"+HIR"「盘蛇照路」"NOR"格开。\n",
]),
([      	"action" : "$N一招「千山鸟飞绝」，面色凝重，双掌轻飘飘地抓向$n。\n",
        	"dodge": -20,
                "parry": -20,
                "force": 40,
                "damage_type": "抓伤",
                "parry_msg":    "只听见「锵」一声，被$n劈手一招"+HIW"「千山鸟飞绝」"NOR"格开。\n",
]),
([      	"action" : "$N一招「蛛丝长空」，双掌幻化一片腥风，将$n笼罩于内。\n",
        	"dodge": -25,
                "parry": -25,
                "force": 40,
                "damage_type": "砸伤",
                "parry_msg":    "只听见「锵」一声，被$n一招"+HIB"「蛛丝长空」"NOR"双掌幻化一片腥风将之格开。\n",
]),
([      	"action" : "$N一招「倒马桩」，向$n的$l连击数掌。\n",
        	"dodge": -25,
                "parry": -30,
                "force": 45,
                "damage_type": "撞伤",
                "parry_msg":    "只听见一声龙吟，$n一招"+HIY"「倒马桩」"NOR"劈手格开。\n",
]),
([      	"action" : "$N一招「万径人踪灭」，只见一片掌影攻向$n。\n",
        	"dodge": -30,
                "parry": -25,
                "force": 50,
                "damage_type": "内伤",
                "parry_msg":    "只听见「锵」一声，$n舞出一片掌影，一招"+HIC"「万径人踪灭」"NOR"将之格开。\n",
]),
([      	"action" : "$N双掌平挥，一招「冰蟾玉照」击向$n。\n",
       		"dodge": -30,
                "parry": -30,
                "force": 55,
                "damage_type": "瘀伤",
                "parry_msg":    "只听见「锵」一声，$n身形一长，一招"+HIG"「冰蟾玉照」"NOR"将之徒手格开。\n",
]),
([      	"action" : "$N一招「五彩遮月」，只见一片掌影攻向$n。\n",
        	"dodge": -30,
                "parry": -30,
                "force": 55,
                "damage_type": "瘀伤",
                "parry_msg":    "结果$n身形一长，一片掌影迎向$N，却是一招"+HIG"「五彩遮月」"NOR"。\n",
]),
([      	"action" : "$N施出「百足盘旋」，右手横扫$n的$l，左手攻向$n的胸口。\n",
        	"dodge": -30,
                "parry": -30,
                "force": 55,
                "damage_type": "瘀伤",
                "parry_msg":    "结果$n施出「百足盘旋」，只听见「锵」一声将之徒手格开。\n",
]),
([      	"action" : "$N左掌虚晃，右掌一记「冰蟾西下」击向$n的头部。\n",
        	"dodge": -30,
                "parry": -30,
                "force": 55,
                "damage_type": "瘀伤",
                "parry_msg":    "结果$n施出「冰蟾西下」，只听见「锵」一声将之徒手逼回。\n",
]),
([      	"action" : "$N施出「万毒噬体」，双掌同时击向$n的$l。\n",
        	"dodge": -30,
                "parry": -30,
                "force": 60,
                "damage_type": "瘀伤",
                "parry_msg":    "结果$n施出「万毒噬体」，只听见「锵」一声双掌已将之格开。\n",
])
});
int valid_enable(string usage)
{
        return usage == "parry" || usage == "unarmed";
}
int valid_learn(object me)
{
	int i;
	string *skills;
	if( me->query("public_skill/wudu-shenzhang_abandon") )
		return notify_fail("你以前曾经学过五毒神掌，现在再也不能学习了。\n");
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("练五毒神掌必须空手。\n");
        if( (int)me->query_skill("force") < 150)
		return notify_fail("你的内功火候不够，无法练五毒神掌。\n");
        if( (int)me->query_maxforce()<1200)
                return notify_fail("你的内力太弱，无法练五毒神掌。\n");
        if( (int)me->query_skill("unarmed", 1) < 300)
                return notify_fail("你的扑击格斗之术火候不够，无法练五毒神掌。\n");
	skills = ({
		"shenghuo-spear","lieyang-jian","lihuo-dodge","wuhu-blade",
	}); 
	for(i=0;i<sizeof(skills);i++)
	{
		if( me->query_skill(skills[i],2)>=1 )
			return notify_fail("你学过「"+to_chinese(skills[i])+"」，就无法再学「五毒神掌」了。\n");
		if( me->query("public_skill/"+skills[i]+"_abandon") )
			return notify_fail("你以前曾经学过「"+to_chinese(skills[i])+"」，再也不能学习「五毒神掌」了。\n");	
	}        	
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	string force;
	if( (int)me->query("kee") < 90)
        	return notify_fail("你的体力太低了。\n");
	if( (int)me->query("force") < 80)
                return notify_fail("你的内力不够练五毒神掌。\n");
	if( me->query_skill("wudu-shenzhang",2)<150 )
		return notify_fail("你的「五毒神掌」还不够纯熟，光靠练是没用的。\n");
	if( !stringp(force=me->query_skill_mapped("force")) )
		return notify_fail("你没有激发内功，恐怕练习五毒神掌有些危险。\n");
	if( me->query_skill(force,2)<me->query_skill("wudu-shenzhang",2) )
		return notify_fail("你的「"+to_chinese(force)+"」还不够纯熟，恐怕练习五毒神掌有些危险。\n");
        me->receive_damage("kee", 60);
        me->add("force", -60);
        return 1;
}
string perform_action_file(string action)
{
        return CLASS_D("public") + "/wudu-shenzhang/" + action;
}

varargs mixed hit_ob(object me, object victim, int damage_bonus,int factor)
{
	string *n1,*n2,*n3;
	if( !me || !victim || !me->is_killing(victim->query("id")) 
	 || damage_bonus < 50 ) 
		return 0;
	if( random(me->query("bellicosity"))>victim->query("bellicosity")/10 )
    	{
    		victim->receive_wound("kee", damage_bonus/5+1,me,TYPE_PERFORM );
    		if( random(4)==1 || userp(victim) )
    			victim->apply_condition("wudu",victim->query_condition("wudu")+1+random(2));		
    		
    		n1 = ({
    			MAG"$n"MAG"脸色一黑，",
    			MAG"$n"MAG"面上黑气一闪，",
    			MAG"$N"MAG"双掌黑气一闪，",
    			MAG"$N"MAG"双掌传来一股腥气，",
    		});
    		n2 = ({
    			"$n"MAG"只觉一阵头昏，",
    			"$n"MAG"眼前一黑，",
    			"$n"MAG"只觉$l一麻，",	
    		});
    		n3 = ({
    			"立刻站立不稳，摇摇晃晃。\n"NOR,
    			"「嘿」地一声退了两步。\n"NOR,
    			"$l有如受到一记重击，连退了五六步！\n"NOR,
    			"眼前一黑，身子立刻摇摇欲坠！\n"NOR,
    			"立刻吐出一口黑血，身子象断了线的风筝向後飞去！\n"NOR,
    			"不由大叫：毒毒毒！连忙慌忙后退。\n"NOR,
    		});
    		
    		return n1[random(sizeof(n1))]+n2[random(sizeof(n2))]+n3[random(sizeof(n3))];
	}
}

string query_parry_msg(object weapon)
{
    return action[random(sizeof(action))]["parry_msg"];
}

string query_type(){ return "public";}