//风波十二叉 fengbo-cha.c
//9-17-97 pickle
/*
风波十二叉    dodge  0    parry  -5    damage  25
因其有特别之处，建议各项暂设为中等。
*/

//pickle, not changed yet, please try to be compatible. 

// 昔人已乘黄鹤去，此地空余黄鹤楼
// 黄鹤一去不复返，白云千载空悠悠
// 晴川沥沥汉阳树，芳草凄凄鹦鹉洲
// 日暮乡关何处去，烟波江上使人愁

// 江上往来人，但爱鲈鱼美
// 君看一叶舟，出没风波里
inherit SKILL;

mapping *action = ({
        ([      "name"  : "「昔人已乘黄鹤去」",
                "action": "$N似乎在寻找些什么，手中$w在身前试探了数叉。叉尖所指之处，正是$n的$l，原来是「昔人已乘黄鹤去」。\n",
                "dodge" : 0,
		"parry" : 0,
                "damage" : 25,
                "damage_type" : "戳伤",
		"parry_msg": "$n挥动$W，在身前画了个半圆，正好挡开$N的攻势，原来是「昔人已乘黄鹤去」。\n",
        ]),
        ([      "name"  : "「此地空余黄鹤楼」",
                "action": "$N身形不动，手中$w用一招「此地空余黄鹤楼」，拍向$n的$l。这招似乎颇为窒滞生硬，但毫不拖泥带水，攻势甚是凌厉。\n",
                "dodge" : 0,
		"parry" : 0,
                "damage" : 35,
                "damage_type" : "瘀伤",
		"parry_msg": "$n丝毫不为所动，一招「此地空余黄鹤楼」轻描淡写地挥叉一刺，逼得$N回手自防。\n",
        ]),
        ([      "name"  : "「黄鹤一去不复返」",
                "action": "$N接连几个起落，作势欲走，$n忙疾追不迭。正在这时，$N于空中突然回身，一式「黄鹤一去不复返」直指$n的$l！\n",
                "dodge" : -10,
		"parry" : -10,
                "damage" : 30,
                "damage_type" : "刺伤",
		"parry_msg": "$n一抖手中$W，一式「黄鹤一去不复返」将$N兵器弹了开去。\n",
        ]),
        ([      "name"  : "「白云千载空悠悠」",
                "action": "$N一声清啸，但见漫天叉影，化作朵朵白云，扰得$n眼花缭乱这招「白云千载空悠悠」颇为传神，果然有一番前不见古人，后不见来者的气概。\n",
                "dodge" : -10,
		"parry" : -10,
                "damage" : 35,
                "damage_type" : "瘀伤",
		"parry_msg": "$n将$W舞得风雨不透，这招「白云千载空悠悠」颇为传神，$N无奈之下只好换招。\n",
        ]),
        ([      "name"  : "「晴川沥沥汉阳树」",
                "action": "$N手中$w一颤，用一招「晴川沥沥汉阳树」，迅捷无比地在$n上下左右各刺一叉。\n",
                "dodge" : -20,
		"parry" : -10,
                "damage" : 30,
                "damage_type" : "刺伤",
		"parry_msg": "$n以手中$W画了个圆弧，用一招「晴川沥沥汉阳树」将周身破绽都封死了。\n",
        ]),
        ([      "name"  : "「芳草凄凄鹦鹉洲」",
                "action": "$N施出一招「芳草凄凄鹦鹉洲」，只见$w若有若无地一探，看去势似乎刺向$n左侧数寸处，但不知怎的，转瞬间叉尖已到了$l！\n",
                "dodge" : -20,
		"parry" : -20,
                "damage" : 25,
                "damage_type" : "戳伤",
		"parry_msg": "$n施出一招「芳草凄凄鹦鹉洲」，怯生生地举叉一挡，似乎力不从心。但等到二人兵刃相交时，$W上忽然发出一股韧力，将$N挡了开去。\n",
        ]),
        ([      "name"  : "「日暮乡关何处去」",
                "action": "$N朗笑一声，手中$w泛出重重暗影，好似一阵阵浓雾，推向$n。$n看不透这招「日暮乡关何处去」的来路，实在不知如何招架。\n",
                "dodge" : -25,
		"parry" : -20,
                "damage" : 35,
                "damage_type" : "刺伤",
		"parry_msg": "$n不避不让，挺$W在身前空处连次数叉。这招「日暮乡关何处去」看来平平无奇，却于平淡中将$N的攻势封死了。\n",
        ]),
        ([      "name"  : "「烟波江上使人愁」",
                "action": "$n刚喘得一喘，却见$N身形一闪，已经踪影全无。$n还未来得及转身，$N的$w已到背后了。这招「烟波江上使人愁」果然轻快无比，令人防不胜防。\n",
                "dodge" : -15,
		"parry" : -15,
                "damage" : 45,
                "damage_type" : "戳伤",
		"parry_msg": "$n眼见$N攻势凌厉，忙用一招「烟波江上使人愁」，连转数圈，将$N的力拨在一边。\n",
        ]),
        ([      "name"  : "「江上往来人」",
                "action": "$N怒叱一声，手中$w齐快无比地在$n身前来来回回连划七划。这招「江上往来人」变幻无方，$n实在不知哪招是虚，哪招是实。\n",
                "dodge" : 5,
		"parry" : -15,
                "damage" : 50,
                "damage_type" : "戳伤",
		"parry_msg": "$n连挥手中$W，只听叮叮当当一阵密响，这招「江上往来人」变幻无方，终于将$N挡了回去。\n",
        ]),
        ([      "name"  : "「但爱鲈鱼美」",
                "action": "$N手中$w缓缓画了个圆圈，用一招「但爱鲈鱼美」慢慢向$n的$l套去。\n",
                "dodge" : -15,
		"parry" : -15,
                "damage" : 35,
                "damage_type" : "戳伤",
		"parry_msg": "$n似乎胸有成竹，「但爱鲈鱼美」一出，挺叉连划数个圆圈。$N看不透$n的守势，果然不敢贸然进攻。\n",
        ]),
        ([      "name"  : "「君看一叶舟」",
                "action": "$N身形一旋，冲天而起。手中$w借着下冲之势，一招「君看一叶舟」直插$n的$l。\n",
                "dodge" : -20,
		"parry" : -20,
                "damage" : 40,
                "damage_type" : "戳伤",
		"parry_msg": "$n看准来势，以$W向$N的兵刃猛点。只听「当」的一声巨响，一招「君看一叶舟」果然将$N的兵刃荡了开去。\n",
        ]),
        ([      "name"  : "「出没风波里」",
                "action": "$N突然脸上青气一显，叉上嗡嗡之声大做，正当$n惊诧时，$N狂风骤雨般连攻五叉。这招「出没风波里」是整套叉法的精髓，施将出来，不但变幻莫测，且声势惊人，$n顿时不知所措。\n",
                "dodge" : -15,
		"parry" : -15,
                "damage" : 45,
                "damage_type" : "戳伤",
		"parry_msg": "$n不顾自身，手中$W连连刺向$N。这「出没风波里」围魏救赵之计果然奏效，将$N逼了回去。\n",
        ]),
});


