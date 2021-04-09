// emeiforce.c 峨嵋心法
inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { 
       if ( me->query("class")!="human") return notify_fail("你非人族弟子，无法习得！\n");
return 1; }

int practice_skill(object me)
{
        return
notify_fail("峨嵋心法只能用学的，或是从运用(exert)中增加熟练度。\n");
}

void skill_improved(object me)
{
	switch (me->query_skill("linji-zhuang",1))
	{
		  case 30:
		   tell_object(me, HIG "你天地术练成了! \n" NOR );
		   break;
		  case 60:
		   tell_object(me, HIG "你之心术练成了! \n" NOR );
		   break;
		  case 90:
		   tell_object(me, HIG "你龙鹏术练成了! \n" NOR );
		   break;
		  case 120:
		   tell_object(me, HIG "你风云术练成了! \n" NOR );
		   break;
		  case 150:
		   tell_object(me, HIG "你大小术练成了! \n" NOR );
		   break;
		  case 180:
		   tell_object(me, HIG "你幽冥术练成了! \n" NOR );
		   break;

	}
	return;
}

string exert_function_file(string func)
{
        return CLASS_D("emei") + "/emeiforce/" + func;
}

