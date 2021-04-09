#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short", "桂树叶间");
  set ("long", @LONG
四周花香弥漫，枝叶繁茂，却已看不见地。
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "up" : __DIR__"ontop.c",
  "down" : __DIR__"tree1.c",
]));
	 set("objects", (["/d/obj/flower/guihua.c":2,]));

  setup();
}

int valid_leave(object who,string dir)
{
	if( dir=="up" && userp(who)
	 && who->query_temp("maze/40tupo")
	 && time()>=who->query("maze/tupo-40")+1800
	 && ( (who->query_level()==39&&who->query("combat_exp")>=16100000) ||wizardp(who) ) )
	{
		who->delete_temp("maze");
		who->dismiss_team(who);
        	if( MAZE_D->enter_maze(who, "tupo40-2") )
        	{
        		who->set("maze/tupo-40",time());
        		message_vision(HIC"\n$N"HIC"进入了昆仑木极之地"HIY"建木遗迹"HIC"。\n"NOR,who);
                	return 2;
                }
                else	return notify_fail("你有些踌躇不前。\n");
	}
	else	return ::valid_leave(who,dir);
}





