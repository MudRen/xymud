// created by snowcat 12/2/1997

inherit ROOM;

void create ()
{
  set ("short", "草坡");
  set ("long", @LONG

山坡上荒草一大片，长有齐胸之高，走在里面深深浅浅竟如陷
沼泽一般。底下藤萝绊脚，抬头风声呼呼响，听上去象是幽歌
阵阵隐隐地传来。

LONG);

  set("exits", ([
        "northwest"    : __DIR__"caopo2",
        "southeast"    : __DIR__"huangye1",
      ]));
  set("outdoors",__DIR__"");
  setup();
}

