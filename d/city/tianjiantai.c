//changan city
#include <ansi.h>
inherit ROOM;

void create ()
{
set ("short", "天监台");
set ("long", @LONG

这里便是长安城钦天监台，朝廷每年的祭天仪式都在这里举行。中央
广场上画着八卦图形，周围还摆这一些施法时用的器具．天监台的总
管是正先生袁天罡，总可在这里看到他的身影。
LONG);
set("exits", ([
        "east" : "/d/city/xuanwu-n1",
        ]));
set("objects", ([
        __DIR__"npc/yuantiangang" : 1,
        ]));
set("no_clean_up", 0);
set("outdoors", "changan"); 
setup();
}
