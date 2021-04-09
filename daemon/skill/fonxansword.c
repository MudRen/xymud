// fonxansword.c
//not used yet...

inherit SKILL;

mapping *action = ({
	([	"action":		"$N使一招「峰回路转」，手中$w如一条银蛇般刺向$n的$l",
		"dodge":		0,
		"damage":		30,
		"damage_type":	"刺伤"
	]),
	([	"action":		"$N使出封山剑法中的「空山鸟语」，剑光霍霍斩向$n的$l",
		"dodge":		0,
		"damage":		30,
		"damage_type":	"割伤"
	]),
	([	"action":		"$N一招「御风而行」，身形陡然滑出数尺，手中$w斩向$n的$l",
		"dodge":		0,
		"damage":		20,
		"damage_type":	"割伤"
	]),
	([	"action":		"$N手中$w中宫直进，一式「旭日东升」对准$n的$l刺出一剑",
		"dodge":		0,
		"damage_type":	"刺伤"
	]),
	([	"action":		"$N纵身一跃，手中$w一招「金光泻地」对准$n的$l斜斜刺出一剑",
		"dodge":		0,
		"damage_type":	"刺伤"
	]),
	([	"action":		"$N的$w凭空一指，一招「童子引路」刺向$n的$l",
		"dodge":		0,
		"damage":		40,
		"damage_type":	"刺伤"
	]),
	([	"action":		"$N手中$w向外一分，使一招「柳暗花明」反手对准$n$l一剑刺去",
		"dodge":		0,
		"damage":		20,
		"damage_type":	"刺伤"
	]),
	([	"action":		"$N横剑上前，身形一转手中$w使一招「空谷秋虹」画出一道光弧斩向$n的$l",
		"dodge":		0,
		"damage":		10,
		"damage_type":	"割伤"
	]),
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("你的内力不够，没有办法练封山剑法。\n");

	if( (string)me->query_skill_mapped("force")!= "fonxanforce")
		return notify_fail("封山剑法必须配合封山派内功才能练。\n");

	if( !(ob = me->query_temp("weapon"))
	||	(string)ob->query("skill_type") != "sword" )
		return notify_fail("你必须先找一把剑才能练剑法。\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30
	||	(int)me->query("force") < 3 )
		return notify_fail("你的内力或气不够，没有办法练习封山剑法。\n");
	me->receive_damage("kee", 30);
	me->add("force", -3);
	write("你按着所学练了一遍封山剑法。\n");
	return 1;
}

string perform_action_file(string action)
{
	return CLASS_D("public") + "/fonxansword/" + action;
}
