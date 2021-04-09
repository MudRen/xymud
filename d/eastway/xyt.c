inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "小雁塔");
  set ("long", @LONG

小雁塔是一座通高几十丈的砖塔，从底下向上看去，庄严而玲珑，
塔身檐角密布，一共有十五层之高，与东边的大雁塔遥遥相望。塔
底有门洞通向塔内，东边有路通向进士场。
LONG);

  set("exits", ([
        "enter"     : __DIR__"xyt1",
        "east" : __DIR__"jinshi",
      ]));
  set("outdoors", __DIR__);

  setup();
}

int valid_leave(object who,string dir)
{
	object fo;
	if( dir!="enter" && dir!="east" )
		return ::valid_leave(who,dir);
	if( !userp(who) )
		return ::valid_leave(who,dir);
	if( !wizardp(who) && !who->query("env/test") 
	  && (who->query_level()<25|| who->query_level()>=30) )
		return ::valid_leave(who,dir);
	if( !objectp(fo=present("jin fo",who))
	 || base_name(fo)!="/d/maze/xiaoyan-ta/obj/fo" )
	 	return ::valid_leave(who,dir);
	if( time()<who->query("maze/xiaoyan-ta")+1800 )	
		return ::valid_leave(who,dir);
	who->delete_temp("maze");
	if( MAZE_D->enter_maze(who, "xiaoyan-ta") )
	{
		if( fo && !wizardp(who) )
			destruct(fo);
        	who->set_temp("maze/xiaoyan",1);
        	who->set("maze/xiaoyan-ta",time());
        	tell_object(who,HIY"你携金佛行至此地，一旁早有法门寺的大和尚接过金佛，将你从一旁带入塔下密道。\n"NOR);
        	return 2;
	}		
	return ::valid_leave(who,dir);
}	