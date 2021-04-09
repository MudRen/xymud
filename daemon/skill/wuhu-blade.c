//五虎断门刀, wuhu-blade.c 
#include <ansi.h>      
inherit SKILL; 

mapping *action = ({ 
              ([      "name"	: "饿虎扑食", 
                      "action"	: "$N纵身跃在空中，有如饿虎扑食一般，手中$w借着下落之势，向$n当头劈下！\n", 
                      "parry_msg":"$n纵身跃在空中，有如饿虎扑食一般，手中$W镗的一声将$N的攻击架开！\n", 
                      "damage"	:               25, 
                      "damage_type":  "劈伤" 
              ]), 
              ([      "name": "三人成虎", 
                      "action": "$N展开轻功在$n周围飞奔，疾跑中向$n砍去数刀。$n只见三个人影，从三个不同的方向砍来，不由惊慌失措。\n",
                      "parry_msg": "$n展开轻功在$N周围飞奔，疾跑中向$N砍去数刀，有条不紊的将其攻击格开。\n",
                      "damage":               30, 
                      "damage_type":  "砍伤" 
              ]),    
              ([      "name": "狐假虎威", 
                      "action": "$N一声巨吼，震得$n耳中回声不止。趁此机会，$N一刀削向$n的$l。原来是五虎断门刀中的杀手「狐假虎威」。\n", 
                      "parry_msg": "$n一声巨吼，震得$N耳中回声不止。趁此机会，$n一式「狐假虎威」，将其攻击挡开。\n", 
                      "dodge":                -10, 
                      "parry":                -10, 
                      "damage":               20, 
		      "damage_type":  "割伤" 
              ]),    
              ([      "name": "虎落平阳", 
                      "action": "$N左掌护身，滚倒在地上，右手$w连连向$n的双脚削去。\n", 
                      "parry_msg": "$n左掌护身，滚倒在地上，右手$W挥动，将$N攻击尽数挡住。\n", 
                      "damage":               30, 
		      "damage_type":  "劈伤" 
              ]),    
              ([      "name": "骑虎难下", 
                      "action": "$N站稳马步，运起浑身之力，逼入$w中，向$n发出雷霆一击！这招「骑虎难下」名字虽然难听，招数果然有效。\n", 
                      "parry_msg": "$n站稳马步，运起浑身之力，逼入$W中，一招「骑虎难下」将$N的招式全部逼回！\n",
                      "dodge":                -10, 
                      "parry":                -10, 
                      "damage":               30, 
		      "damage_type":  "劈伤" 
              ]), 
}); 
       
int valid_learn(object me)
{
	int i;
	string *skills;
	object ob; 

	if( me->query("public_skill/wuhu-blade_abandon") )
		return notify_fail("你以前曾经学过五虎断门刀，现在再也不能学习了。\n");
        if( (int)me->query_maxforce()< 150 ) 
        	return notify_fail("你的内力不够，不能学五虎断门刀， 多练些内力再来吧。\n"); 
	if (!(ob = me->query_temp("weapon")) 
         || (string)ob->query("skill_type") != "blade" ) 
		return notify_fail("你必须先找一把刀才能练刀法。\n"); 
	if( (int)me->query_skill("blade", 1) < 300)
                return notify_fail("你的基本刀法火候不够，无法练五虎断门刀。\n");			
	skills = ({
		"wudu-shenzhang","lieyang-jian","lihuo-dodge","shenghuo-spear",
	}); 
	for(i=0;i<sizeof(skills);i++)
	{
		if( me->query_skill(skills[i],2)>=1 )
			return notify_fail("你学过「"+to_chinese(skills[i])+"」，就无法再学「五虎断门刀」了。\n");
		if( me->query("public_skill/"+skills[i]+"_abandon") )
			return notify_fail("你以前曾经学过「"+to_chinese(skills[i])+"」，再也不能学习「五虎断门刀」了。\n");	
	} 		
	return 1; 
} 
       
varargs int practice_skill(object me,int flag) 
{ 
	if ((int)me->query("kee") < 30) 
        	return notify_fail("你的气太低，再练下去会有危险的！\n"); 
	if ((int)me->query("force") < 500) 
        	return notify_fail("你的内力不够，无法练习五虎断门刀。\n"); 
	if( me->query_skill("wuhu-blade",2)<150 )
		return notify_fail("你的「五虎断门刀」还不够纯熟，光靠练是没用的。\n");	        	
	me->receive_damage("kee", 20); 
        me->add("force", -50); 
       	if( flag )
       		write("你按着所学练了一遍五虎断门刀。\n"); 
        return 1; 
} 
       
int valid_enable(string usage) 
{ 
	return usage=="blade"||usage=="parry"; 
} 
       
mapping query_action(object me, object weapon) 
{ 
	int i;
	if( !me )
		return 0;
	i = me->query_temp("PERFORM_WUHU");
	if( i<=0 )	
		return action[random(sizeof(action))]; 
	if( i>5 )
		i = 5;
	return action[i-1];		
} 
     
string perform_action_file(string func) 
{ 
	if( !userp(this_player()) )
		return CLASS_D("public") + "/wuhu-blade/" + func; 
	else	return CLASS_D("public") + "/wuhu-blade2/" + func; 	
}

string query_type(){ return "public";}