// Room: /d/4world/school2.c
inherit ROOM;

void create ()
{
  set ("short", "武馆教练场");
  set ("long", @LONG

这里是方方正正的一个教练场，地上铺着黄色的细砂，许多弟子正
在在这里努力地操练着。东边一间不起眼的小屋，柴门半掩。往北
则是武馆师父们休息的大厅。
LONG);

  set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"schoolhall.c",
  "south" : __DIR__"school1",
  "east" : __DIR__"storage.c",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/dizi" : 1,
  __DIR__"npc/dongfangcong" : 1,
]));

  set("outdoors","aolai");

  setup();
}
