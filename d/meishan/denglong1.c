
#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "登龙津");
  set ("long", @LONG

灌江水静静东流，遥望水面一片渺茫。江心小岛上有数百只野
鸭，在水边盘旋沉浮。岸边有几十根大木桩子搭成的渡口，偶
有船只停靠。
LONG);


  set("objects", ([ /* sizeof() == 1*/ 
  __DIR__"npc/fisher" : 1,
]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
  "northwest" : "/d/meishan/guanjiang3",
  "east" : __DIR__"denglong2",
]));

  setup();
}

