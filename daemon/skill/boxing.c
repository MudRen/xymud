inherit SKILL;

mapping *action = ({
([  "action" : "\n$N一记勾拳，勾向$n的$l。\n",
        "force" : 10,
        "dodge" : 5,
        "damage": 50,
        "damage_type" : "抓伤",
]),
([      "action" : "$N一记直拳，直捣$n的$l。",
        "force" : 200,
        "dodge" : 10,
        "damage": 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一记摆拳，直摆$n的$l。",
        "force" : 230,
        "dodge" : 10,
        "damage": 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "\n$N一记重拳，击向$n的$l。",
        "force" : 230,
        "dodge" : 25,
        "damage": 70,
        "damage_type" : "内伤"
]),
([      "action" : "$N一套组合拳，直攻$n的要害部位。",
        "force" : 20,
        "dodge" : 15,
        "damage": 90,
        "damage_type" : "瘀伤",
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"|| usage=="hand"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练拳击必须空手。\n");
        if ((int)me->query("max_force") < 200)
                return notify_fail("你的内力太弱，无法练拳击。\n");
        if ( me->query_skill("boxing",1)>500 && me->query("family/family_name") )
                return notify_fail("你是有门派的人了，学这些杂七杂八的东西作甚？\n");
        return 1;
}

varargs int practice_skill(object me,int flag)
{
        int i = me->query_skill("boxing",1)/30;
        if( i<1 ) i = 1;
        if( i>10 ) i = 10;
        i*= 10;
        if( (int)me->query("kee") < i
        || (int)me->query("force") < i/10 )
                return notify_fail("你的内力或气不够，没有办法练习。\n");
        if ( me->query_skill("boxing",1)<=100 )
                return notify_fail("你现在的等级太低，难以练习。\n");
        me->receive_damage("kee",i);
        me->add("force", -i/10);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

/* mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("boxing", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}*/

mapping query_action(object me, object weapon)
{
return action[random(sizeof(action))];
}
string perform_action_file(string func)
{
return CLASS_D("12gong") + "/boxing/" + func;
}
