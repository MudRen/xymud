#include <ansi.h>
inherit ROOM;
    
void create()
{
	set("short","【20级突破】副本");
        set("channel_id","引气入体");
        setup();
}

int valid_leave(object who,string dir)
{
	if( !who->query_temp("maze/tupo20-1") )
        	return notify_fail("你是怎么混进来的？！\n");
        return ::valid_leave(who,dir);
}
