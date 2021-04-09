// Room: /d/cloud/cloud21.c southeast of cloud2

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "云端");

	set("long", @LONG

    你站在云端，向四周望去，四面是一望无际的云海，头顶是碧蓝的天空。
向下望去，只见一片青翠的绿色，偶尔有一些细细的白线贯穿其中。一只小黄
莺悄悄地从云丛中探出头来，很惊讶地看着你。

LONG
	);

	set("exits", ([
		"west" 		: __DIR__"cloud23.c",
		"north" 	: __DIR__"cloud21.c",
		"northwest"	: __DIR__"cloud2.c",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	me->add("mana", -10);

	return ::valid_leave(me, dir);
}
