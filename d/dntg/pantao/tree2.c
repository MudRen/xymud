#include <ansi.h>
inherit "/d/dntg/pantao/tree.c";

void falldown(object,object);
void create()
{
        set("short", "蟠桃树上"NOR);
        set("long", "周围枝叶繁茂，遮天闭日，一片碧绿中你隐隐看到几颗红
彤彤的蟠桃若隐若现。这里的蟠桃层花甘实，六千年一熟。\n");




        set("exits", ([
  "down": __DIR__"pan2b",
        ]));

        set("objects", ([
               __DIR__"obj/pantao2": 2,
              ]));

        setup();
}


