// created by snowcat 11/16/1997

inherit ROOM;

void create ()
{
  set ("short", "山道");
  set ("long", @LONG

山道顺山势盘绕上下，峦青涧清景色宜人。道路两边或是绿林
或是翠岭，猿啼鹃鸣野鹿踏茵荒无人烟，远远看去，苍松奇柏
层层叠叠紫云遮天气象无穷。

LONG);

  set("exits", ([
        "southwest"    : __DIR__"shandao3",
        "northup"    : __DIR__"shandao1",
      ]));
  set("outdoors",__DIR__"");
  setup();
}

