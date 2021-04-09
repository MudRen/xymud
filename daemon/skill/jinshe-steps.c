inherit SKILL;
#include <ansi.h>
string *dodge_msg = ({
     "$n一招「金蛇游身」，$N只觉眼前一花，不见了$n的身影。\n",
     "$n一招「白蛇吐芯」，身形微晃，有惊无险地避开了$N这一招。\n",
     "只见$n身子向后一翻，一招「灵蛇腾空」，后荡而起，掠向一旁。\n",
     "$n可是$n一个「青蛇遁世」，长袖翻飞，躲过$N这一招。\n",
     "$n可是$n一个「银蛇乱舞」，忽左忽右，躲过$N这一招。\n",
});
int valid_enable(string usage) { return (usage=="dodge"); }
int valid_learn(object me)
{
        if( (int)me->query("spi") < 10 )
                return notify_fail("你的灵性不够，没有办法练金蛇游身步。\n");
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int practice_skill(object me)
{
        if( (int)me->query("sen") < 30 )
                return notify_fail("你的精神太差了，不能练金蛇游身步。\n");
        me->receive_damage("sen", 30);
        return 1;
}

