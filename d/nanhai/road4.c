//Cracked by Roath
// Room: /d/nanhai/road1
inherit ROOM;

void create ()
{
	set ("short", "小路");
  	set ("long", @LONG
这是一条通往后山的小路，道路至此越来越不好走，分叉也越来越
多了，就象迷宫一样，一不小心就会迷失方向，而且顺原路都走不回去。
你不禁踌躇起来，还要不要继续往前走呢？
LONG);
	set("outdoors", "/d/nanhai");
  	set("exits", ([
  		"north" : __FILE__,
  		"southeast" : __DIR__"road3",
  		"southwest" : __DIR__"road33",
	]));
	setup();
}

int valid_leave(object who,string dir)
{
	if( dir!="north" || !userp(who) )
		return ::valid_leave(who,dir);
	who->delete_temp("maze");
	who->set_temp("maze/公共地图","putuo_zizhulin");
	if( MAZE_D->enter_maze(who, "zizhulin1") )
		return 2;
	return notify_fail("你不禁踌躇起来，还要不要继续往前走呢？\n");
}	