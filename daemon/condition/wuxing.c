#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   	if( !living(me) ) 
   		message("vision", HIR""+me->name() + "身中五行奇毒，只觉五感缺失。\n"NOR, environment(me), me);
   	else 
   	{
   		tell_object(me, HIY "所中五行奇毒发作了。\n" NOR );
		message("vision", HIR""+me->name() + "身中五行奇毒，只觉五感缺失。\n"NOR, environment(me), me);
   	}
   	me->receive_wound("kee",150);
   	me->receive_damage("kee",150);
	me->set_temp("death_msg","五行奇毒毒发身亡，听说死的时候，已不成人形！\n");
   	me->apply_condition("wuxing", duration - 1);
	if( duration < 1 ) 
   	{
   		if( me->query_temp("death_msg")=="五行奇毒毒发身亡，听说死的时候，已不成人形！\n" )
   			me->delete_temp("death_msg");
   		return 0;
   	}
   	return CND_CONTINUE;
}

string name() {return "五行奇毒";}

