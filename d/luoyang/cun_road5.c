//洛阳洛阳近郊
#include <room.h>
inherit ROOM;

void create()
{       
set("short", "小村口");
set("long", @LONG
这是一条村中青石小路。村里农民都起早摸黑地下地去了，路上
一个大人也没有。
前方一座高高的大山阻住了去路，山下是一眼无际的茂密树林。
由于这边住户多是农民，并且树林里好似有野兽，所以再往前去，便
人迹罕至了。

LONG);  
set("exits", ([
        "west" : __DIR__"cun_road4",
]));
set("objects", ([ //sizeof() == 1
//        "/d/maze/qianjidong/door" : 1,
]));
set("outdoors", "luoyang");
setup();
}

