#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	object fb,fowner;
	mapping data;
	
	data = me->query_temp("nili-qi");
	if( !data || !living(me) ) 
	{
      		message_vision("$N身上泥犁旗的效果已经消失。\n",me);
      		if( me->query("env/invisibility") )
      			me->delete("env/invisibility");
      		me->delete_temp("nili-qi");	
      		return 0;	
   	}
   	fb = data["fabao"];
   	if( !fb || !objectp(fb) )
   	{
      		message_vision("$N身上泥犁旗的效果已经消失。\n",me);
      		if( me->query("env/invisibility") )
      			me->delete("env/invisibility");
      		me->delete_temp("nili-qi");	
      		return 0;	
	}
	fowner = data["Fowner"];
	if( !fowner || !objectp(fowner) || !present(fb,fowner) )
	{
      		message_vision("$N身上泥犁旗的效果已经消失。\n",me);
      		if( me->query("env/invisibility") )
      			me->delete("env/invisibility");
      		me->delete_temp("nili-qi");	
      		return 0;	
	}
	if( time()>=data["start"]+data["time"] )
	{
      		message_vision("$N身上泥犁旗的效果已经消失。\n",me);
      		if( me->query("env/invisibility") )
      			me->delete("env/invisibility");
      		me->delete_temp("nili-qi");	
      		return 0;	
	}
	return CND_CONTINUE;
}
int can_clear() { return 0; }
string name() {return "系统设置";}

