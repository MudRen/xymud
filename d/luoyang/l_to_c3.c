//洛阳洛阳近郊
#include <room.h>
inherit ROOM;

void create()
{       
set("short", "洛阳南郊");
set("long", @LONG
这里是洛阳的南郊，虽然已是郊区，但来往的旅客依然是络绎不绝，
沿着脚下宽阔笔直的大路向南走，便能到达两京地带；向北走，便
是古都洛阳。
往东的方向座落着一个小村庄。

LONG);  
set("exits", ([
        "north" : __DIR__"l_to_c2",
       "east" : __DIR__"cun_road1",             
]));
set("outdoors", "luoyang");
setup();
}
