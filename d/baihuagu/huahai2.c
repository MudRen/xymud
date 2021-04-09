inherit ROOM;
#include "/cmds/std/valid_move.h"
void create()
{
        set("short", "花海");
        set("long", @LONG
放眼望去，但见天地间仿佛已被鲜花充满，但却是无人认得出的花
朵，只觉得这些花无比的鲜艳，无比的美丽。真是令人想不到，荒漠之
中，竟有这样的花海。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"huahai1",
]));
        set("objects", ([
                __DIR__"npc/moon" : 1,
       ]) );

	setup();
}
void init()
{
  	add_action("do_push", "push");
}
int do_push(string arg)
{
  	object me=this_player();
  	if ((arg != "flower" && arg != "花丛") || !arg)
    		return notify_fail("你要推什么？\n");
  	if (me->is_busy()) return notify_fail("你忙着呢！\n");
        if (!valid_move(me)) return notify_fail("你被定住了，什么也干不了。\n");
  	if (me->query("family/family_name") != "百花谷")
      		return 1;
      	message_vision("$N推开花海中的一丛花走了进去，转眼消失不见了！\n", me);
      	me->move(__DIR__"lianxi");
      	return 1;
}
