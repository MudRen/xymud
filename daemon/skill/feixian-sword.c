// Feixian-sword.c 飞仙剑法
// Cracked by 凌惊雪 5-20-2003

inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「峰回路转」，手中$w如一条银蛇般刺向$n的$l",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//1
([      "action" : "$N使一招「峰回路转」，手中$w如一条银蛇般刺向$n的$l",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//2
([      "action" : "$N使出飞仙剑法中的「空山鸟语」，剑光霍霍斩向$n的$l",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//3
([      "action" : "$N一招「御风而行」，身形陡然滑出数尺，手中$w斩向$n的$l",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//4
([      "action" : "$N手中$w中宫直进，一式「旭日东升」对准$n的$l刺出一剑",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//5
([      "action" : "$N纵身一跃，手中$w一招「金光泻地」对准$n的$l斜斜刺出一剑",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//6
([      "action" : "$N的$w凭空一指，一招「一剑西来」刺向$n的$l",
        "dodge" : -50,
        "parry" : -50,
        "damage" : 100,
        "damage_type" : "刺伤",
]),
//7
([      "action" : "$N手中$w向外一分，使一招「柳暗花明」反手对准$n$l一剑刺去",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
//8
([      "action" : "$N横剑上前，身形一转手中$w使一招「仙云密布」画出一道光弧刺向$n的$l",
        "dodge" : -20,
        "parry" : -30,
        "damage" : 40,
        "damage_type" : "刺伤",
]),
});


int valid_enable(string usage) 
	{ 
		return (usage == "sword") || (usage == "parry"); 
	}

int valid_learn(object me)
{
        if (me->query("chushi/chushi_shushan") != "yes" )
                return notify_fail("你没有领悟「飞仙剑法」的窍门。\n");
        if ((int)me->query("max_force") < 1000)
                return notify_fail("你的内力太弱，无法练「飞仙剑法」。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
	int i = me->query_temp("pfm-feixian");
	if( !me->query_temp("pfm-feixian") ) {
        return action[random(sizeof(action))];
	}
	else
	{
	return action[i];
	}
}

int practice_skill(object me)
{
        if (me->query("chushi/chushi_shushan") != "yes" )
                return notify_fail("你没有领悟「飞仙剑法」的窍门。\n");
        if ((int)me->query("kee") < 60)
                return notify_fail("你的体力不够练「飞仙剑法」。\n");
        if ((int)me->query("force") < 50)
                return notify_fail("你的内力不够练「飞仙剑法」。\n");
        me->receive_damage("kee", 50);
        return 1;
}
string perform_action_file(string func)
{
return CLASS_D("chushi") + "/feixian-sword/" + func;
}
