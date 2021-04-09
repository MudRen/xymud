// Bloodystrike.c 密宗大手印
// Cracked by 凌惊雪 4-22-2003

inherit SKILL;
mapping *action = ({
        ([      "action":               
"$N使出一招「苦海端无涯」，左掌虚幌，右掌穿出击向$n的$l",
                "dodge":                -30,
                "parry":                -30,
                "force":                100,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N使出一招「地狱似有门」，左掌化虚为实击向$n的$l",
                "dodge":                -30,
                "parry":                -30,
                "force":                100,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N使出密宗大手印中的「天堂却无路」，一掌拍向$n的$l",
                "dodge":                -30,
                "parry":                -30,
                "force":                125,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N双掌一错，使出「密宗为独尊」，对准$n的$l连续拍出",
                "dodge":                -30,
                "parry":                -30,
                "force":                150,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N左掌立于胸前，右掌推出，一招「万念皆是空」击向$n$l",
                "dodge":                -30,
                "parry":                -30,
                "force":                175,
                "damage_type":  "瘀伤"
        ]),
        ([      "action":               
"$N使出「佛云以杀止杀」，身形凌空飞起，从空中当头向$n的$l出掌攻击",
                "dodge":                -40,
                "parry":                -40,
                "force":                200,
                "damage_type":  "瘀伤"
        ]),
});

int valid_learn(object me)
{
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail("练密宗大手印必须空手。\n");
        return 1;
}

int valid_enable(string usage) { return usage=="unarmed"; }

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30 )
                return notify_fail("你的体力不够了，休息一下再练吧。\n");
        if( (int)me->query("force") < 5 )
                return notify_fail("你的内力不够了，休息一下再练吧。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        return 1;
}
 

string perform_action_file(string func)
{
	return CLASS_D("sanxian") + "/bloodystrike/" + func;
}


