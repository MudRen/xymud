//【百花掌】baihua-zhang.c
// cglaem...12/08/96.
//menpai skill
//lestat modi for dtxy
//Snowtu 2008 修改降低命中和伤害
#include <ansi.h>
inherit SKILL;

void diezhang_hit(object me, object victim, object weapon, int damage);

mapping *action = ({
        ([      "action":"$N浅浅一笑，一招"+MAG"「自在飞花轻似梦」"+NOR"若有若无地拍向$n的$l",
                "dodge": -5,
                "parry": 5,
                "damage":50,
                "damage_type":"瘀伤",
        ]),
        ([      "action":"$N身形一顿，似有退意。$n正待反攻，忽见$N纤纤五指，直拂$n双目。正是“百花掌”之杀手"+HIR"「一枝红杏出墙来」"+NOR,
                "dodge": -10,
                "parry": -10,
                "damage":40,
                "damage_type":"刺伤",
                        "weapon":"右手掌",
        ]),
        ([      "action":"只见$N嫣然一笑，双掌翻飞，一招"+HIM"「人面桃花相映红」"+NOR"当真是妙到毫巅",
                "dodge": -20,
                "parry": -20,
                "damage":30,
                "damage_type":"瘀伤",
        ]),
        ([      "action":"$N纤腰一摆，陡然滑出数尺，右手顺势一招"+HIY"「黄菊枝头生晓寒」"+NOR"往$n的$l拍去",
                "dodge": 5,
                "parry": -15,
                "damage": 50,
                "damage_type":"瘀伤",
        ]),
            ([  "action":"只见$N双唇紧闭，面色凝重，一招"+HIW"「此花开尽更无花」"+NOR"全力击向$n的$l",
                "dodge": 5,
                "parry": 5,
                "damage":60,
                "damage_type":"瘀伤",
        ]),
});

mapping *action2 = ({
        ([      "action":"$N浅浅一笑，一招"+MAG"「自在飞花轻似梦」"+NOR"夹带着一股太阴之气若有若无地拍向$n的$l",
                "dodge": -7,
                "parry": 3,
                "damage":52,
                "damage_type":"瘀伤",
        ]),
        ([      "action":"$N身形一顿，似有退意。$n正待反攻，忽见$N纤纤五指，化作五股霞光直拂$n双目。正是“百花掌”之杀手"+HIR"「一枝红杏出墙来」"+NOR,
                "dodge": -12,
                "parry": -12,
                "damage":42,
                "damage_type":"刺伤",
		"weapon":"霞光",
        ]),
        ([      "action":"只见$N嫣然一笑，双掌翻飞，一招"+HIM"「人面桃花相映红」"+NOR"当真是妙到毫巅",
                "dodge": -22,
                "parry": -22,
                "damage":32,
                "damage_type":"瘀伤",
        ]),
        ([      "action":"$N纤腰一摆，陡然飘出数尺，右手顺势一招"+HIY"「黄菊枝头生晓寒」"+NOR"幻化出巨大的掌影往$n的$l拍去",
                "dodge": 3,
                "parry": -17,
                "damage": 52,
                "damage_type":"瘀伤",
        ]),
            ([  "action":"只见$N双唇紧闭，面色凝重，一招"+HIW"「此花开尽更无花」"+NOR"似月潮之浪涛全力击向$n的$l",
                "dodge": 3,
                "parry": 4,
                "damage":62,
                "damage_type":"瘀伤",
        ]),
});

mapping *action3 = ({
        ([      "action":"$N浅浅一笑，一招"+MAG"「自在飞花轻似梦」"+NOR"夹带着一股太阴之气若有若无地拍向$n的$l",
                "dodge": -10,
                "damage":55,
                "damage_type":"瘀伤",
        ]),
        ([      "action":"$N身形一顿，似有退意。$n正待反攻，忽见$N纤纤五指，化作五股霞光直拂$n双目。正是“百花掌”之杀手"+HIR"「一枝红杏出墙来」"+NOR,
                "dodge": -15,
                "parry": -15,
                "damage":45,
                "damage_type":"刺伤",
		"weapon":"霞光",
        ]),
        ([      "action":"只见$N嫣然一笑，双掌翻飞，一招"+HIM"「人面桃花相映红」"+NOR"当真是妙到毫巅",
                "dodge": -25,
                "parry": -25,
                "damage":35,
                "damage_type":"瘀伤",
        ]),
        ([      "action":"$N纤腰一摆，陡然飘出数尺，右手顺势一招"+HIY"「黄菊枝头生晓寒」"+NOR"幻化出巨大的掌影往$n的$l拍去",
                "parry": -20,
                "damage": 55,
                "damage_type":"瘀伤",
        ]),
            ([  "action":"只见$N双唇紧闭，面色凝重，一招"+HIW"「此花开尽更无花」"+NOR"似月潮之浪涛全力击向$n的$l",
                "parry": 1,
                "damage":65,
                "damage_type":"瘀伤",
        ]),
});

mapping *diezhang = ({
        ([      "action": HIC"$N"HIC"一笑百媚生，衣袖一甩，一式"+MAG"「月夜叠潮」"+NOR HIC"顺势而出，带着浩瀚的太阴之力拍向$n"HIC"的$l。\n"NOR,
		"dodge": -50,
		"parry": -50,
		"damage": 60,
		"damage_type": "瘀伤",
	]),
});

int valid_learn(object me)
{
        if( (string)me->query("gender") != "女性" )
                return notify_fail("百花掌是只有女子才能练的武功。\n");
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail("练百花掌必须空手。\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed";
}

mapping query_action(object me, object weapon)
{
	mapping* m_actions;
	if( me->query_temp("diezhang") )
		return diezhang[random(sizeof(diezhang))];
	if( me->query_level()<40 )
        	m_actions = action;
        else if( me->query_level()<80 )
        	m_actions = action2;
        else	m_actions = action3;
        return m_actions[random(sizeof(m_actions))];
}

int practice_skill(object me)
{
        if( (int)me->query("sen") < 30)
                return notify_fail("你的精神无法集中了，休息一下再练吧。\n");
        if( (int)me->query("kee") < 30 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");
        if( (int)me->query("force") < 10 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("sen", 30);
        me->add("force", -10);

        return 1;
}

string perform_action_file(string func)
{
return CLASS_D("moon") + "/baihua-zhang/" + func;
}

varargs mixed hit_ob(object me, object victim, int damage_bonus,int factor)
{
	int dayphase;
	if( !me || !living(me) || !victim || !me->is_fighting(victim)
	 || damage_bonus<2 )
		return 0;
	if( me->query("family/family_name")!="月宫" 
	 && me->query("chushi/chushi_moon")!="yes" )
		return 0;	
	if( !me->is_killing(victim->query("id")) )
		return 0;
					
	dayphase =NATURE_D->query_current_day_phase();
	if( dayphase>=6 )
		return damage_bonus/2;
	return 0;
}