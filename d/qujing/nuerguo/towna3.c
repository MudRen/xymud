// created by snowcat.c 4/4/1997
// room: /d/nuerguo/towna3.c

inherit ROOM;

void create ()
{
  set ("short", "安乐巷东");
  set ("long", @LONG

这里是西梁镇的安乐巷东。北面有一堵长长的城墙，看样子
大概是西梁王宫所在地。女人们三三两两围在一起，谈论着
西梁公主最新的招驸一事。

LONG);

  set("exits", ([
        "west"  : __DIR__"towna2",
        "south" : __DIR__"townb3",
    ]));
  set("outdoors", __DIR__"");

  setup();
}






