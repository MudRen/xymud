//相柳之毒
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	mixed b;
	int i,t;
	string *str,arg;
   	if( duration < 1 
   	 || !me || !living(me) )
	{
		if( me )
			me->delete_temp("xiangliu"); 
   		return 0;
   	}	
   	str=me->query_temp("xiangliu");
   	if( !str || !arrayp(str) )
   		return 0;
   	for(i=0;i<sizeof(str);i++)
   	{
		arg = str[i];
		if( !arg )
			continue;
		if( arg=="busy" )
		{
			b = me->query_busy();
			if( b && intp(b) && b<2 )
				t = (int)b+1;
			else	t = 2;
			message_vision(HIG"\n$N"HIG"身上冒起一道绿油油的雾气，顿时举步维艰。\n"NOR,me);
			me->start_busy(t);
		}
		else if( arg=="hurt" )
		{
			t = 10-duration;
			if( t<1 ) t = 1;
			if( t>5 ) t = 5;
			t = t*500;
			message_vision(HIR"\n$N"HIR"身上冒起一道红彤彤的雾气，顿时血光飞溅。\n"NOR,me);
			me->receive_damage("kee",t);
			COMBAT_D->report_status(me);
		}
		else if( arg=="hurt2" )
		{
			t = 10-duration;
			if( t<1 ) t = 1;
			if( t>5 ) t = 5;
			t = t*500;
			message_vision(HIR"\n$N"HIR"身上冒起一道红彤彤的雾气，顿时血光飞溅。\n"NOR,me);
			me->receive_wound("kee",t);
			COMBAT_D->report_status(me,1);
		}
		else if( arg="no_pfm" )
		{
			if( time()>(me->query_temp("no_perform/start")+me->query_temp("no_perform/time")) )
			{
				message_vision(HIM"\n$N"HIM"身上冒起一道道紫气，在$P周身盘旋。\n"NOR,me);
				me->set_temp("no_perform",([
					"start" : time(),
					"time"  : 5,
					"msg"	: HIR"\n你刚想发招，却被紫雾所扰，顿时章法全无，发不出招来。\n"NOR,
				]));
			}
		}
		else if( arg="no_cast" )
		{
			if( time()>(me->query_temp("no_cast/start")+me->query_temp("no_cast/time")) )
			{
				message_vision(MAG"\n$N"MAG"身上冒起一道道紫气，在$P周身盘旋。\n"NOR,me);
				me->set_temp("no_cast",([
					"start" : time(),
					"time"  : 5,
					"msg"	: HIR"\n你刚想发招，却被紫雾所扰，顿时口诀全忘，发不出招来。\n"NOR,
				]));
			}
		}	
		
   	}		
   		
   	me->apply_condition("xiangliu_hurt", duration - 1);
   	return CND_CONTINUE;
}
