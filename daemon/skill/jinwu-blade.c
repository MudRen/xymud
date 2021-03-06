// Jinwu-dao.c 金乌刀
// Cracked by 凌惊雪 4-17-2003

inherit SKILL;

mapping *action = ({
([	"action" : "$N藏刀内收，一招「开门楫盗」，刀锋自下而上划了个半弧，向$n的$l挥去",
	"force" : 60,
        "dodge" : -20,
        "parry" : -25,
	"damage": 50,
	"skill_name" : "开门楫盗",
	"damage_type" : "割伤"
]),
([	"action" : "$N左掌虚托右肘，一招「梅雪逢夏」，手中$w笔直划向$n的$l",
	"force" : 60,
        "dodge" : -20,
        "parry" : -20,
	"damage": 60,
	"skill_name" : "梅雪逢夏",
	"damage_type" : "割伤"
]),
([	"action" : "$N一招「千钧压驼」，$w绕颈而过，刷地一声自上而下向$n猛劈",
	"force" : 60,
        "dodge" : -15,
        "parry" : -25,
	"damage": 70,
	"skill_name" : "千钧压驼",
	"damage_type" : "割伤"
]),
([	"action" : "$N右手反执刀柄，一招「赤日金鼓」，猛一挫身，$w直向$n的颈中斩去",
	"force" : 60,
        "dodge" : -5,
        "parry" : -25,
	"damage": 80,
	"skill_name" : "赤日金鼓",
	"damage_type" : "割伤",
]),
([	"action" : "$N一招「汉将当关」，无数刀尖化作点点繁星，向$n的$l挑去",
	"force" : 80,
        "dodge" : -20,
        "parry" : -25,
	"damage": 90,
	"skill_name" : "汉将当关",
	"damage_type" : "割伤"
]),
([	"action" : "$N双手合执$w，一招「鲍鱼之肆」，拧身急转，刀尖直刺向$n的双眼",
	"force" : 90,
        "dodge" : -15,
        "parry" : -35,
	"damage": 100,
	"skill_name" : "鲍鱼之肆",
	"damage_type" : "割伤"
]),
([	"action" : "$N一招「旁敲侧击」，手中$w划出一个大平十字，向$n纵横劈去",
	"force" : 90,
        "dodge" : -15,
        "parry" : -35,
	"damage": 110,
	"skill_name" : "旁敲侧击",
	"damage_type" : "割伤"
]),
([	"action" : "$N反转刀尖对准自己，一招「长者折枝」，全身一个翻滚，$w向$n拦腰斩去",
	"force" : 110,
        "dodge" : -20,
        "parry" : -30,
	"damage": 90,
	"skill_name" : "长者折枝",
	"damage_type" : "割伤"
]),
([	"action" : "$N一招「赤日炎炎」，$w的刀光仿佛化成一簇簇烈焰，将$n团团围绕",
	"force" : 110,
        "dodge" : -10,
        "parry" : -40,
	"damage": 100,
	"skill_name" : "赤日炎炎",
	"damage_type" : "割伤"
]),
([	"action" : "$N刀尖平指，一招「大漠风沙」，一片片切骨刀气如飓风般裹向$n的全身",
	"force" : 100,
        "dodge" : -35,
        "parry" : -45,
	"damage": 90,
	"skill_name" : "大漠风沙",
	"damage_type" : "割伤"
]),
});

int valid_enable(string usage)

{ return (usage == "blade") || (usage == "parry"); }

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}
varargs int practice_skill(object me,int flag)
{
       if( (int)me->query("kee") < 100
        ||      (int)me->query("force") < 100 )
                return notify_fail("你的内力或气不够，没有办法练习金乌刀。\n");
        me->receive_damage("kee", 100);
        me->add("force", -100);
       if ( flag )  write("你按着所学练了一遍金乌刀。\n");
        return 1;
}

string perform_action_file(string func)
{
return CLASS_D("suburb") + "/jinwu-blade/" + func;
}

