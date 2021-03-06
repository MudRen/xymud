#include <ansi.h>
inherit SKILL;

object me = this_player();

mapping *action = ({
([      "action" : "$N使出一式"HIY"「大悲」"NOR"，$N手中的$w已经迅捷无比的刺向$n的$l。  ",
        "skill_name" : "大悲",
        "force" : (int)me->query_skill("tianlei-sword",1)/10,
        "dodge" : -10,
        "damage" : 30,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一式"HIC"「出剑」"NOR"，简单而有效地往$n的$l刺去。",
        "skill_name" : "出剑",
        "force" : (int)me->query_skill("tianlei-sword",1)/8,
        "dodge" : -5,
        "damage" : 30,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一招"HIB"「不动」"NOR"，身形一转，反手一挥，手中$w刺向$n的$l。",
        "skill_name" : "不动",
        "force" : (int)me->query_skill("tianlei-sword",1)/6,
        "dodge" : -10,
        "damage" : 40,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出"HIM"「初醒」"NOR"，双脚点地，全身转出一团剑光滚向$n。",
        "skill_name" : "初醒",
        "force" : (int)me->query_skill("tianlei-sword",1)/4,
        "dodge" : -10,
        "damage" : 48,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一招"HIW"「无涯」"NOR"，全身劲气贯于$w中，一片剑光袭向$n的$l。",
        "skill_name" : "无涯",
        "force" : (int)me->query_skill("tianlei-sword",1)/2,
        "dodge" : -10,
        "damage" : 54,
        "damage_type" : "刺伤",
]),
([      "action" : "$N剑锋忽转，一式"HIC"「冲霄」"NOR"，闪电般刺向$n的$l。",
        "skill_name" : "冲霄",
        "force" : (int)me->query_skill("tianlei-sword",1)/2,
        "dodge" : -15,
        "damage" : 60,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出一招"HIR"「归宗」"NOR"，手中$w狂风骤雨般地向$n的$l连攻数剑。",
        "skill_name" : "归宗",
        "force" : (int)me->query_skill("tianlei-sword",1),
        "dodge" : -20,
        "damage" : 66,
        "damage_type" : "割伤",
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
 
int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 100 )
                return notify_fail("你的内力不够，没有办法练天雷剑。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");

        return 1;
}

int practice_skill(object me)
{

	          object ob;

          if( me->query_skill("tianlei-sword",1) < 201 )  
				return notify_fail("天雷剑必须合壁。\n");  

	   if(me->query("family/family_name") != "娥眉")
            return notify_fail("这是仙家绝学,你是从什么地方偷学的呢?\n"); 
       if( (int)me->query("max_force") < 100 )
                return notify_fail("你的内力不够，没有办法练天雷剑法。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");

        return 1;


}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
      string perform_action_file( string action)  
     {  
           return CLASS_D("emei") + "/tianlei-sword/" + action;  
      }  

int query_max_research()
{
        return 220;
}
