#include <ansi.h>
inherit FORCE;
int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) {
       if ( me->query("class")!="yao" && !me->samsara_check("wudu-xinfa") && me->query("spskk")!=12)         return notify_fail("你非妖族弟子，无法习得！\n");
return 1; }

int practice_skill(object me)
{
        return notify_fail("五毒心法只能向师父学，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
        return CLASS_D("wudu") + "/wudu-xinfa/" + func;
}

