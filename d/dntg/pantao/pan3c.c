// created by snowcat.c 5/27/1997
// room: /d/pantao/pan3c.c

inherit ROOM;

void create ()
{
  set ("short", "蟠桃园");
  set ("long", @LONG

蟠桃园内花红叶绿，夭夭灼灼花盈树，颗颗枝枝果压枝。只见
是：时开时结千年熟，无夏无冬万载迟，先熟的，酡颜醉脸，
还生的，带蒂青皮。好个凝脂肌带绿，映日显丹姿。

LONG);

  set("exits", ([
        "west"       : __DIR__"pan3b",
      "north" : __DIR__"pan2c",
]));
//         "northeast"  : __DIR__"palace5",

  set("outdoors",1);
  setup();
}

