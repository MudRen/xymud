//sgzl

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "傲来国");
	set("long", @LONG
东胜神洲海边一小国。傲来国西临大海，东靠花果山，只是
在其间一块狭窄的平原地带上建有一座城池。一条大路直通
南方，路上行人也是匆匆而过。
LONG );


	set("exits", ([
  		"west"   : "/d/changan/aolaiws",
   		"east"   : "/d/dntg/hgs/flowerfruit",
  		"south"   : __DIR__"northgate",
	]));
	set("out_doors", "aolai");
	setup();
}

int valid_leave(object who,string dir)
{
	if( dir!="east" || !userp(who) )
		return ::valid_leave(who,dir);
		
	if( who->query_level()!=9 )
	{
		if( !wizardp(who) )
			return ::valid_leave(who,dir);
		if( !who->query("env/test") )
			return ::valid_leave(who,dir);
	}
	if( time()<who->query("maze/tupo10")+1800 )
		return ::valid_leave(who,dir);
	
	who->delete_temp("maze");
	if( MAZE_D->enter_maze(who, "tupo10") )
	{
        	who->set_temp("maze/tupo10",1);
        	who->set("maze/tupo10",time());
        	tell_object(who,HIY"你无意间闯进了大山深处。\n"NOR);
        	return 2;
	}
	else	return ::valid_leave(who,dir);
}	