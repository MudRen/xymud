inherit ROOM;
#include <room.h>

void create ()
{
  set ("short", "白云洞");
  set ("long", @LONG

洞口虽小，洞内却别有天地。
LONG);
  set("exits", ([ /* sizeof() == 3 */
  "out" : __DIR__"undertree",
]));

  set("no_clean_up", 1);
  setup();
}
int clean_up()
{
      return 0;
}

