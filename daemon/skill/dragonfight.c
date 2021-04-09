//【龙形搏击】dragonfight.c
inherit SKILL;
#include <ansi.h>
#include <combat.h>

mapping *action = ({
        ([      "action": "$N纵身跃起，一招"+HIR"「飞龙在天」"NOR"，双掌以排山倒海之势击向$n的$l。\n",
                "dodge": -20,
                "parry": -20,
                "force": 90,
                "damage_type": "瘀伤",
                "weapon" :     "双掌",
                "parry_msg":    "只听见「锵」一声，被$n劈手一招"+HIR"「飞龙在天」"NOR"格开。\n",
        ]),
        ([      "action": "$N似退反进，突然欺身向前，五指如钩，一招"+HIW"「潜龙勿用」"NOR"，对准$n的$l一把抓了过去。\n",
                "dodge": -20,
                "parry": -20,
                "force": 55,
                "damage_type": "抓伤",
                "weapon":      "右手五指",
                "parry_msg":    "只听见「锵」一声，被$n劈手一招"+HIW"「潜龙勿用」"NOR"格开。\n",
        ]),
        ([      "action": "只见$N一旋身，双腿如铁棍一般扫向$n。这一招"+HIB"「神龙摆尾」"NOR"当真是防不胜防。\n",
                "dodge": -25,
                "parry": -25,
                "force": 95,
                "damage_type": "砸伤",
                "weapon":      "双腿",
                "parry_msg":    "只听见「锵」一声，被$n一招"+HIB"「神龙摆尾」"NOR"双腿如铁棍一般将之格开。\n",
        ]),
        ([      "action": "$N忽发龙吟，使出一招"+HIY"「龙战于野」"NOR"，啸声中和身而上，向$n直撞而来。\n",
                "dodge": -25,
                "parry": -30,
                "force": 80,
                "damage_type": "撞伤",
                "weapon":      "全身",
                "parry_msg":    "只听见一声龙吟，$n一招"+HIY"「龙战于野」"NOR"，啸声中劈手格开。\n",
        ]),
            ([  "action": "只见$N一个筋斗翻在半空，一招"+HIC"「龙腾四海」"NOR"将发未发，但是全身劲气疾卷$n。\n",
                "dodge": -30,
                "parry": -25,
                "force": 90,
                "damage_type": "内伤",
                "weapon":      "劲气",
                "parry_msg":    "只听见「锵」一声，$n一个筋斗翻在半空，一招"+HIC"「龙腾四海」"NOR"，全身劲气将之格开。\n",
        ]),
            ([  "action": "$N身形一长，朝$n劈面就是一拳。这招"+HIG"「苍龙出海」"NOR"势若奔雷，锐利无比。\n",
                "dodge": -30,
                "parry": -30,
                "force": 100,
                "damage_type": "瘀伤",
                "weapon":      "拳头",
                "parry_msg":    "只听见「锵」一声，$n身形一长，一招"+HIG"「苍龙出海」"NOR"将之劈手格开。\n",
        ]),
});

int valid_learn(object me)
{
        if( (int)me->query_skill("dragonforce",1) < (int)me->query_skill("dragonfight",1)/2)
                return notify_fail("你的龙神心法还不够精湛，无法领会更深层的龙形搏击！\n");
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail("练龙形博击必须空手。\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed" ||usage=="parry";
}

int practice_skill(object me)
{
        if( (int)me->query_skill("dragonforce",1) < (int)me->query_skill("dragonfight",1)/2)
                return notify_fail("你的龙神心法还不够精湛，无法领会更深层的龙形搏击！\n");
        if( (int)me->query("sen") < 50)
                return notify_fail("你的精神无法集中了，休息一下再练吧。\n");
        if( (int)me->query("kee") < 50 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");
        if( (int)me->query("force") < 20 )
                return notify_fail("你的内力不够了。\n");
        me->receive_damage("kee", 30);
        me->add("force", -20);
        return 1;
}

mapping query_action(object me, object weapon)
{
	int i;
	if( random(20)==0 )
		return action[random(sizeof(action))];
	else
	{
		i = me->query_skill("dragonforce",1)/150;
		if( i<1 ) i = 1;
		if( i>6 ) i = 6;
		return action[random(i)];
	}	
}

string perform_action_file(string func)
{
	return CLASS_D("dragon") + "/dragonfight/" + func;
}

varargs mixed hit_ob(object me, object victim, int damage_bonus,int factor)
{
	if( !me || !victim || !me->is_killing(victim->query("id")) 
	 || damage_bonus < 50 ) 
		return 0;
	if( random(me->query_str()) > victim->query("str")/8 ) 
    	{
    		victim->receive_wound("kee", damage_bonus / 2,me,TYPE_PERFORM );
        	switch(random(11)) 
        	{
        		case 0: return HIB"$n"HIB"听到「喀啦」一声轻响，竟似是骨碎的声音！\n"NOR;
            		case 1: return HIB"$N劲力一吐，$n的$l发出「喀」地一声爆响！\n"NOR;
            		case 2: return HIB"只听见$n的$l「喀」地一声 ...\n"NOR;
			case 4: return HIB"$n"HIB"被$N"HIB"震得气血翻腾，大惊失色。\n"NOR;
			case 5: return HIB"$n"HIB"被$N"HIB"震得站立不稳，摇摇晃晃。\n"NOR;
            		case 6: return HIB"$n"HIB"「嘿」地一声退了两步。\n"NOR;
            		case 7: return HIB"$n"HIB"被震得半身发麻。\n"NOR;
            		case 8: return HIB"$n"HIB"$l有如受到一记重击，连退了五六步！\n"NOR;
            		case 9: return HIB"$n"HIB"眼前一黑，身子向後飞出丈许！\n"NOR;
			case 10: return HIB"$n"HIB"眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！\n"NOR;
		}
	}
}

string query_parry_msg(object weapon)
{
    return action[random(sizeof(action))]["parry_msg"];
}