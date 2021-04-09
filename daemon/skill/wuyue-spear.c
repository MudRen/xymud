//wuyue-spear 五岳神
#include <ansi.h>
#include <combat.h>
inherit SKILL;

string *msg1 =({
        "$n使出一招「",
        "$n运足精神，好一招「",
        "$n一个虎跳使出个「",
        "$n神态悠闲，一招「",
        "$n人枪合一，突然一招「",
        "$n一口气抖出五朵枪花，暗喝一声「",
});

string *msg2 =({
	"泰山压顶","华岳插云","衡峰溪绕","五岳朝宗","太室参佛","恒岭悬空",
});	

string *msg3 =({
        "」将之挡开。\n",
        "」格开了这招。\n",
        "」势若飞瀑挡住了。\n",
        "」挡开了这招。\n",
        "」将这招挡住了。\n",
        "」将这招格开了。\n",
});

mapping *action = ({
        ([      "action": "$N使一招"+HIM"「泰山压顶」"NOR"，手中$w向$n劈头改脑直扫了下来。\n",
                "damage":               60,
                "dodge":                -15,
                "parry":                -15,
                "damage_type":  "刺伤"
        ]),
        ([      "action": "$N运足精神，抖起$w，一招"+HIC"「华岳插云」"NOR"挑向$n$l。\n",
                "damage":               60,
                "dodge":                -5,
                "parry":                -10,
                "damage_type":  "刺伤"
        ]),
        ([      "action": "$N手中$w势若飞瀑刺向$n的$l，好一招"+HIG"「衡峰溪绕」"NOR"。\n",
                "damage":               65,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "刺伤"
        ]),
        ([      "action": "$N 一口气抖出五朵枪花，暗喝一声"+HIB"「五岳朝宗」"NOR"。枪枪不离$n要害。\n",
        	"limb" : ({"后心","胸口","头部",})[random(3)],
                "damage":               70,
                "dodge":                -10,
                "parry":                -15,
                "damage_type":  "刺伤"
        ]),
        ([      "action": "只见$N一个虎跳使个"+HIY"「太室参佛」"NOR"，手中$w带出一道利闪直奔$n$l。\n",
                "damage":               70,
                "dodge":                -5,
                "parry":                -5,
                "damage_type":  "刺伤"
        ]),
        ([      "action": "只见$N腾空飞气，人枪合一，$w只落$n$l，正是一招"+HIW"「恒岭悬空」"NOR"。\n",
                "damage":               70,
                "dodge":                -5,
                "parry":                -15,
                "damage_type":  "刺伤"
        ]),
});
int valid_learn(object me)
{
        object ob;
        if( (int)me->query_maxforce()<100 )
                return notify_fail("你的内力不够，没有办法练五岳神枪。\n");
        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "spear" )
                return notify_fail("你必须先找一柄枪才能练枪法。\n");
        return 1;
}

int valid_enable(string usage)
{
        return (usage=="spear") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

varargs int practice_skill(object me,int flag)
{
        object weapon;
	if( (string)me->query_skill_mapped("force")!= "huomoforce")
     		return notify_fail("五岳神枪必须配合火魔心法才能练。\n");
        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "spear" )
                return notify_fail("你必须先找一柄长枪或者是类似的武器，才能练枪法。\n");
        if( (int)me->query("kee") < 30 
        ||    (int)me->query("force") < 25  )
                return notify_fail("你的体力不够练这门枪法，还是先休息休息吧。\n");
        me->receive_damage("kee", 30);
        me->add("force", -25);
	if ( flag )        write("你按着所学练了一遍五岳神枪。\n");
        return 1;
}

string perform_action_file(string func)
{
	return CLASS_D("kusong") + "/wuyue-spear/" + func;
}

varargs mixed hit_ob(object me, object victim, int damage_bonus,int factor)
{
	if( !me || !victim || !me->is_killing(victim->query("id")) ) 
		return 0;
	if( !me->query_temp("CX_perform") )
		return 0;
	damage_bonus = damage_bonus/2+random(damage_bonus/2)+10;		
	victim->receive_wound("kee", damage_bonus/2+1,me,TYPE_PERFORM );
        switch(random(5)) 
        {
		case 0: return YEL"$n"YEL"的头发冒起一股青烟！\n"NOR;
            	case 1: return HIB"$n"HIB"身上滋滋作响！\n"NOR;
		case 2: return HIR"$n"HIR"的脸上膨起几个大水疱！\n"NOR;
		case 4: return HIY"$n"HIY"$l发出一股焦味！\n"NOR;
	}		
}

string query_parry_msg(object me,object target)
{
	if( !me || !target )
		return 0;
	if( !me->query_temp("weapon") )
		return 0;
        return "结果"+msg1[random(sizeof(msg1))]+HIC+msg2[random(sizeof(msg2))]+NOR+msg3[random(sizeof(msg3))];
}
