//Cracked by Roath
//  妖神之争 １。０
//  by happ@YSZZ 2000.4.7
//  /d/qujing/village/road1.c

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "后房");
  set ("long", @LONG

这里是这家人休息的地方，由于这家主人共有三个女儿，所以
整个房间都充满了青香。

LONG);
  set("exits", ([
        "north": __DIR__"house",
          ]));
  set("objects",([
        __DIR__"npc/girl1":1,
        __DIR__"npc/girl2":1,
        __DIR__"npc/girl3":1,
        ]));
  set("no_fight",1);
  setup();
}