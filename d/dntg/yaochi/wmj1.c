//sgzl

#include <room.h>
inherit ROOM;

void create()
{
set("short", "王母街");
set("long", @LONG
    
一条宽敞的大街，笔直的伸展出去。这条街上住的
都是天宫最有权势的人，路的尽头，就是蟠桃园。
LONG );


set("exits", ([
  "north"   : __DIR__"wmj2",
]));

set("objects", ([
//  __DIR__"npc/chijiao"   : 1,
]));




set("outdoors", 1);

setup();
}
