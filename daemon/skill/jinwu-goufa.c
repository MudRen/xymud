// jinwu-goufa.c 金蜈钩法
#include <ansi.h>
inherit SKILL;
mapping *action = ({
([   "action" : "$N手中$w一抖，一式「灵蛇吐信」，闪电般的疾刺向$n的$l",
     "dodge"  : -10,
     "parry"  : 10,
     "damage" : 60,    "damage_type":  "刺伤"
]),
([   "action" : "$N身形突闪，招式陡变，手中$w从一个绝想不到的方位斜刺向$n的$l",
     "dodge"  : -10,
     "parry"  : 10,
     "damage" : 70,
       "damage_type":  "刺伤"
]),
([   "action" : "$N一式「柔丝轻系」，剑意绵绵不绝，化做一张无形的大网将$n困在当中",
     "dodge"  : -20,
     "parry"  : 20,
     "damage" : 50,
          "damage_type":  "刺伤"
]),
([   "action" : "$N一声阴笑，飞身纵起，一式「张牙舞爪」，手中$w狂舞，幻出千万条手臂，合身扑向$n",
     "dodge"  : -40,
     "parry"  : 30,
     "damage" : 90,
          "damage_type":  "刺伤"
]),
([   "action" : "$N身形一旋看似欲走，手中$w却倏的从腋下穿过，疾刺向$n的$l，好一式「天蝎藏针」",
     "dodge"  : -20,
     "parry"  : 10,
     "damage" : 100,
   "damage_type":  "刺伤"
]),
([   "action" : "$N脚步踉跄，身形忽的向前跌倒，一式「井底望月」，掌中$w自下而上直刺$n的小腹",
     "dodge"  : 10,
     "parry"  : -20,
     "damage" : 60,
         "damage_type":  "刺伤"
]),
([   "action" : "$N身形一晃，一式「金蛇缠腕」，手中$w如附骨之蛆般无声无息地刺向$n的手腕",
     "dodge"  : -20,
     "parry"  : 0,
     "damage" : 70,
    "damage_type":  "刺伤"
]),
([   "action" : "$N一声厉啸，身形冲天而起，一式「神蟾九变」，掌中$w如鬼魅般连刺$n全身九道大穴",
     "dodge"  : -30,
     "parry"  : 10,
     "damage" : 90,
     "lvl"    : 110,
     "damage_type":  "刺伤"
]),
([   "action" : "$N缓缓低首，手中$w中宫直进，一式「蜈化龙形」，迅捷无比地往$n的$l刺去",
     "dodge"  : -20,
     "parry"  : -20,
     "damage" : 120,
    "damage_type":  "刺伤"
]),
([   "action" : "$N深吸一口起，招演「万毒至尊」，$w尖端透出一条强劲的黑气，闪电般的袭向$n",
     "dodge"  : -30,
     "parry"  : -20,
     "damage" : 150,    "damage_type":  "刺伤"
]),
});
int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 1200 )
                return notify_fail("你的内力修为不够深，金蜈钩法学了也没用。\n");
        if (!(ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword" )
                return notify_fail("你必须先找一柄剑才能练习剑法。\n");
        return 1;
}

int practice_skill(object me)
{
        int dod=(int)me->query_skill("dodge");
        int swo=(int)me->query_skill("jinwu-goufa");

        if (dod<swo/2)
                return notify_fail("你的身法跟不上剑法，练下去很可能会伤到自己。\n");
        if ((int)me->query("kee") < 30)
                return notify_fail("你体质欠佳，强练御剑术有害无益。\n");
if ( me->query("family/family_name")!="黄花观五毒门"  && me->query_skill("jinwu-goufa",1)<350 && !me->samsara_check("jinwu-

goufa")) 
return notify_fail("非妖魔之身不可习也。\n"); 
if (me->query("class")!="yao" && !me->samsara_check("jinwu-goufa"))
        return notify_fail("非妖魔之身不可习也。\n");  
        if ((int)me->query("force") < 5)
                return notify_fail("你内力不足，强练金蜈钩法有走火入魔的危险。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        message_vision("$N默默回忆了一会儿，然后练了一遍金蜈钩法。\n", me);
        return 1;
}

int valid_enable(string usage)
{
        return usage=="sword"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string perform_action_file(string func)
{
        return CLASS_D("wudu") + "/jinwu-goufa/"+func;
}

