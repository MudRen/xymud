// 少帅军点兵场

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "点兵场");
  set ("long", @LONG
空阔的场地上铺满了细细的黄土，正中一圆柱放着用来净化长
生决魔性的和氏壁(jinghua)。四面众将盘膝而坐，吸取至善之气。
北面是一间厢房,府中的嘉宾可以去休息。场地南边有个兵器库。
LONG);

  set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"kefang",
  "south" : __DIR__"bingqiku",
// "east" : __DIR__"majuan",
  "west" : __DIR__"shaoshuai",
]));

  setup();
}
