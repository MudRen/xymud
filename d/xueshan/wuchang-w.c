//standroom.c used by weiqi...others may hate this format:D
//wuchang-w.c

inherit ROOM;

void create ()
{
	set ("short", "西武场");
	set ("long", @LONG

这是冰宫前的一块平地，供大雪山弟子练功之用。冰面极平，光
鉴照人。不过走在上面得小心点，雪山弟子也正是借此锻炼下盘
的稳固功夫。
LONG);

	//set("item_desc", ([" *** " : " *** \n", ]));
	//for look something.

	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"wuchang-sw",
		"north" : __DIR__"wuchang-nw",
	//	"west" : __DIR__"restroom",
		"east" : __DIR__"wuchang-c",
		//"up" : __DIR__"***",
		//"down" : __DIR__"***",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"npc/xunshi" : 2,
		__DIR__"npc/huangque-shier" : 1,
		
	]));


	set("outdoors", "xueshan");

	setup();
}
