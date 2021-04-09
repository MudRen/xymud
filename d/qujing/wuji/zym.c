// Room: /u/mimi/zhuziguo/zhengyangmen.c    snowcat moved to /d/qujing/wuji
inherit ROOM;

void create ()
{
  set ("short", "正阳门");
  set ("long", @LONG

这里是进入皇宫的正门，雕龙塑凤，一眼看去富丽堂皇。门前侍卫盔
甲鲜明，威风凛凛，守卫森严。门内琼阁林立，层层叠叠，瑞气纷飘。

LONG);

  set("exits", ([ /* sizeof() == 2 */
    "south" : __DIR__"nstreet2",
    "north" : __DIR__"palace.c",
    "west" : __DIR__"wall3",
  ]));

  setup();
}
