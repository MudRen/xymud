// zhting.c

inherit ROOM;

void create ()
{
  set ("short", "都市殿");
  set ("long", @LONG

这里便是阴间地府十王之都市王的宫殿．平时若是无事，都市
王便会在殿上处理一些杂务．殿上一张大木桌，桌上堆了一些
文告之类，一个小青铜炉吐着淡淡的的青烟，一个青衣童子侍
立于后．
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"walk2",
]));
  set("hell", 1);
  set("out_doors", 1);
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/dushiwang" : 1,
  __DIR__"npc/tong" : 1,
]));

  setup();
}
