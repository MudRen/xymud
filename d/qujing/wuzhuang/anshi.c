//Cracked by Roath
//anshi.c
#include <room.h>
inherit ROOM;

int can_enter=1;

void create ()
{
	set ("short", "亭底暗室");
	set ("long", @LONG

这是牡丹亭底下的一间暗室。黑咕窿咚的什么也看不清。你试着
到处摸了摸(mo)。 
LONG);

	set("exits", 
	([ //sizeof() == 4
		//"southwest" : __DIR__"juyuan",
		//"north" : __DIR__"southpool",
		"up" : __DIR__"mudanting",
		//"west" : __DIR__"westway6",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"obj/huangtong-key" : 1,
	]));

	create_door("up", "桌底暗门", "down", DOOR_CLOSED);
	//set("outdoors", "wuzhuang");

	set("no_clean_up", 1);
	can_enter=1;

	setup();
}