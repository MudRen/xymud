//枯骨刀法, kugu-blade.c
//modified 4-17-97 pickle

/*
枯骨刀 
无底洞之杀手绝学，刀法专注进攻，使用此项武功需持
枯骨刀才能发挥出威力，因其重招不重力，用普通的刀
伤害力不大。
*/
// 尸横遍野，行尸走肉，尸山血海，借尸还魂，马革裹尸，毁尸灭迹
#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([      
        	"name"  : "尸横遍野",
                "action": "$N在$n四周滚来滚去，手中$w招招不离$n的下盘，这招"+HIW"「尸横遍野」"NOR"果然奏效，逼得$n手忙脚乱。\n",
                "parry_msg": "结果$n一招"+HIW"「尸横遍野」"NOR"将$N逼得手忙脚乱。\n",
                "dodge" : -30,
		"parry" : -15,
                "damage": 30,
                "damage_type": "砍伤",
		"dodge_msg":"$N连打七八个滚，虽看似狼狈不堪，却巧妙地躲过了$n的攻势。\n",
        ]),
        ([      "name"  : "借尸还魂",
                "action": "激战中，$N忽然将$w收在身旁，直挺挺的倒下。正在$n不知所措之时，$N的$w如毒蛇一般突然向$n的$l飞去，正是一招"+HIW"「借尸还魂」"NOR"。\n",
                "dodge" : -15,
		"parry" : -30,
                "damage": 30,
                "damage_type": "戳伤",
		"dodge_msg": "$N似乎已经打中了$n时，$n突然原地疾转，化为一片黑影不见了。\n",
		"parry_msg": "$n连忙使一招"+HIW"「借尸还魂」"NOR"，举$W一挡，借势疾退开去。\n",
        ]),
        ([      "name"  : "尸山血海",
                "action": "$N左手运起排山倒海的掌力，右手$w舞出夺目的寒光，笼罩住$n的全身。\n",
                "dodge" : -10,
		"parry" : -20,
                "damage": 35,
                "damage_type": "劈伤",
		"dodge_msg": "$n平平跃起，在空中连转数圈，落在$N身后。原来是"+HIR"「尸山血海」"NOR"。\n",
		"parry_msg": "$n展开$W疾挥，但见漫天刀影，这招"+HIR"「尸山血海」"NOR"果然将$N的攻势挡了回去。\n",
        ]),
        ([      "name"  : "毁尸灭迹",
                "action": "$N忽然间脸色苍白，身体软软的消失在黑暗中。$n在激战中突然不见了敌人，惊慌失措间，$N运起了"+HIW"「毁尸灭迹」"NOR"的半招进攻，一刀向$n的后脑砍去。\n",
                "limb"  : "头部",
                "dodge" : -10,
		"parry" : -20,
                "damage": 35,
                "damage_type": "砍伤",
		"dodge_msg": "$N似乎就要击中了$n，但$n腰身连扭数下，将攻势避了过去。$N虽然看得一清二楚，却道不出这招"+HIW"「毁尸灭迹」"NOR"的奥妙。\n",
		"parry_msg": "$n看准来势，举$W迎去。只听「噗」地一声闷想，$n的人影已不见了。\n",
        ]), 
        ([      "name"  : "马革裹尸",
                "action": "只见$N运起轻功，好似一堵无形的墙壁，向$n徐徐推近。急转中$N忽然一刀砍向$n的$l，好一招"+HIW"「马革裹尸」"NOR"。\n",
                "dodge" : -10,
                "parry" : -30,
                "damage": 40,
                "damage_type": "砍伤",
		"dodge_msg": "$n「吱吱」尖叫数声，双脚一点，从$N头顶翻了过去。\n",
		"parry_msg": "$n原地不动，身子如陀螺般疾转。$N虽然命中，却被$n卸去劲力。\n",
        ]),
        ([      "name"  : "行尸走肉",
                "action": "$N门户大开，就象丧失了神志一般，自身跟着手中的$w向$n扑去。这招"+HIW"「行尸走肉」"NOR"虽然凶险，但威力奇大，逼的$n连连倒退。\n",
                "dodge" : -30,
                "parry" : -30,
                "damage": 40,
                "damage_type": "砍伤",
		"dodge_msg": "$n忙用一招"+HIW"「行尸走肉」"NOR"，膝盖不弯，硬梆梆地连蹦数下，居然避过了$N的招数。\n",
		"parry_msg": "$n眼见招来，竟然不避不让，以身相迎。只听「噗」地一声，$N的进攻如中败竹，居然对$n毫无影响。\n",
        ]),
});

int valid_learn(object me)
{
        object ob;

	if(me->query("family/family_name") != "陷空山无底洞")
        	return notify_fail("你不习惯血腥，学不了枯骨刀！\n");
	if( (int)me->query_maxforce() < 350 )
		return notify_fail("你的内力不够，不能学枯骨刀法，多练些内力再来吧。\n");
	if( (int)me->query_skill("kugu-blade")>=me->query("family/sell_reward"))
        	return notify_fail("你的枯骨刀已经到了极限，需要更多的血腥来加深修为！\n");
        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade" )
		return notify_fail("你必须先找一把刀才能练刀法。\n");
        return 1;
}

int practice_skill(object me)
{
	if( me->query_skill("kugu-blade", 1) < 180)
        	return notify_fail("你的修为还不足以练枯骨刀。\n");
    	if(  me->query("family/master_id") != "yu shu" )
		return notify_fail("师父还没有教你如何练习枯骨刀的法门。\n");
    	if( me->query("kee") < 50)
		return notify_fail("你的体力不足，无法练枯骨刀。\n");
    	if( me->query("force") < 50)
		return notify_fail("你的内力太低，无法在纵跃的同时舞刀。\n");
    	me->add("kee", -10);
    	me->add("force", -50);
	return 1;
}

int valid_enable(string usage)
{
        return usage=="dodge"||usage=="blade"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_parry_msg(object weapon)
{
	return action[random(sizeof(action))]["parry_msg"];
}
string query_dodge_msg(string limb)
{
	return action[random(sizeof(action))]["dodge_msg"];
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string func)
{
	return CLASS_D("wdd") + "/kugu-blade/"+func;
}

mixed hit_ob(object me,object victim,int damage)
{
	int v;
	string *m1,*m2,msg;
	if( !me || !victim || !me->is_killing(victim->query("id")) 
	 || !living(me) || random(damage)<10 )
	 	return 0;
	 if( random(me->query("bellicosity"))<50 
	  || random(me->query_cor())<20 
	  || random(10)<3 )
	 	return 0;
	v = random(me->query("bellicosity")/100)+1;
	me->add("family/sell_reward",v);
	if( !me->query("env/brief_message") )
		tell_object(me,HIY"【系统】你的血腥值增加了"HIR+v+HIY"点。\n"NOR);
	m1 = ({
		NOR RED"$N"RED"煞气熏天，",
		NOR RED"$w"RED"上血光一闪，",
		NOR RED"$N"RED"脸上杀气缭绕，",
		NOR RED"$w"RED"上绽放道道血光，",
		
	});
	m2 = ({
		"$N"RED"脸上的戾气愈加浓烈。"NOR"\n",
		"宛如魔神，叫人望之心惊。"NOR"\n",
		"将$N"RED"映衬得宛如魔神。"NOR"\n",
	});
	msg = m1[random(sizeof(m1))]+m2[random(sizeof(m2))];
	return msg;
}