#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   	if( duration < 1 ) return 0;
   	if( !living(me) ) 
		message("vision", HIR""+me->name() + "伤口突然飙起一注血箭。\n"NOR, environment(me), me);
   	else 
   	{
      		tell_object(me, HIR "你被动物撕咬的伤口发作了。\n" NOR );
      		message("vision", HIR""+me->name() + "伤口突然飙起一注血箭。\n"NOR,environment(me), me);
   	}
   	me->receive_wound("kee", 200);
   	me->receive_damage("kee", 200);
   	me->apply_condition("beast_hurt", duration - 1);
   	if( duration < 1 ) return 0;
   	return CND_CONTINUE;
}
