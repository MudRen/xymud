//洛阳洛阳近郊
#include <room.h>
inherit ROOM;

void create()
{       
set("short", "小路");
set("long", @LONG
这是一条村中青石小路。村里农民都起早摸黑地下地去了，路上一个
大人也没有，只有几个小童在溪边捉鱼嬉戏。路边柳条拂地，时见野
花，几只小鸡小鸭踱来踱去。一条野狗摇着尾巴跑了过来，闻了闻，
又跑了开去。
    路边是本地唯一的一家杂货店，什么都卖。       
LONG);  
set("exits", ([
        "west" : __DIR__"cun_road2",
        "east"  : __DIR__"cun_road4",
        "south" : __DIR__"cun_zahuo",
]));
set("outdoors", "luoyang");
setup();
}

