
// zhutian-bu.c 诸天化身步
// modified by Venus Oct.1997
// written by That

inherit SKILL;
#include <ansi.h>

string *dodge_msg = ({
	"只见$n一招"+BLINK""+HIB"「天地钩」"NOR"，身体腾空，双足向上，笔直地纵起丈余，躲过了$N这一招。\n",
	"$n身随意转，一式"+BLINK""+HIC"「凤点头」"NOR"头部前挺，侧身收腹，倏地往一旁挪开了三尺，避过了这一招。\n",
	"$n双足抓地，身形微晃，一招"+BLINK""+HIM"「鹰爪松」"NOR"有惊无险地避开了$N这一招。\n"
	"但是$n身形飘忽，一式"+BLINK""+HIW"「风摆柳」"NOR"，轻轻一纵，早已避开。\n",
	"$n一个"+BLINK""+HIR"「阴阳箭」"NOR"，向后纵出数丈之远，避开了$N的凌厉攻势，立即又欺近$N身旁。\n",
	"$n使出"+BLINK""+HIG"「日月扣」"NOR"，双手如钩向一旁飘然纵出，轻轻着地。\n"
});

int valid_enable(string usage)
{
	return (usage=="dodge");
}

int valid_learn(object me)
{
	if( (int)me->query("max_force") < 0 )
		return notify_fail("你的内力不够，没有办法学诸天化身步。\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30)
		return notify_fail("你现在太虚弱，练诸天化身步当心摔死。\n");
	if((int)me->query("force") < 3 )
		return notify_fail("你现在内力不够，不能乘风而起。\n");
	me->receive_damage("kee", 30);
	me->add("force", -3);
	return 1;
}

