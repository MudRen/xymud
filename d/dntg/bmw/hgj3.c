//sgzl

#include <room.h>
inherit ROOM;

void create()
{
set("short", "护国街");
set("long", @LONG
    
在这里有天宫的重兵把守，这条街直通天宫兵营，
那里驻扎着几十万天兵。兵营旁边是饲养天马的
御马间。
LONG );


set("exits", ([
  "north"   : "/d/dntg/sky/yunluw3",
  "south"   : __DIR__"hgj2",
]));


set("objects", ([
]));



set("outdoors", 1);

setup();
}
