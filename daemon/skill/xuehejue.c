// Xuehejue.c 血河诀
// Cracked by 凌惊雪 2-7-2003
#include <ansi.h>
#include <combat.h>
inherit SKILL;

mapping *action = ({
([  
	"action" : "$N一招「血河倒泻」，纵身跃起手中$w轻挥，斩向$n后颈。\n",
	"limb" : "颈部",
        "dodge":                -10,
        "parry":                -10,
        "damage":                65,
        "damage_type":  "割伤",
	"skill_name": "血河倒泻",
]),
([  
	"action" : "$N手中$w连画三个弧形，大叫「血气弥漫」，一道血气化作巨刃，向$n的右臂齐肩斩落。\n",
	"limb" : "右臂",
        "dodge":                -15,
        "parry":                -15,
        "damage":                70,
        "weapon": "血刃",
        "damage_type": "割伤"
]),
([  	"action" : "$N轻吁一声，刷刷刷刷四下，血色气箭向$n胸，腹，腰，肩四处连刺，好一招「血雾纷飞」！\n",
        "dodge":                -20,
        "parry":                 -30,
        "damage":                75,
        "weapon": "血箭",
        "damage_type": "刺伤"
]),
([  	"action" : "$N手中$w轻轻一抖，「血气惊天」斜行向前，$w冲出一道血色长枪迅捷无比，击向$n的$l。\n",
        "dodge":                -25,
        "parry":                 -20,
        "damage":                80,
        "weapon": "血枪",
        "damage_type": "刺伤"
]),
([  	"action" : "$N身行突变，仰天一声清啸「"HIR"血洗天河"NOR"」，$w舞动如风，化作漫天血光，盖向$n的$l。\n",
        "dodge":                -25,
        "parry":                 -20,
        "damage":                85,
        "weapon": "血光",
        "damage_type": "刺伤"
]),
([  	"action" : "$N身行突变，仰天一声清啸「"HIR"血流成河"NOR"」，$w上血光细凝成线，迅捷无比，刺向$n的$l。\n",
        "dodge":                -25,
        "parry":                 -20,
        "damage":                90,
        "skill_name": "血流成河",
        "damage_type": "刺伤"
]),
([  	"action" : "$N身行突变，仰天一声清啸「"HIR"血冻冰川"NOR"」，斜飞向右，$w横削直击，迅捷无比，击向$n的$l，御风而回。\n",
        "dodge":                -45,
        "parry":                 -40,
        "damage":                95,
        "skill_name": "血冻冰川",
        "damage_type": "刺伤"
]),
([  	"action" : "$N身行突变，「"HIR"血满江红"NOR"」运起漫天血光，带着压倒一切的气势击向$n的$l。\n",
        "dodge":                -55,
        "parry":                 -50,
        "damage":                150,
        "weapon": "血光",
        "damage_type": "刺伤"
]),
([  	"action" : "$N身形一顿，一式「"HIR"血气冲天"NOR"」，背后血光冲天，带着呼啸之声压向$n的$l。\n",
        "dodge":                -65,
        "parry":                 -60,
        "damage":                150,
        "weapon": "血光",
        "damage_type": "砸伤"
]),
([  	"action" : "$N身化血影，一式「"HIR"血踪万里"NOR"」在$n周身游走，道道血气刺向$n的$l。\n",
        "dodge":                -75,
        "parry":                 -70,
        "damage":                150,
        "weapon": "血气",
        "damage_type": "刺伤"
]),
});

int valid_enable(string usage) 
{ 
	return usage == "sword" || usage == "blade" || usage == "stick" || usage == "fork" || usage == "whip" || usage == "hammer" || usage == "mace" || usage == "spear" || usage == "staff" || usage == "parry"; 
} 

int valid_learn(object me)
{
	int i = (int)me->query_skill("xuehejue",2);
	int j = (int)me->query_skill("force",2);
	int k = (int)me->query("mark/luoyang_xuehejue");
	
	if( me->query("public_skill/xuehejue_abandon") )
		return notify_fail("你曾经放弃学习过血河诀，现在再也不能学习了。\n");
	if( me->query_skill("pingfeng",2)>=1 )
		return notify_fail("你既然已经学了屏风四扇门，就不能三心二意。\n");
	if( me->query("killerside") != "killer")
		return notify_fail("你不是金衣楼门下，难以领会血河诀的精髓。\n");
	if( j<300 )
		return notify_fail("你的内功修为太低，强学这门功夫没用的，小心走火入魔。\n");
	if( i>=k*10 )
		return notify_fail("你的实战能力不够，需要更多的「"HIY"血河诀"NOR"」学习点数。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i = (int)me->query_skill("xuehejue", 1);
  	int j = me->query_temp("XHJ");
  	if( !me->query_temp("XHJ") ) 
  	{
    		i = i/60;
		if(i>sizeof(action)-1)
			i=sizeof(action)-1;
        	return action[random(i)];
  	}
  	else
  	{
  		if( j<1 )
  			j = 1;
  		if( j>sizeof(action))
			j=sizeof(action);
  		return action[j-1];
  	}
}

varargs int practice_skill(object me,int flag)
{
	if( (int)me->query("kee") < 50 || (int)me->query("force") < 20 )
		return notify_fail("你的内力或气不够，没有办法练习屏风四扇门。\n");
 	me->receive_damage("kee",20);
 	me->add("force", -20);
	if( flag )  
		write("你按着所学练了一遍血河诀。\n");
 	return 1;
}

string perform_action_file(string action)
{
	return CLASS_D("public") + "/xuehejue/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if( !me || !victim || !me->is_killing(victim->query("id")) 
	 || damage_bonus < 10 ) 
	 	return 0;
	if( me->query_skill("pingfeng",2)>=1 )
		return 0;
	if( me->query_skill("xuehejue",2)<200 )
		return 0;
	if( random(damage_bonus) > victim->query_str()/5) 
	{
		damage_bonus = damage_bonus/2+random(damage_bonus/3);
		if( me->query("force_factor")>0 )
			damage_bonus = victim->receive_wound("kee", damage_bonus, me,TYPE_PERFORM);
		if( damage_bonus<=1 )
			return 0;
		me->receive_curing("kee",damage_bonus/2);	
		me->receive_heal("kee",random(damage_bonus/2)+1);
		switch(random(2)) {
                        case 0: return HIW "$n"HIW"一个不防，被劲气中夹杂的「冻冰川」内劲所伤。\n" NOR;
                        case 1: return HIR "$n"HIR"一个不防，被劲气中夹杂的「满江红」内劲所伤。\n" NOR;
                }
        }
}

void skill_improved(object me)
{
	if( me->query_skill("xuehejue",2)%2==0 )
		me->delete("mark/luoyang_xuehejue");
}

string query_parry_msg(object me,object target)
{
	string *str1,*str2,*str3;
	str1 = ({"身上","身后","背后","双臂","双手"});
	str2 = ({"血气","血光","血色",});
	str3 = ({"一闪","宛如实物","翻滚腾挪","冲天而起","迎头赶上",});
	return "结果$n"+str1[random(sizeof(str1))]+str2[random(sizeof(str2))]+str3[random(sizeof(str3))]+"，「咔」的一声将之格开。\n";	
}

string query_type(){ return "public";}