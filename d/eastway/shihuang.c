#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short", "始皇陵");
  set ("long", @LONG

这是座落在官道以东的一个大丘陵，呈覆斗型。站在丘陵
上极目远眺，不禁心旷神怡。旁边有一座高大的石碑：
“秦始皇陵”。

LONG);

  set("exits", ([
        "east"       : __DIR__"bingma",
        "west"       : __DIR__"guandao3",
      ]));
  set("objects", ([ /* sizeof() == 2 */
         __DIR__"npc/wujiang" : 2,
         __DIR__"npc/bing" : 3,
      ]));

  set("outdoors", __DIR__);

  setup();
}

int valid_leave(object who,string dir)
{
        if( dir=="east" && userp(who)
         && who->query_temp("maze/qingling_ask") 
         && time()>=who->query("maze/qingling")+1800 )
        {
                who->delete_temp("maze");
                if( MAZE_D->enter_maze(who, "qingling-1") )
                {
                        who->set("maze/qingling",time());
                        message_vision(HIC"\n$N"HIC"进入了始皇陵。\n"NOR,who);
                        return 2;
                }
                else    return notify_fail("你有些踌躇不前。\n");
        }
        else    return ::valid_leave(who,dir);
}
