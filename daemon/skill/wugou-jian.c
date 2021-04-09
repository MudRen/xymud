inherit SKILL;
#include <ansi.h>
mapping *action = ({
([      "name":   "身出莲花清净台",
    "action" : "$N身体左转，左手剑指，剑尖前端一寸处短促抖腕发力，\n"
    "一招"BLINK""HIR"「身出莲花清净台」"NOR"，手中$w轻轻颤动，一剑自上而下扎向$n．",
    "dodge" : 5,
    "damage" : 15,
    "parry"  :10,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "三乘妙典法门开",
    "action" : "$N身形不动，右前臂外旋，剑刃上崩，一招"BLINK""HIR"「三乘妙典法门开」"NOR"，\n"
    "手中$w向前下反刺，一剑指向$n",
    "dodge" : 10,
    "damage" : 20,
    "parry"  :15,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "玲珑舍利超凡俗",
    "action" : "$N左脚向前，蹬地跳起，右手$w突向前刺，随转体变向，\n"
    "使出一式"BLINK""HIR"「玲珑舍利超凡俗」"NOR"，剑光如匹练般泄向$n",
    "dodge" : 5,
    "damage" : 25,
    "parry"  :15,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "璎珞明珠绝世埃",
    "action" : "$N平剑斜洗，臂圆剑直，双脚交替弧形迈进，右手$w使出一式"BLINK""HIR"「璎珞明珠绝世埃」"NOR"，"
    "剑锋往来运转如梭，连绵不绝刺向$n",
    "dodge" : -5,
    "damage" : 35,
    "parry"  :15,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "八德池中生
紫焰",
    "action" : "$N屈腕抬臂，剑由前向后上方抽带，挺起中平剑奋勇向前，右手$w使出\n"
    "一式"BLINK""HIR"「八德池中生紫焰」"NOR"刺向$n",
    "dodge" : -10,
    "damage" : 30,
    "parry"  :10,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "七珍妙树长金苔",
    "action" : "$N左上步，抱剑当胸，右手$w一式"BLINK""HIR"「七珍妙树长金苔」"NOR"，"
    "剑意圆润，刺向$n",
    "dodge" : 0,
    "parry"  :15,
    "damage" :30,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "只因东土多英俊",
    "action" : "$N侧身退步，左手剑指划转，右手$w一记"BLINK""HIR"「只因东土多英俊」"NOR"，"
    "自下上撩指向$n",
    "dodge" : -10,
    "damage" : 40,
    "parry"  :15,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
([      "name":   "来遇前绿结圣胎",
    "action" : "$N碎步急进，提剑沿剑身方向疾速上崩，一招"BLINK""HIR"「来遇前绿结圣胎」"NOR"直取$n",
    "dodge" : -5,
    "damage" : 40,
    "parry"  :25,
    "lvl" : 0,
    "damage_type" : "刺伤"
]),
  ([ "name": "「天外飞仙」",
     "action":
HIW"剑光一闪，如惊虹掣电。从来没有人看见过如此辉煌，如此迅急的剑光。\n忽然间，整个大地都已在剑气笼罩下-- 一种可以令人连骨髓都冷透的剑气。\n这一剑的锋芒世上已没有人能抵挡。\n"NOR,
     "dodge": -150,
     "parry": -150,
       "damage": 400,
       "force": 400,
     "damage_type": "刺伤",
]),
});
int valid_enable(string usage) { 
    return (usage == "sword") || (usage == "parry");
}
int valid_learn(object me)
{
    if ((int)me->query("force") < 100)
   return notify_fail("你的内力不够。\n");
    if ((int)me->query_skill("force", 1) < 10)
   return notify_fail("你的内功火候太浅。\n");
    return 1;
}
mapping query_action(object me, object weapon)
{
        int i;
        i=me->query_temp("WGJ_perform");
          if( !me->query_temp("WGJ_perform") ) {
        return action[random(8)];
        }else {
        return action[i];
        }
}        
int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return notify_fail("你的内力或气不够，没有办法练习吴钩剑法。\n");
        me->add("kee", -30);
        me->add("force", -3);
        write(HIC"混天正体合先天，万劫千番只自然。\n"NOR,me);
        return 1;
}
string perform_action_file(string func) {
  return CLASS_D("kunlun") + "/wugou-jian/" + func;
}

