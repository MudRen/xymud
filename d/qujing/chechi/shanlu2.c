// created by snowcat.c 10/21/1997
// room: /d/qujing/chechi/shanlu2.c

inherit ROOM;

void create ()
{
  set ("short", "山路");
  set ("long", @LONG

城内的小山坡上斜斜地筑了一条土小路，弯弯曲曲盘旋而上。因
年久失修的缘故，路面坎坷凸凹不平。路边早已是乱草丛生，杂
石竖横。

LONG);

  set("exits", ([
        "westdown"     : __DIR__"shanlu1",
        "southwest"    : __DIR__"shanlu3",
      ]));

  set("outdoors","/d/qujing/chechi");
  setup();
}

