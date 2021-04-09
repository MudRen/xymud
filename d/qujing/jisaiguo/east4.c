#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "金光寺东街");
  set ("long", @LONG

路西是赦建金光寺，青色的寺墙高立，高有丈许，上覆青色瓦片。
街道很宽，来往车辆不多，路面很干净，是因为僧人经常打扫的
缘故。路边民居错落有序，几个小童在路边玩耍。
LONG);

//  set("objects", ([ /* sizeof() == 1*/ 
//  __DIR__"npc/erlang" : 1,
//]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"east3",
  "west" : __DIR__"south2",
]));

  setup();
}

