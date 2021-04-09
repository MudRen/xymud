// Room: /d/luoyang/shaoshuai.c
inherit ROOM;
void create ()
{
  set ("short", "点兵场");
  set ("long", @LONG
空阔的场地上铺满了细细的黄土，正好适合点兵。四面有几个
少帅军众将正在练武。树荫里，一位书生打扮的人正在背着手观看，
还不时走上前去指点一二。
LONG);

  set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"keting.c",
  "west" : __DIR__"qiwangfu",
  "north" : __DIR__"zoulang",
  "east" : __DIR__"shaoshuai2",
]));
  set("objects", ([
             __DIR__"npc/bing": 4,
             __DIR__"npc/xuxingzhi": 1,
             ]));
  setup();
}
