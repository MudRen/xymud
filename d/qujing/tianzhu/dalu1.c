// create by snowcat.c 12/8/1997

inherit ROOM;

void create ()
{
  set ("short", "大路");
  set ("long", @LONG

一条长长的野外大路，路上铺着碎石子，路边开着无名花草。
大路在平坦的原野上弯曲地蜿蜒。远处可见青青群峦起伏于云
雾之中。

LONG);

  set("exits", ([
        "east"   : __DIR__"ximen",
        "west"   : "/d/qujing/lingshan/dalu3",
      ]));
  set("outdoors", __DIR__);

  setup();
}



