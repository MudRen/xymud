#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([      "action" : "$N轻抚手中的$w，突然间只见刀光一闪，再闪，又一闪！三道刺骨的寒气已然袭上了$n的$l",
     		"dodge":     10,
     		"parry":     10,
     		"damage":     35,
     		"damage_type":     "割伤"
        ]),
        ([      "action": "只见$N倒提$w，身形急冲，就在与$n错身之际，突然反手一刀从$n后脑斜劈而下",
     		"dodge":     5,
     		"parry":     5,
		"damage":    40,
                "damage_type":     "劈伤"
        ]),
        ([      "action": "$N斜身飞起，带出一片匹练也似的刀光卷向$n的$l",
                "damage":                  45,
                "damage_type":     "劈伤"
        ]),
        ([      "action": "$N突然一脚踢出，手中的$w划出一道轻妙的圆弧，淡淡的刀光封住了$n的头脸，切断了$n的呼吸",
		"dodge":     -5,
     		"parry":     -5,
		"damage":    50,
                   "damage_type":     "割伤"
        ]),
        ([      "action": "只见$N脸色一寒，一招「千里冰封」使出，从眉捷到脚跟，$n周身的血液都似被这无尽的刀势冻住，而生命也仿佛要离体而去",
		"dodge":  -10,
     		"parry":  -10,
		"damage":   55,
                   "damage_type":     "劈伤"
        ]),   
        ([      "action": "$N刀势渐慢，而$w上带出的寒气却越来越浓。就在这时，$n的心头一紧，一道比针尖还要锐利的寒气已刺上了$n$l",
		"dodge":                   -15,
     		"parry":     -15,
		"damage": 60,
		"damage_type":     "刺伤"
        ]),   
        ([      "action": "$N也不管三七二十一，高举$w呼！地就是一刀向$n迎面斩下！虽然只有一刀，可怕的刀势却似万古不化的寒冰封死了$n的一切退路",
		"dodge":                   -20,
     		"parry":     -20,
		"damage":   65,
		"damage_type":     "劈伤"
        ]),   
});


int valid_learn(object me)
{
        object ob;

        if( (int)me->query_maxforce() < 100 )
                return notify_fail("你的内力不够，没有办法练冰魄寒刀，多练些内力再来吧。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade"
        ||      (string)ob->query("material") != "ice" )
                return notify_fail("你必须先找一把冰做的刀才能练冰魄寒刀。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="blade"; //note, should not be able to enable with parry...ice mah:D
}

mapping query_action(object me, object weapon)
{
	int i;
     	i = me->query_skill("bingpo-blade",1)/60;
     	if( i>7 )
     		i = 7;
     	if( random(10)==1 )		
     		return action[random(sizeof(action))];
     	else	return action[random(i)];
}

varargs int practice_skill(object me,int flag)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 5 )
                return notify_fail("你的内力或气不够，没有办法练习冰魄寒刀。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
	if ( flag )        write("你按着所学练了一遍冰魄寒刀。\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
    return CLASS_D("xueshan")+"/bingpo-blade/"+action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon = me->query_temp("weapon");     
  	string msg;
       	if( me->query_temp("ningxie") )
       		return 0;
	if(me->query("force")<200) 
		return 0;
	if( me->query("force_factor")<1 )
		return 0;	
        if( (string)me->query("family/family_name") != "大雪山" )
        	return 0;
        if( (!weapon) || random(me->query_skill("throwing",1))<50 )
		return 0; 
	if(damage_bonus<10) damage_bonus= 10;
	if (((int)me->query_skill("blade", 1)/2) > random((int)victim->query_skill("force", 1)))
	{
		victim->receive_wound("kee", (damage_bonus/2)+1,me );
              	msg = HIW"$N"HIW"默运真气，将$w"HIW"中寒气逼出，"NOR;
                switch(random(3)) 
                {
                        case 0:	
                        	msg+= HIW"只见一丝寒气无声无息地钻到$n"HIW"体内！\n"NOR;
				break;
			case 1:
                               	msg+= HIW"在$n"HIW"的伤口上留下一道浅浅的白印！\n"NOR;
				break;
			default :
				msg+= HIW"$n"HIW"突然觉得体内奇寒难忍...\n"NOR;
                                break;
		}
		if( COMBAT_D->query_message_type(me,victim)==2 )
			msg = "结果对$n造成了"HIR+((damage_bonus/2)+1)+NOR"点气血损失，";
		return msg;
	}
	return 0;
 }
