//飞天御剑流
//lestat modi for dtxy 2001

inherit SKILL;
#include <ansi.h>

mapping *action = ({
   ([  "action": "$N手按刀身，一招"+HIC"「龙翔闪」"NOR",手中$w嗡嗡作响,由下而上直抽，招招不离$n的下颚",
     "dodge":     -20,
     "damage":     40,
     "damage_type":   "刺伤"
   ]),
([ "action":"只见$N飞身跃起,一招"+HIM"「龙椎闪」"NOR",剑光如水,一泄千里,洒向$n全身",
     "dodge":     -30,
     "damage":     40,
     "damage_type":   "割伤"
   ]),
   ([   "action":
"$N拔剑出鞘，一道弧形"NOR+HIC"剑光"NOR+HIB"划过"NOR+"，$n看出破绽,反击的一招却被$N以刀硝架住,正是一招"+HIG"「双龙闪」"NOR".\n",
     "dodge":     -40,
     "damage": 35,
     "damage_type":   "割伤"
   ]),
   
   ([ "action":
"$N以手中的$w向地面猛击,碎出的石块向$n砸去,正是这招"+HIY"「土龙闪」"NOR".\n",
     "dodge":     -20,
     "damage": 45,
     "damage_type":   "刺伤"
   ]),
  ([  "action":      
 "$N一招"+HIB"「龙巢闪」"NOR",剑尖划出无数圆圈,狂风骤起,笼罩天地.\n",
     "dodge":     -30,
     "damage": 40,
     "damage_type":   "刺伤"
   ]),
  ([   "action": 
"$N闪身躲开$n的攻击,手中$w自左而右地划了一个大弧,平平刺向$n的$l,正是飞天御剑流之"+HIW"「龙卷闪」"NOR".\n",
     "dodge":     -10,
     "damage":     50,
     "damage_type":   "刺伤"
   ]),
});

int valid_learn(object me)
{
   object ob;

   if( (int)me->query("max_force") < 50 )
    return notify_fail("你的内力不够,没有办法练飞天御剑流.\n");


   if( !(ob = me->query_temp("weapon"))
   ||   (string)ob->query("skill_type") != "blade" )
     return notify_fail("你必须先找一把刀才能练刀法。\n");

   return 1;
}

int valid_enable(string usage)
{
   return usage=="blade" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
     mapping* m_actions;
     return action[random(sizeof(action))];
}

int practice_skill(object me)
{
   if( (int)me->query("kee") < 30
   ||   (int)me->query("force") < 3 )
    return notify_fail("你的内力或气不够,没有办法练习飞天御剑流.\n");
   me->receive_damage("kee", 30);
   me->add("force", -3);
  write("你按着所学练了一遍飞天御剑流.\n");
   return 1;
}

string perform_action_file(string action)
{
  return "/daemon/class/feitian/feitian/" + action;
}






