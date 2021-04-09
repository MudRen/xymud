//Cracked by Roath
// Room: /d/nanhai/haibian
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "小岛");
  set ("long", @LONG

“万顷风云浮碧玉，孤插苍溟小白华”，这是南海上的一个小岛。
岛虽小却大大有名，据说观音菩萨就在岛上传经说法。极目远眺，
隐隐可见大陆的轮廓。
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"tingjing",
]));
  set("outdoors", "/d/nanhai");

  setup();
}

void init()
{
        add_action("do_swim", "swim");
}

int do_swim()
{
        object me, horse;
	me = this_player();
/*	
        if(me->query_temp("ridee")){
                horse=me->query_temp("ridee");
                me->command_function("dismount "+horse->query("id"));
        }                        
*/
message_vision(HIY "$N纵身一跃，跳入海中。只见$N使足了全身力气，手足并用，不一会儿就游到了大陆岸边。\n" NOR, me);
        me->move("/d/changan/southseashore");
	message_vision(HIY "只见$N浑身湿漉漉地从海里爬了上来。\n" NOR, me);
	me->receive_damage("kee", 20);
	me->receive_damage("sen", 20);
        return 1;
}