int valid_learn(object me)
{
	object ob;
	if( me->query("class")!="dragon" )
		return notify_fail("你非龙族，怎能习惯这水中出没的叉法？\n");
        if( (int)me->query_maxforce() < 100 )
                return notify_fail("你的内力不够，无法领会风波十二叉的精妙之处。\n");
	if( me->query_skill("dragonforce", 1) < me->query_skill("fengbo-cha", 1)/2)
		return notify_fail("你的龙神心法修为太低。\n");
        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "fork" )
                return notify_fail("你必须先找一柄叉来才能学叉法。\n");
        return 1;
}

varargs int practice_skill(object me,int flag)
{
	int level;
	string msg;
	if( me->query("family/family_name") != "东海龙宫")
		return notify_fail("你非龙族，怎能习惯这水中出没的叉法？\n");
    	if(me->query_skill_mapped("force") !="dragonforce")
		return notify_fail("风波十二叉必须配合龙神心法才能发挥威力。\n");
    	if(me->query("kee") < 50) 
    		return notify_fail("你的体力太弱，先休息一会儿吧。\n");
    	if(me->query("sen") < 50) 
    		return notify_fail("你的神智不清，就算练了也什么都学不到的。\n");
    	if(me->query("force") < 20) 
    		return notify_fail("你的内力不足，无法照路数舞叉。\n");
	me->add("kee", -30);
    	me->add("force", -3);
    	if( flag )
    	{
		level = me->query_skill("fengbo-cha", 1);
		level/= 100;
		if( level<1 )
			level = 1;
		if( level>12 )
			level = 12;
		msg = "你来来回回练习着风波十二叉，";
		msg+= "结果"+action[level-1]["name"]+"这一招似乎有些长进。\n";
		tell_object(me,msg);
	}
    	return 1;
}

int valid_enable(string usage)
{
        return usage=="fork"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
	int level;
	if( !me )
		return 0;
	if( !intp(level=me->query_temp("PERFORM_BIBO"))
	 && level<=0 )
	{	 		
		level = me->query_skill("fengbo-cha", 1);
		level/= 100;
	}	
	if( level<1 )
		level = 1;
	if( level>12 )
		level = 12;	
    	return action[random(level)];
}

string query_parry_msg(object weapon)
{
    return action[random(sizeof(action))]["parry_msg"];
}

string perform_action_file(string func)
{
return CLASS_D("dragon") + "/fengbo-cha/" + func;
}
