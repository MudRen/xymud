// rose_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	me->receive_wound("sen", 10);
	me->receive_damage("kee", 10);
	me->set_temp("death_msg","火玫瑰毒发作死了。\n");
	me->apply_condition("rose_poison", duration - 1);
	tell_object(me, HIG "你中的" HIR "火玫瑰毒" HIG "发作了！\n" NOR );
	if( duration < 1 ) return 0;
	return 1;
}
